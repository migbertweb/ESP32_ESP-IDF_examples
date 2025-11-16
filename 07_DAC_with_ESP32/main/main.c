/**
 * Archivo: main.c
 * Descripción: Ejemplo de uso del Convertidor Digital-Analógico (DAC) del ESP32.
 *              Genera una señal de rampa en el canal 1 del DAC (GPIO25) que varía
 *              continuamente entre 0V y 3.3V.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo configurar y utilizar el DAC del ESP32 para generar
 *      señales analógicas. La salida puede visualizarse con un osciloscopio o medirse
 *      con un multímetro.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/dac.h"
#include "esp_err.h"
#include "esp_log.h"

// Configuración del DAC
#define DAC_CHANNEL         DAC_CHANNEL_1    // Usar canal 1 (GPIO25)
#define DAC_RAMP_DELAY_MS   50               // Retardo entre pasos de la rampa (ms)

// Etiqueta para mensajes de log
static const char *TAG = "DAC_EXAMPLE";

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    ESP_LOGI(TAG, "Iniciando ejemplo de DAC en el canal %d", (int)DAC_CHANNEL + 1);
    
    // Habilitar el canal del DAC
    esp_err_t ret = dac_output_enable(DAC_CHANNEL);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al habilitar el DAC: %s", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(TAG, "Generando señal de rampa en el DAC...");
    ESP_LOGI(TAG, "Conecta un osciloscopio o multímetro a GPIO25 para ver la señal");

    // Bucle principal
    while (1) {
        // Generar rampa ascendente (0 a 255)
        for (int value = 0; value <= 255; value++) {
            // Establecer el valor de salida del DAC
            ret = dac_output_voltage(DAC_CHANNEL, value);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "Error al establecer el voltaje del DAC: %s", esp_err_to_name(ret));
                continue;
            }
            
            // Mostrar el valor actual en el monitor serie
            printf("Valor DAC: %d (%.2fV)\n", value, (value / 255.0f) * 3.3f);
            
            // Pequeña pausa para el efecto de rampa
            vTaskDelay(DAC_RAMP_DELAY_MS / portTICK_PERIOD_MS);
        }

        // Generar rampa descendente (255 a 1)
        for (int value = 255; value > 0; value--) {
            // Establecer el valor de salida del DAC
            ret = dac_output_voltage(DAC_CHANNEL, value);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "Error al establecer el voltaje del DAC: %s", esp_err_to_name(ret));
                continue;
            }
            
            // Mostrar el valor actual en el monitor serie
            printf("Valor DAC: %d (%.2fV)\n", value, (value / 255.0f) * 3.3f);
            
            // Pequeña pausa para el efecto de rampa
            vTaskDelay(DAC_RAMP_DELAY_MS / portTICK_PERIOD_MS);
        }
    }
}