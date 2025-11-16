/**
 * Archivo: main.c
 * Descripción: Ejemplo de uso del sensor de efecto Hall integrado en el ESP32.
 *              Lee el valor del sensor y controla un LED en función de la
 *              intensidad del campo magnético detectado.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo leer el sensor de efecto Hall integrado
 *      en el ESP32 y cómo reaccionar a cambios en el campo magnético.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include <inttypes.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// Configuración de pines
#define LED_PIN              GPIO_NUM_12  // Pin para el LED
#define HALL_THRESHOLD       100          // Umbral para activar el LED
#define SAMPLE_DELAY_MS      100          // Retardo entre lecturas

// Declaración de la función del sensor Hall (definida en la ROM del ESP32)
int hall_sens_read(void);

// Variable para almacenar el valor del sensor
uint32_t hall_sensor_value = 0;

// Etiqueta para mensajes de log
static const char *TAG = "HALL_SENSOR";

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    ESP_LOGI(TAG, "Iniciando ejemplo de sensor de efecto Hall");
    
    // Configuración del pin del LED
    esp_err_t ret = gpio_reset_pin(LED_PIN);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al reiniciar el pin del LED: %s", esp_err_to_name(ret));
        return;
    }
    
    ret = gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al configurar el pin del LED: %s", esp_err_to_name(ret));
        return;
    }
    
    ESP_LOGI(TAG, "Acerca un imán al ESP32 para ver cómo cambian los valores");
    ESP_LOGI(TAG, "El LED se encenderá cuando el valor sea menor a %d", HALL_THRESHOLD);

    // Bucle principal
    while (true) {
        // Leer el valor del sensor Hall
        hall_sensor_value = hall_sens_read();
        
        // Mostrar el valor en el monitor serie
        printf("Valor del sensor Hall: %" PRIu32 "\n", hall_sensor_value);

        // Controlar el LED según el valor del sensor
        if (hall_sensor_value < HALL_THRESHOLD) {
            // Encender el LED si el valor está por debajo del umbral
            gpio_set_level(LED_PIN, 1);
            ESP_LOGD(TAG, "Campo magnético detectado! (Valor: %" PRIu32 ")", hall_sensor_value);
        } else {
            // Apagar el LED en caso contrario
            gpio_set_level(LED_PIN, 0);
        }
        
        // Pequeña pausa entre lecturas
        vTaskDelay(SAMPLE_DELAY_MS / portTICK_PERIOD_MS);
    }
}