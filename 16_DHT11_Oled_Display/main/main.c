/**
 * Archivo: main.c
 * Descripción: Ejemplo de lectura de sensor DHT11 y visualización en pantalla OLED.
 *              Este código lee temperatura y humedad del sensor DHT11 y los muestra
 *              en una pantalla OLED SSD1306 utilizando un ESP32.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo leer datos del sensor DHT11 y mostrarlos en una
 *      pantalla OLED, actualizando solo cuando los valores cambian.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>              // Funciones estándar de E/S
#include <string.h>             // Funciones para manipulación de cadenas
#include <inttypes.h>           // Para tipos de enteros con tamaño específico
#include "esp_log.h"            // Funciones de registro de ESP-IDF
#include "freertos/FreeRTOS.h"  // Definiciones principales de FreeRTOS
#include "freertos/task.h"      // Funciones de tareas de FreeRTOS
#include "dht11.h"              // Controlador del sensor DHT11
#include "ssd1306.h"            // Controlador de pantalla OLED SSD1306

// Etiqueta para mensajes de log
static const char *TAG = "DHT11_OLED_DEMO";

// Configuración de pines
#define CONFIG_DHT11_PIN         GPIO_NUM_4  // Pin de datos del DHT11
#define CONFIG_CONNECTION_TIMEOUT 5          // Tiempo de espera en segundos

// Tiempo entre lecturas (mínimo 2 segundos para DHT11)
#define READ_INTERVAL_MS          2000

// Tamaño de búfer para cadenas de texto
#define STR_BUF_SIZE             32

// Valores inválidos iniciales
#define INVALID_TEMP_HUM         0xFF

/**
 * @brief Inicializa los periféricos necesarios
 */
static void init_hardware(void)
{
    ESP_LOGI(TAG, "Inicializando hardware...");
    
    // Inicializar la pantalla OLED
    esp_err_t ret = init_ssd1306();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al inicializar la pantalla OLED: %s", 
                esp_err_to_name(ret));
        vTaskDelay(portMAX_DELAY);
    }
    
    // Mostrar mensaje de inicio
    ssd1306_clear();
    ssd1306_print_str(10, 10, "Iniciando...", false);
    ssd1306_display();
    
    ESP_LOGI(TAG, "Hardware inicializado correctamente");
}

/**
 * @brief Muestra los valores de temperatura y humedad en la pantalla OLED
 * 
 * @param temperature Temperatura a mostrar
 * @param humidity Humedad a mostrar
 */
static void update_display(float temperature, float humidity)
{
    char temp_str[STR_BUF_SIZE];
    char hum_str[STR_BUF_SIZE];
    
    // Formatear cadenas con una posición decimal
    snprintf(temp_str, sizeof(temp_str), "Temp: %.1f C", temperature);
    snprintf(hum_str, sizeof(hum_str), "Humedad: %.1f%%", humidity);
    
    // Limpiar la pantalla
    ssd1306_clear();
    
    // Mostrar título
    ssd1306_print_str(15, 5, "DHT11 + OLED", false);
    
    // Dibujar línea divisoria
    for (int i = 0; i < 128; i++) {
        ssd1306_draw_pixel(i, 15, true);
    }
    
    // Mostrar valores
    ssd1306_print_str(10, 25, temp_str, false);
    ssd1306_print_str(10, 40, hum_str, false);
    
    // Actualizar la pantalla
    ssd1306_display();
    
    ESP_LOGI(TAG, "%s | %s", temp_str, hum_str);
}

/**
 * @brief Función principal de la aplicación
 */
