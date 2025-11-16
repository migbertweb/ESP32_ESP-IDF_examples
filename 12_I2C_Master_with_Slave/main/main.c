/**
 * Archivo: main.c
 * Descripción: Ejemplo de comunicación I2C maestro con un dispositivo esclavo.
 *              Este código configura un ESP32 como maestro I2C que lee datos
 *              de un dispositivo esclavo en la dirección 0x0C.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo configurar un ESP32 como maestro I2C
 *      para leer datos de un dispositivo esclavo.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "sdkconfig.h"

// Configuración de pines I2C
#define I2C_MASTER_SDA_IO           21      // Pin GPIO para SDA
#define I2C_MASTER_SCL_IO           22      // Pin GPIO para SCL
#define I2C_MASTER_NUM             I2C_NUM_0 // Puerto I2C a utilizar
#define I2C_MASTER_FREQ_HZ         10000    // Frecuencia del reloj I2C (10KHz)
#define I2C_MASTER_TX_BUF_DISABLE  0        // Deshabilitar búfer de transmisión
#define I2C_MASTER_RX_BUF_DISABLE  0        // Deshabilitar búfer de recepción
#define I2C_MASTER_TIMEOUT_MS      1000     // Tiempo de espera en milisegundos

// Configuración del dispositivo esclavo
#define I2C_SLAVE_ADDR             0x0C    // Dirección del dispositivo esclavo
#define I2C_DATA_LEN               14      // Longitud de los datos a leer

// Búfer para almacenar los datos recibidos
static uint8_t i2c_rx_buffer[I2C_DATA_LEN + 1] = {0}; // +1 para el carácter nulo

// Etiqueta para mensajes de log
static const char *TAG = "I2C_MASTER";

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
        conf.mode,                   // Modo maestro
        I2C_MASTER_RX_BUF_DISABLE,   // Tamaño del búfer de recepción
        I2C_MASTER_TX_BUF_DISABLE,   // Tamaño del búfer de transmisión
        0                            // Flags (0 para ninguno)
    );
    
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al instalar el controlador I2C: %s", esp_err_to_name(ret));
        return ret;
    }
    
    ESP_LOGI(TAG, "Controlador I2C inicializado correctamente");
    ESP_LOGI(TAG, "Buscando dispositivo esclavo en la dirección 0x%02X", I2C_SLAVE_ADDR);
    return ESP_OK;
}

/**
 * @brief Lee datos del dispositivo esclavo I2C
 * 
 * @param data Búfer para almacenar los datos leídos
 * @param size Tamaño del búfer de datos
 * @return esp_err_t Código de error ESP_OK si es exitoso
 */
static esp_err_t i2c_master_read_slave(uint8_t *data, size_t size)
{
    if (data == NULL || size == 0) {
        return ESP_ERR_INVALID_ARG;
    }
    
    // Crear un enlace de comandos I2C
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    if (cmd == NULL) {
        ESP_LOGE(TAG, "Error al crear el enlace de comandos I2C");
        return ESP_ERR_NO_MEM;
    }
    
    // Configurar la secuencia de comandos I2C
    i2c_master_start(cmd);
    // Enviar dirección del esclavo con bit de lectura (1)
    i2c_master_write_byte(cmd, (I2C_SLAVE_ADDR << 1) | I2C_MASTER_READ, true);
    // Leer datos del esclavo
    i2c_master_read(cmd, data, size - 1, I2C_MASTER_LAST_NACK); // Último byte con NACK
    i2c_master_stop(cmd);
    
    // Ejecutar la secuencia de comandos I2C
    esp_err_t ret = i2c_master_cmd_begin(
        I2C_MASTER_NUM, 
        cmd, 
        pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)
    );
    
    // Liberar los recursos del enlace de comandos
    i2c_cmd_link_delete(cmd);
    
    if (ret != ESP_OK) {
        ESP_LOGD(TAG, "Error en la comunicación I2C: %s", esp_err_to_name(ret));
        return ret;
    }
    
    // Asegurarse de que la cadena esté terminada en nulo
    data[size - 1] = '\0';
    
    return ESP_OK;
}

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    esp_err_t ret;
    
    // Inicializar el controlador I2C
    ret = i2c_master_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al inicializar I2C. Reiniciando...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        esp_restart();
    }
    
    ESP_LOGI(TAG, "Ejemplo de comunicación I2C Maestro-Esclavo iniciado");
    ESP_LOGI(TAG, "Leyendo %d bytes del esclavo en la dirección 0x%02X cada segundo...", 
             I2C_DATA_LEN, I2C_SLAVE_ADDR);
    
    // Bucle principal
    while (1) {
        // Limpiar el búfer de recepción
        memset(i2c_rx_buffer, 0, sizeof(i2c_rx_buffer));
        
        // Leer datos del esclavo
        ret = i2c_master_read_slave(i2c_rx_buffer, I2C_DATA_LEN);
        
        if (ret == ESP_OK) {
            // Mostrar los datos recibidos
            ESP_LOGI(TAG, "Datos recibidos: %s", i2c_rx_buffer);
            
            // Verificar si los datos son legibles (caracteres imprimibles)
            bool printable = true;
            for (int i = 0; i < I2C_DATA_LEN && i2c_rx_buffer[i] != '\0'; i++) {
                if (i2c_rx_buffer[i] < 32 || i2c_rx_buffer[i] > 126) {
                    printable = false;
                    break;
                }
            }
            
            if (!printable) {
                ESP_LOGW(TAG, "Advertencia: Los datos recibidos contienen caracteres no imprimibles");
                // Mostrar los datos en formato hexadecimal
                printf("Datos en hexadecimal: ");
                for (int i = 0; i < I2C_DATA_LEN; i++) {
                    printf("%02X ", i2c_rx_buffer[i]);
                }
                printf("\n");
            }
        } else if (ret == ESP_ERR_TIMEOUT) {
            ESP_LOGW(TAG, "Tiempo de espera agotado al leer del esclavo");
        } else {
            ESP_LOGE(TAG, "Error al leer del esclavo: %s", esp_err_to_name(ret));
        }
        
        // Esperar antes de la próxima lectura
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    // Nota: En una aplicación real, deberías limpiar los recursos al salir
    // i2c_driver_delete(I2C_MASTER_NUM);
}
