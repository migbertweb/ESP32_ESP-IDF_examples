/**
 * Archivo: main.c
 * Descripción: Ejemplo de control de pantalla LCD 16x2 con interfaz I2C usando ESP32.
 *              Este código muestra mensajes de ejemplo en una pantalla LCD 16x2
 *              a través de un adaptador I2C (generalmente PCF8574).
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo inicializar y mostrar texto en una pantalla LCD 16x2
 *      conectada a través de I2C.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include <string.h>
#include "driver/i2c.h"
#include "i2c_lcd.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Etiqueta para mensajes de log
static const char *TAG = "LCD_16x2";

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    ESP_LOGI(TAG, "Iniciando ejemplo de LCD 16x2 con I2C");
    
    // Inicializar la pantalla LCD
    esp_err_t ret = lcd_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al inicializar la pantalla LCD: %s", esp_err_to_name(ret));
        vTaskDelay(portMAX_DELAY);
    }
    
    // Limpiar la pantalla LCD
    lcd_clear();
    
    // Mostrar mensaje en la primera línea
    lcd_put_cursor(0, 0);
    lcd_send_string("Hola, ESP32!");
    
    // Mostrar mensaje en la segunda línea
    lcd_put_cursor(1, 0);
    lcd_send_string("LCD 16x2 I2C");
    
    ESP_LOGI(TAG, "Mensajes mostrados en la pantalla LCD");
    
    // Bucle principal (no se sale de la función app_main)
    while (1) {
        // Aquí podrías actualizar la pantalla periódicamente si fuera necesario
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Función para mostrar un mensaje de bienvenida personalizado
 * 
 * @param nombre Nombre a mostrar en el mensaje de bienvenida
 */
void mostrar_bienvenida(const char *nombre)
{
    char mensaje[17];  // 16 caracteres + carácter nulo
    
    // Limitar la longitud del nombre para que quepa en la pantalla
    strncpy(mensaje, nombre, 16);
    mensaje[16] = '\0';
    
    // Mostrar mensaje de bienvenida
    lcd_clear();
    lcd_put_cursor(0, 0);
    lcd_send_string("Bienvenido:");
    lcd_put_cursor(1, 0);
    lcd_send_string(mensaje);
    
    ESP_LOGI(TAG, "Mensaje de bienvenida mostrado para: %s", nombre);
}

/**
 * @brief Función para mostrar la hora actual en la pantalla LCD
 * 
 * @param hora Puntero a la estructura tm con la hora actual
 */
void mostrar_hora(const struct tm *hora)
{
    char tiempo[17];  // Formato: "HH:MM:SS DD/MM/YY"
    
    if (hora == NULL) {
        ESP_LOGE(TAG, "Error: Puntero a hora nulo");
        return;
    }
    
    // Formatear la hora y fecha
    snprintf(tiempo, sizeof(tiempo), "%02d:%02d:%02d %02d/%02d/%02d",
             hora->tm_hour, hora->tm_min, hora->tm_sec,
             hora->tm_mday, hora->tm_mon + 1, hora->tm_year % 100);
    
    // Mostrar en la segunda línea
    lcd_put_cursor(1, 0);
    lcd_send_string(tiempo);
}
