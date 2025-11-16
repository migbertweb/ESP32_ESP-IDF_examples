/**
 * Archivo: main.c
 * Descripción: Ejemplo de interrupción por GPIO en ESP32 usando ESP-IDF.
 *              Detecta flancos de subida en un pin configurado como entrada
 *              con interrupción y lleva la cuenta de las veces que se activa.
 *              El contador se muestra por el puerto serie.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo configurar y manejar interrupciones por hardware
 *      en el ESP32, lo que es útil para eventos que requieren respuesta inmediata.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "inttypes.h"

// Definición del pin de interrupción
#define INTERRUPT_PIN  5

// Variables globales
volatile uint16_t interrupt_count = 0;  // Contador de interrupciones
volatile bool button_state = false;     // Estado del botón (para manejo en el bucle principal)

/**
 * @brief Manejador de la interrupción (ISR)
 * 
 * Esta función se ejecuta cuando se detecta un flanco de subida en el pin de interrupción.
 * El atributo IRAM_ATTR asegura que la función se cargue en la RAM interna para
 * un acceso más rápido y para que esté disponible incluso cuando la caché esté deshabilitada.
 * 
 * @param arg Argumento opcional (no utilizado en este ejemplo)
 */
static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    // Incrementa el contador de interrupciones
    interrupt_count++;
    // Activa la bandera para indicar que hubo una interrupción
    button_state = true;
    
    // Vuelve a registrar el manejador de interrupción (necesario en algunas versiones de ESP-IDF)
    gpio_isr_handler_add(INTERRUPT_PIN, gpio_isr_handler, NULL);
    // Vuelve a habilitar la interrupción
    gpio_intr_enable(INTERRUPT_PIN);
}

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    // Inicializa el pin de interrupción
    gpio_reset_pin(INTERRUPT_PIN);
    // Configura el pin como entrada
    gpio_set_direction(INTERRUPT_PIN, GPIO_MODE_INPUT);
    // Habilita la resistencia pull-up interna
    gpio_set_pull_mode(INTERRUPT_PIN, GPIO_PULLUP_ONLY);
    // Configura la interrupción para que se active en flanco de subida
    gpio_set_intr_type(INTERRUPT_PIN, GPIO_INTR_POSEDGE);

    // Instala el servicio de interrupciones de GPIO
    // El parámetro es el nivel de prioridad (0 es la prioridad más alta)
    gpio_install_isr_service(0);
    
    // Asocia el manejador de interrupción al pin
    gpio_isr_handler_add(INTERRUPT_PIN, gpio_isr_handler, NULL);
    // Habilita la interrupción
    gpio_intr_enable(INTERRUPT_PIN);

    printf("Ejemplo de interrupción por GPIO\n");
    printf("Presiona el botón conectado al pin %d...\n", INTERRUPT_PIN);

    // Bucle principal
    while(1)
    {
        // Si se detectó una interrupción
        if(button_state == true)
        {
            // Muestra el contador de interrupciones
            printf("Interrupciones detectadas: %d\n", interrupt_count);
            // Reinicia la bandera
            button_state = false;
        }
        
        // Pequeña pausa para reducir el uso de CPU
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}