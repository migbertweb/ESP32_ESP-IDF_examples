/**
 * Archivo: main.c
 * Descripción: Ejemplo básico de parpadeo de LED en ESP32 usando ESP-IDF.
 *              Hace parpadear un LED conectado al pin GPIO2 con un intervalo de 1 segundo.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo demuestra el control básico de GPIO en el ESP32.
 *      El LED integrado en la placa (conectado al pin 2) parpadeará cada segundo.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Definición del pin del LED
// En la mayoría de placas ESP32, el LED integrado está en el pin 2
#define LED_PIN 2

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    // Inicializa el pin del LED
    gpio_reset_pin(LED_PIN);
    // Configura el pin como salida
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // Bucle principal
    while(1)
    {
        // Enciende el LED
        gpio_set_level(LED_PIN, true);
        // Espera 1000ms (1 segundo)
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        // Apaga el LED
        gpio_set_level(LED_PIN, false);
        // Espera 1000ms (1 segundo)
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}