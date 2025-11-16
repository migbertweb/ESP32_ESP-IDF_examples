/**
 * Archivo: main.c
 * Descripción: Ejemplo de uso del ADC (Convertidor Analógico-Digital) en ESP32.
 *              Lee valores analógicos de un pin ADC y los muestra por el puerto serie.
 *              Utiliza el canal ADC1_CHANNEL_0 (GPIO36) con una resolución de 12 bits.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo configurar y leer valores de un pin analógico
 *      en el ESP32, útil para leer sensores analógicos como potenciómetros, 
 *      sensores de luz, etc.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_log.h"

// Variable para almacenar el valor leído del ADC
int adc_value = 0;

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    // Configura la atenuación del canal ADC
    // ADC_ATTEN_DB_11 permite leer hasta aproximadamente 3.1V con buena precisión
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    
    // Configura la resolución del ADC a 12 bits (0-4095)
    adc1_config_width(ADC_WIDTH_BIT_12);

    printf("Iniciando ejemplo de ADC...\n");
    printf("Conecta un potenciómetro o sensor analógico a GPIO36 (ADC1_CHANNEL_0)\n");
    printf("Valor del ADC (0-4095):\n");

    // Bucle principal
    while(true)
    {
        // Lee el valor crudo del ADC (0-4095)
        adc_value = adc1_get_raw(ADC1_CHANNEL_0);
        
        // Muestra el valor leído
        printf("Valor ADC: %d\n", adc_value);

        // Pequeña pausa para no saturar el puerto serie
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}