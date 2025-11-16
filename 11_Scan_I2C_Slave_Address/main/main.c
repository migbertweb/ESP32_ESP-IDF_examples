/**
 * Archivo: main.c
 * Descripción: Ejemplo de escáner de direcciones I2C para ESP32.
 *              Escanea todas las direcciones I2C posibles (1-127) e informa
 *              qué direcciones tienen dispositivos conectados.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo es útil para identificar dispositivos I2C conectados
 *      y verificar sus direcciones en el bus I2C.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include <string.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include "sdkconfig.h"

// Configuración de pines I2C
#define I2C_MASTER_SCL_IO           22      // Pin GPIO para el reloj I2C (SCL)
#define I2C_MASTER_SDA_IO           21      // Pin GPIO para los datos I2C (SDA)
#define I2C_MASTER_NUM             I2C_NUM_0 // Puerto I2C a utilizar
#define I2C_MASTER_FREQ_HZ         1000000  // Frecuencia del reloj I2C (1MHz)
#define I2C_MASTER_TX_BUF_DISABLE  0        // Deshabilitar búfer de transmisión
#define I2C_MASTER_RX_BUF_DISABLE  0        // Deshabilitar búfer de recepción
#define I2C_MASTER_TIMEOUT_MS      1000     // Tiempo de espera en milisegundos

// Etiqueta para mensajes de log
static const char *TAG = "I2C_SCANNER";

/**
 * @brief Inicializa el controlador I2C en modo maestro
 * 
 * @return esp_err_t Código de error ESP_OK si es exitoso
 */
static esp_err_t i2c_master_init(void)
{
    esp_err_t ret;
    
    // Configuración del controlador I2C
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,                     // Modo maestro
        .sda_io_num = I2C_MASTER_SDA_IO,            // Pin SDA
        .scl_io_num = I2C_MASTER_SCL_IO,            // Pin SCL
        .sda_pullup_en = GPIO_PULLUP_ENABLE,         // Habilitar pull-up en SDA
        .scl_pullup_en = GPIO_PULLUP_ENABLE,         // Habilitar pull-up en SCL
        .master.clk_speed = I2C_MASTER_FREQ_HZ,      // Frecuencia del reloj
        .clk_flags = 0,                              // Sin banderas especiales de reloj
    };
    
    // Aplicar configuración al controlador I2C
    ret = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al configurar parámetros I2C: %s", esp_err_to_name(ret));
        return ret;
    }
    
    // Instalar el controlador I2C
    ret = i2c_driver_install(
        I2C_MASTER_NUM,              // Puerto I2C
        I2C_MODE_MASTER,             // Modo maestro
        I2C_MASTER_RX_BUF_DISABLE,   // Tamaño del búfer de recepción
        I2C_MASTER_TX_BUF_DISABLE,   // Tamaño del búfer de transmisión
        0                            // Flags (0 para ninguno)
    );
    
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al instalar el controlador I2C: %s", esp_err_to_name(ret));
        return ret;
    }
    
    ESP_LOGI(TAG, "Controlador I2C inicializado correctamente");
    return ESP_OK;
}

/**
 * @brief Escanea el bus I2C en busca de dispositivos
 */
static void i2c_scan(void)
{
    uint8_t address;
    esp_err_t ret;
    bool devices_found = false;
    
    ESP_LOGI(TAG, "Iniciando escaneo del bus I2C...");
    printf("\nEscaneando bus I2C...\n");
    printf("   ");
    
    // Encabezado de la tabla de direcciones
    for (int i = 0; i < 0x10; i++) {
        printf(" %02X ", i);
    }
    printf("\n   -------------------------------------------------\n");
    
    // Escanear todas las direcciones I2C posibles (1-127)
    for (int i = 0; i < 128; i += 16) {
        printf("%02X:", i);
        for (int j = 0; j < 16; j++) {
            address = i + j;
            
            // Saltar direcciones reservadas (0x00-0x07, 0x78-0x7F)
            if (address < 8 || address > 0x77) {
                printf("   ");
                continue;
            }
            
            // Crear comando I2C
            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            // Enviar dirección con bit de escritura
            i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
            i2c_master_stop(cmd);
            
            // Ejecutar comando y verificar respuesta
            ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
            i2c_cmd_link_delete(cmd);
            
            // Si el dispositivo responde, mostrarlo
            if (ret == ESP_OK) {
                printf(" %02X", address);
                devices_found = true;
                
                // Mostrar información adicional sobre dispositivos conocidos
                if (address == 0x3C || address == 0x3D) {
                    printf("(OLED)");
                } else if (address == 0x68 || address == 0x69) {
                    printf("(RTC/MPU)");
                } else if (address >= 0x50 && address <= 0x57) {
                    printf("(EEPROM)");
                } else {
                    printf("    ");
                }
            } else if (ret == ESP_ERR_TIMEOUT) {
                printf(" --"); // Timeout
            } else {
                printf(" .."); // Error
            }
        }
        printf("\n");
    }
    
    if (!devices_found) {
        printf("\n¡No se encontraron dispositivos I2C!\n");
        printf("Verifica las conexiones y asegúrate de que los dispositivos estén alimentados.\n");
    } else {
        printf("\nEscaneo I2C completado.\n");
    }
}

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    // Inicializar el controlador I2C
    esp_err_t ret = i2c_master_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al inicializar I2C: %s", esp_err_to_name(ret));
        return;
    }
    
    ESP_LOGI(TAG, "Ejemplo de escáner I2C iniciado");
    ESP_LOGI(TAG, "Pines: SDA=GPIO%d, SCL=GPIO%d", I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO);
    
    // Realizar el escaneo I2C
    i2c_scan();
    
    // No es necesario mantener el controlador I2C activo
    i2c_driver_delete(I2C_MASTER_NUM);
    ESP_LOGI(TAG, "Controlador I2C liberado");
    
    // El programa termina aquí, pero el bucle principal debe seguir ejecutándose
    while (1) {
        vTaskDelay(portMAX_DELAY); // Dormir indefinidamente
    }
}