void app_main()
{
    // Inicializar hardware
    init_hardware();
    
    // Inicializar estructura del sensor DHT11
    dht11_t dht11_sensor = {
        .dht11_pin = CONFIG_DHT11_PIN,
        .temperature = 0,
        .humidity = 0
    };
    
    // Variables para almacenar lecturas previas
    static float prev_temp = INVALID_TEMP_HUM;
    static float prev_hum = INVALID_TEMP_HUM;
    
    ESP_LOGI(TAG, "Iniciando bucle principal...");
    
    // Bucle principal
    while (1) {
        // Leer valores del sensor DHT11
        if (dht11_read(&dht11_sensor, CONFIG_CONNECTION_TIMEOUT) == 0) {
            // Lectura exitosa
            float curr_temp = dht11_sensor.temperature;
            float curr_hum = dht11_sensor.humidity;
            
            // Verificar si los valores son válidos y han cambiado
            if ((curr_temp != prev_temp || curr_hum != prev_hum) &&
                curr_temp >= 0 && curr_temp <= 50 &&  // Rango típico DHT11
                curr_hum >= 20 && curr_hum <= 90) {    // Rango típico DHT11
                
                // Actualizar pantalla con los nuevos valores
                update_display(curr_temp, curr_hum);
                
                // Guardar valores actuales como previos
                prev_temp = curr_temp;
                prev_hum = curr_hum;
            }
        } else {
            // Error en la lectura
            ESP_LOGW(TAG, "Error al leer el sensor DHT11");
            
            // Mostrar mensaje de error en la pantalla
            ssd1306_clear();
            ssd1306_print_str(10, 20, "Error de lectura", false);
            ssd1306_print_str(10, 35, "del sensor DHT11", false);
            ssd1306_display();
        }
        
        // Esperar antes de la siguiente lectura
        vTaskDelay(pdMS_TO_TICKS(READ_INTERVAL_MS));
    }
}

/**
 * @brief Función para mostrar un gráfico de tendencia de temperatura
 * 
 * @param values Array de valores de temperatura
 * @param num_values Número de valores en el array
 * @param min_temp Temperatura mínima para la escala
 * @param max_temp Temperatura máxima para la escala
 */
void show_temperature_trend(const float *values, uint8_t num_values, 
                           float min_temp, float max_temp)
{
    if (values == NULL || num_values == 0 || num_values > 20) {
        ESP_LOGE(TAG, "Parámetros inválidos para gráfico de tendencia");
        return;
    }
    
    const uint8_t graph_width = 120;  // Ancho del gráfico en píxeles
    const uint8_t graph_height = 40;  // Alto del gráfico en píxeles
    const uint8_t graph_x = 4;        // Posición X del gráfico
    const uint8_t graph_y = 15;       // Posición Y del gráfico
    
    // Limpiar el área del gráfico
    for (uint8_t y = graph_y; y < graph_y + graph_height; y++) {
        for (uint8_t x = graph_x; x < graph_x + graph_width; x++) {
            ssd1306_draw_pixel(x, y, false);
        }
    }
    
    // Dibujar ejes
    for (uint8_t x = graph_x; x < graph_x + graph_width; x++) {
        ssd1306_draw_pixel(x, graph_y + graph_height - 1, true);  // Eje X
    }
    for (uint8_t y = graph_y; y < graph_y + graph_height; y++) {
        ssd1306_draw_pixel(graph_x, y, true);  // Eje Y
    }
    
    // Calcular escala
    float temp_range = max_temp - min_temp;
    if (temp_range < 1.0) temp_range = 1.0;  // Evitar división por cero
    
    // Dibujar puntos y líneas de tendencia
    uint8_t prev_x = 0;
    uint8_t prev_y = 0;
    
    for (uint8_t i = 0; i < num_values; i++) {
        // Calcular posición X (distribuida uniformemente)
        uint8_t x = graph_x + (i * (graph_width - 1)) / (num_values - 1);
        
        // Calcular posición Y (escalada al rango del gráfico)
        float norm_temp = (values[i] - min_temp) / temp_range;
        norm_temp = (norm_temp < 0.0) ? 0.0 : (norm_temp > 1.0) ? 1.0 : norm_temp;
        uint8_t y = graph_y + graph_height - 1 - (uint8_t)(norm_temp * (graph_height - 1));
        
        // Dibujar punto
        ssd1306_draw_pixel(x, y, true);
        
        // Dibujar línea desde el punto anterior (excepto para el primer punto)
        if (i > 0) {
            // Algoritmo de línea de Bresenham para dibujar líneas suaves
            int16_t dx = abs(x - prev_x);
            int16_t dy = abs(y - prev_y);
            int16_t sx = (prev_x < x) ? 1 : -1;
            int16_t sy = (prev_y < y) ? 1 : -1;
            int16_t err = dx - dy;
            
            while (1) {
                ssd1306_draw_pixel(prev_x, prev_y, true);
                
                if (prev_x == x && prev_y == y) break;
                
                int16_t e2 = 2 * err;
                if (e2 > -dy) {
                    err -= dy;
                    prev_x += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    prev_y += sy;
                }
            }
        }
        
        prev_x = x;
        prev_y = y;
    }
    
    // Actualizar la pantalla
    ssd1306_display();
}