/**
 * Archivo: main.c
 * Descripción: Ejemplo de generación de señal PWM en ESP32 usando el módulo LEDC.
 *              Controla la intensidad de un LED mediante modulación por ancho de pulso (PWM)
 *              con un efecto de atenuación gradual (fade) continuo.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo configurar el módulo LEDC del ESP32 para generar
 *      señales PWM y controlar la intensidad de un LED con un efecto de atenuación.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"

// Configuración del temporizador PWM
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (2)     // Pin GPIO para el LED
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_8_BIT  // Resolución de 8 bits (0-255)
#define LEDC_FREQUENCY          (5000)  // Frecuencia en Hz (5kHz)

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    // Configuración del temporizador PWM
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,          // Modo de velocidad
        .duty_resolution  = LEDC_DUTY_RES,     // Resolución de 8 bits (0-255)
        .timer_num        = LEDC_TIMER,         // Número de temporizador
        .freq_hz          = LEDC_FREQUENCY,    // Frecuencia de la señal PWM
        .clk_cfg          = LEDC_AUTO_CLK      // Configuración automática del reloj
    };
    
    // Aplicar configuración del temporizador
    esp_err_t ret = ledc_timer_config(&ledc_timer);
    if (ret != ESP_OK) {
        ESP_LOGE("PWM", "Error al configurar el temporizador: %s", esp_err_to_name(ret));
        return;
    }

    // Configuración del canal PWM
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,           // Modo de velocidad
        .channel       = LEDC_CHANNEL,         // Canal PWM
        .timer_sel     = LEDC_TIMER,           // Temporizador a usar
        .intr_type     = LEDC_INTR_DISABLE,    // Sin interrupciones
        .gpio_num      = LEDC_OUTPUT_IO,       // Pin de salida (GPIO2)
        .duty          = 0,                    // Ciclo de trabajo inicial (0%)
        .hpoint        = 0                     // Punto de activación (no usado en este caso)
    };

    // Configurar el canal PWM
    ret = ledc_channel_config(&ledc_channel);
    if (ret != ESP_OK) {
        ESP_LOGE("PWM", "Error al configurar el canal: %s", esp_err_to_name(ret));
        return;
    }

    // Instalar la función de atenuación (fade)
    ret = ledc_fade_func_install(0);
    if (ret != ESP_OK) {
        ESP_LOGE("PWM", "Error al instalar la función de atenuación: %s", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI("PWM", "Ejemplo de PWM iniciado. El LED en GPIO%d se atenuará gradualmente.", LEDC_OUTPUT_IO);

    // Bucle principal para el efecto de atenuación
    while (1) {
        // Aumentar gradualmente el brillo (fade in)
        for (int duty = 0; duty < 255; duty++) {
            // Establecer el ciclo de trabajo y actualizar inmediatamente
            ledc_set_duty_and_update(LEDC_MODE, LEDC_CHANNEL, duty, 0);
            // Pequeña pausa para el efecto de atenuación
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }

        // Disminuir gradualmente el brillo (fade out)
        for (int duty = 255; duty > 0; duty--) {
            // Establecer el ciclo de trabajo y actualizar inmediatamente
            ledc_set_duty_and_update(LEDC_MODE, LEDC_CHANNEL, duty, 0);
            // Pequeña pausa para el efecto de atenuación
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
}