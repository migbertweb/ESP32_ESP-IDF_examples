/**
 * Archivo: main.c
 * Descripción: Ejemplo de temporizador con interrupción en ESP32.
 *              Utiliza el temporizador de hardware para incrementar un contador
 *              periódicamente y mostrarlo por el puerto serie.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo configurar y utilizar el temporizador de hardware
 *      del ESP32 para generar interrupciones periódicas sin bloquear el bucle principal.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"

// Variable global para el contador
volatile uint16_t count = 0;

/**
 * @brief Función de retrollamada (callback) del temporizador
 * 
 * Esta función se ejecuta cada vez que el temporizador alcanza el tiempo configurado.
 * Incrementa el contador global cada vez que se llama.
 * 
 * @param param Parámetro opcional (no utilizado en este ejemplo)
 */
void timer_callback(void *param)
{
    count++;  // Incrementa el contador cada vez que se llama esta función
}

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    // Configura los parámetros del temporizador
    const esp_timer_create_args_t my_timer_args = 
    {
        .callback = &timer_callback,  // Función a llamar cuando expire el temporizador
        .name = "Timer Interrupt"     // Nombre opcional para depuración
    };

    // Manejador del temporizador
    esp_timer_handle_t timer_handler;
    
    // Crea el temporizador
    esp_err_t err = esp_timer_create(&my_timer_args, &timer_handler);
    if (err != ESP_OK) {
        printf("Error al crear el temporizador: %s\n", esp_err_to_name(err));
        return;
    }

    // Inicia el temporizador periódico (cada 10,000 microsegundos = 10ms)
    err = esp_timer_start_periodic(timer_handler, 10000);
    if (err != ESP_OK) {
        printf("Error al iniciar el temporizador: %s\n", esp_err_to_name(err));
        return;
    }

    printf("Ejemplo de temporizador con interrupción\n");
    printf("El contador se incrementa cada 10ms...\n");

    // Bucle principal
    while(true)
    {
        // Muestra el valor actual del contador
        printf("Contador: %d\n", count);
        
        // Pequeña pausa para no saturar el puerto serie
        vTaskDelay(100 / portTICK_PERIOD_MS);  // 100ms de retraso
    }
    
    // Nota: En una aplicación real, deberías limpiar el temporizador al salir
    // esp_timer_stop(timer_handler);
    // esp_timer_delete(timer_handler);
}