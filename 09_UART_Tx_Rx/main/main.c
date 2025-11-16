/**
 * Archivo: main.c
 * Descripción: Ejemplo de comunicación UART bidireccional en ESP32.
 *              Envía mensajes periódicamente por UART2 y está preparado
 *              para recibir y mostrar datos entrantes.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo configurar y utilizar el periférico UART
 *      del ESP32 para comunicación serie bidireccional.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "sdkconfig.h"

// Configuración de pines UART
#define ECHO_TEST_TXD  (17)  // Pin TX (transmisión)
#define ECHO_TEST_RXD  (16)  // Pin RX (recepción)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)  // No usar RTS
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)  // No usar CTS

// Configuración del puerto UART
#define ECHO_UART_PORT_NUM      (UART_NUM_2)  // Usar UART2
#define ECHO_UART_BAUD_RATE     (9600)        // Velocidad en baudios
#define ECHO_TASK_STACK_SIZE    (2048)        // Tamaño de pila para tareas
#define BUF_SIZE                (1024)        // Tamaño del búfer de recepción

// Mensaje a enviar
static const char *TAG = "UART_EXAMPLE";
static const char *TX_DATA = "Hi I am from ESP32";

// Búfer para datos recibidos
static uint8_t rx_data[128];

/**
 * @brief Inicializa el periférico UART con la configuración especificada
 */
static void uart_init(void)
{
    // Configuración de parámetros UART
    uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,  // Velocidad en baudios
        .data_bits = UART_DATA_8_BITS,     // 8 bits de datos
        .parity = UART_PARITY_DISABLE,     // Sin paridad
        .stop_bits = UART_STOP_BITS_1,     // 1 bit de parada
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,  // Sin control de flujo
        .source_clk = UART_SCLK_APB,       // Reloj de APB
    };

    ESP_LOGI(TAG, "Configurando UART...");
    
    // Configurar parámetros UART
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
    
    // Configurar pines UART
    ESP_ERROR_CHECK(uart_set_pin(
        ECHO_UART_PORT_NUM,
        ECHO_TEST_TXD,
        ECHO_TEST_RXD,
        ECHO_TEST_RTS,
        ECHO_TEST_CTS
    ));
    
    // Instalar el driver UART
    ESP_ERROR_CHECK(uart_driver_install(
        ECHO_UART_PORT_NUM,  // Puerto UART
        BUF_SIZE * 2,        // Tamaño del búfer de recepción
        0,                   // Tamaño del búfer de transmisión (0 para no usar)
        0,                   // Tamaño de la cola de eventos (0 para no usar)
        NULL,                // Cola de eventos (NULL para no usar)
        0                    // Flags (0 para ninguno)
    ));
    
    ESP_LOGI(TAG, "UART configurado correctamente");
    ESP_LOGI(TAG, "Enviando datos por TX: %s", TX_DATA);
}

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    // Inicializar UART
    uart_init();
    
    ESP_LOGI(TAG, "Ejemplo de comunicación UART iniciado");
    ESP_LOGI(TAG, "Conecta los pines TX(%d) y RX(%d) a otro dispositivo UART", 
             ECHO_TEST_TXD, ECHO_TEST_RXD);
    ESP_LOGI(TAG, "Los datos recibidos se mostrarán en el monitor serie");

    // Bucle principal
    while (1) {
        // Enviar datos por UART
        uart_write_bytes(ECHO_UART_PORT_NUM, TX_DATA, strlen(TX_DATA));
        
        // Leer datos del búfer de recepción
        int len = uart_read_bytes(
            ECHO_UART_PORT_NUM,  // Puerto UART
            rx_data,             // Búfer de destino
            sizeof(rx_data) - 1, // Tamaño máximo a leer
            pdMS_TO_TICKS(5)     // Tiempo de espera (5ms)
        );
        
        // Si se recibieron datos, mostrarlos
        if (len > 0) {
            rx_data[len] = '\0';  // Terminar la cadena
            printf("Bytes recibidos: %d, Datos: %s\n", len, rx_data);
            fflush(stdout);  // Asegurar que los datos se envíen inmediatamente
        }
        
        // Pequeña pausa antes del próximo envío
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}