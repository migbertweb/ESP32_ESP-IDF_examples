/**
 * Archivo: main.c
 * Descripción: Ejemplo de comunicación SPI en modo maestro con ESP32.
 *              Configura el periférico SPI2 para enviar datos periódicamente
 *              a un dispositivo esclavo y muestra los datos recibidos.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo configurar y utilizar el periférico SPI
 *      del ESP32 en modo maestro para comunicación con dispositivos esclavos.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

// Configuración de pines SPI
#define PIN_NUM_MOSI   12  // Master Output, Slave Input
#define PIN_NUM_MISO   13  // Master Input, Slave Output
#define PIN_NUM_CLK    15  // Reloj SPI
#define PIN_NUM_CS     14  // Selección de Chip (Chip Select)

// Configuración del bus SPI
#define SPI_HOST        SPI2_HOST  // Usar el controlador SPI2
#define DMA_CHAN        SPI_DMA_CH_AUTO  // Canal DMA automático
#define CLOCK_SPEED_HZ  1000000    // 1 MHz
#define QUEUE_SIZE      1          // Tamaño de la cola de transacciones

// Tamaño de los búferes de transmisión/recepción
#define BUF_SIZE        128

// Etiqueta para mensajes de log
static const char *TAG = "SPI_MASTER";

/**
 * @brief Inicializa el controlador SPI en modo maestro
 * 
 * @param handle Puntero al manejador del dispositivo SPI
 * @return esp_err_t Código de error ESP_OK si es exitoso
 */
static esp_err_t init_spi_master(spi_device_handle_t *handle)
{
    esp_err_t ret;
    
    // Configuración del bus SPI
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,  // Pin MISO
        .mosi_io_num = PIN_NUM_MOSI,  // Pin MOSI
        .sclk_io_num = PIN_NUM_CLK,   // Pin de reloj
        .quadwp_io_num = -1,          // No se usa en modo estándar
        .quadhd_io_num = -1,          // No se usa en modo estándar
        .max_transfer_sz = BUF_SIZE   // Tamaño máximo de transferencia
    };
    
    // Configuración del dispositivo SPI
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = CLOCK_SPEED_HZ,  // Velocidad del reloj
        .mode = 0,                         // Modo 0: CPOL=0, CPHA=0
        .spics_io_num = PIN_NUM_CS,        // Pin de selección de chip
        .queue_size = QUEUE_SIZE,          // Tamaño de la cola de transacciones
        .flags = 0,                        // Sin banderas especiales
        .duty_cycle_pos = 128,             // Ciclo de trabajo del reloj (128 = 50%)
        .cs_ena_pretrans = 0,              // Tiempo de pre-transmisión del CS
        .cs_ena_posttrans = 0,             // Tiempo de post-transmisión del CS
    };
    
    // Inicializar el bus SPI
    ret = spi_bus_initialize(SPI_HOST, &buscfg, DMA_CHAN);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al inicializar el bus SPI: %s", esp_err_to_name(ret));
        return ret;
    }
    
    // Añadir el dispositivo SPI al bus
    ret = spi_bus_add_device(SPI_HOST, &devcfg, handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al agregar el dispositivo SPI: %s", esp_err_to_name(ret));
        spi_bus_free(SPI_HOST);  // Liberar el bus en caso de error
        return ret;
    }
    
    ESP_LOGI(TAG, "SPI inicializado correctamente");
    return ESP_OK;
}

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    esp_err_t ret;
    spi_device_handle_t spi_handle;
    
    // Inicializar el controlador SPI
    ret = init_spi_master(&spi_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al inicializar el SPI. Reiniciando...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        esp_restart();
    }
    
    // Búferes para transmisión y recepción
    uint8_t sendbuf[BUF_SIZE] = {0};
    uint8_t recvbuf[BUF_SIZE] = {0};
    
    // Configuración de la transacción SPI
    spi_transaction_t trans = {
        .length = 0,  // Se establecerá más adelante
        .tx_buffer = sendbuf,
        .rx_buffer = recvbuf
    };
    
    ESP_LOGI(TAG, "Ejemplo de comunicación SPI iniciado");
    ESP_LOGI(TAG, "Enviando datos cada segundo...");
    
    // Bucle principal
    while (1) {
        // Preparar el mensaje a enviar
        int msg_len = snprintf((char *)sendbuf, sizeof(sendbuf), "Hi I am from ESP32 - %lld", esp_timer_get_time() / 1000000);
        
        // Configurar la longitud de la transacción en bits
        trans.length = msg_len * 8;
        
        // Realizar la transacción SPI
        ret = spi_device_transmit(spi_handle, &trans);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Error en la transmisión SPI: %s", esp_err_to_name(ret));
        } else {
            // Mostrar los datos transmitidos y recibidos
            ESP_LOGI(TAG, "Transmitido: %.*s", msg_len, sendbuf);
            
            // Verificar si se recibieron datos
            bool data_received = false;
            for (int i = 0; i < msg_len; i++) {
                if (recvbuf[i] != 0) {
                    data_received = true;
                    break;
                }
            }
            
            if (data_received) {
                ESP_LOGI(TAG, "Recibido: %.*s", msg_len, recvbuf);
            } else {
                ESP_LOGI(TAG, "No se recibieron datos del esclavo");
            }
        }
        
        // Limpiar los búferes para la próxima iteración
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
        
        // Esperar antes de la próxima transmisión
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    // Nota: En una aplicación real, deberías limpiar los recursos al salir
    // spi_bus_remove_device(spi_handle);
    // spi_bus_free(SPI_HOST);
}