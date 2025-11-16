/**
 * Archivo: main.c
 * Descripción: Ejemplo de lectura de entrada digital en ESP32 usando ESP-IDF.
 *              Lee el estado de un botón conectado a GPIO5 y controla un LED en GPIO2.
 *              Cuando se presiona el botón, el LED se enciende; al soltarlo, se apaga.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo leer una entrada digital y controlar una salida
 *      en respuesta a dicha entrada.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Definición de pines
#define LED_PIN     2   // Pin del LED (puede ser el integrado)
#define BUTTON_PIN  5   // Pin del botón

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    // Inicialización de pines
    gpio_reset_pin(LED_PIN);
    gpio_reset_pin(BUTTON_PIN);

    // Configura el pin del LED como salida
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // Configura el pin del botón como entrada con resistencia pull-up interna
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);

    // Bucle principal
    while(true)
    {
        // Lee el estado del botón (false = presionado, true = no presionado)
        bool button_state = gpio_get_level(BUTTON_PIN);

        // Controla el LED según el estado del botón
        if(button_state == false)  // Botón presionado (pull-up)
        {
            gpio_set_level(LED_PIN, true);  // Enciende el LED
        }
        else
        {
            gpio_set_level(LED_PIN, false); // Apaga el LED
        }

        // Pequeña pausa para evitar rebotes y reducir el consumo de CPU
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}