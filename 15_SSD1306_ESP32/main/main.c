/**
 * Archivo: main.c
 * Descripción: Ejemplo de control de pantalla OLED SSD1306 con ESP32.
 *              Este código muestra mensajes de ejemplo en una pantalla OLED
 *              monocromática de 128x64 píxeles con controlador SSD1306.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo inicializar y mostrar texto en una pantalla
 *      OLED SSD1306 conectada a través de I2C.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ssd1306.h"

// Etiqueta para mensajes de log
static const char *TAG = "SSD1306_EXAMPLE";

// Tiempo de actualización de la pantalla (ms)
#define DISPLAY_UPDATE_INTERVAL_MS 3000

/**
 * @brief Muestra una pantalla de bienvenida en el display OLED
 */
static void show_welcome_screen(void)
{
    // Limpiar el búfer de la pantalla
    ssd1306_clear();
    
    // Mostrar mensaje de bienvenida centrado
    ssd1306_print_str(18, 0, "Hello World!", false);
    ssd1306_print_str(18, 17, "SSD1306 OLED", false);
    ssd1306_print_str(28, 27, "with ESP32", false);
    ssd1306_print_str(38, 37, "ESP-IDF", false);
    ssd1306_print_str(28, 47, "Embedded C", false);
    
    // Actualizar la pantalla
    ssd1306_display();
    
    ESP_LOGI(TAG, "Pantalla de bienvenida mostrada");
}

/**
 * @brief Muestra información del sistema en el display OLED
 */
static void show_system_info(void)
{
    char info_str[32];
    
    // Limpiar el búfer de la pantalla
    ssd1306_clear();
    
    // Mostrar información del sistema
    ssd1306_print_str(0, 0, "ESP32 SSD1306 Demo", false);
    
    // Línea divisoria
    for (int i = 0; i < 128; i++) {
        ssd1306_draw_pixel(i, 10, true);
    }
    
    // Mostrar información de ejemplo
    ssd1306_print_str(0, 15, "Temp: 25.5 C", false);
    ssd1306_print_str(0, 25, "Humedad: 45%", false);
    ssd1306_print_str(0, 35, "Uptime: 00:05:30", false);
    
    // Actualizar la pantalla
    ssd1306_display();
    
    ESP_LOGI(TAG, "Información del sistema mostrada");
}

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    ESP_LOGI(TAG, "Iniciando ejemplo de pantalla OLED SSD1306");
    
    // Inicializar la pantalla OLED
    esp_err_t ret = init_ssd1306();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al inicializar la pantalla OLED: %s", esp_err_to_name(ret));
        vTaskDelay(portMAX_DELAY);
    }
    
    ESP_LOGI(TAG, "Pantalla OLED inicializada correctamente");
    
    // Bucle principal
    while (1) {
        // Mostrar pantalla de bienvenida
        show_welcome_screen();
        vTaskDelay(DISPLAY_UPDATE_INTERVAL_MS / portTICK_PERIOD_MS);
        
        // Mostrar información del sistema
        show_system_info();
        vTaskDelay(DISPLAY_UPDATE_INTERVAL_MS / portTICK_PERIOD_MS);
        
        // Aquí puedes agregar más pantallas o funcionalidades
    }
}

/**
 * @brief Función para mostrar un gráfico de barras en la pantalla
 * 
 * @param values Array de valores a mostrar (0-100%)
 * @param num_values Número de valores en el array (máx 8 para 128x64)
 */
void show_bar_graph(const uint8_t *values, uint8_t num_values)
{
    if (values == NULL || num_values == 0 || num_values > 16) {
        ESP_LOGE(TAG, "Parámetros inválidos para gráfico de barras");
        return;
    }
    
    const uint8_t bar_width = 6;  // Ancho de cada barra en píxeles
    const uint8_t spacing = 2;    // Espacio entre barras
    const uint8_t max_height = 40; // Altura máxima de las barras
    
    // Limpiar el área del gráfico
    for (uint8_t y = 10; y < 60; y++) {
        for (uint8_t x = 0; x < 128; x++) {
            ssd1306_draw_pixel(x, y, false);
        }
    }
    
    // Dibujar ejes
    for (uint8_t x = 0; x < 128; x++) {
        ssd1306_draw_pixel(x, 58, true);  // Eje X
    }
    
    // Dibujar barras
    for (uint8_t i = 0; i < num_values; i++) {
        uint8_t bar_height = (values[i] * max_height) / 100;
        if (bar_height > max_height) bar_height = max_height;
        
        uint8_t x_pos = i * (bar_width + spacing) + 2;
        
        // Asegurarse de que las barras no se salgan de la pantalla
        if (x_pos + bar_width >= 128) break;
        
        // Dibujar la barra
        for (uint8_t x = 0; x < bar_width; x++) {
            for (uint8_t y = 0; y < bar_height; y++) {
                ssd1306_draw_pixel(x_pos + x, 58 - y, true);
            }
        }
        
        // Mostrar el valor numérico debajo de la barra
        char val_str[4];
        snprintf(val_str, sizeof(val_str), "%d", values[i]);
        ssd1306_print_str(x_pos, 60, val_str, false);
    }
    
    // Actualizar la pantalla
    ssd1306_display();
}