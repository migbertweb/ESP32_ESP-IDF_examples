/**
 * Archivo: main.c
 * Descripción: Ejemplo de uso del módulo RTC DS3231 con ESP32.
 *              Este código lee y muestra la hora y temperatura del DS3231.
 * Autor: migbertweb
 * Fecha: 2023-11-16
 * Repositorio: https://github.com/migbertweb/ESP32_ESP-IDF_Examples
 * Licencia: MIT License
 * 
 * Uso: Este ejemplo muestra cómo leer la hora y temperatura del DS3231
 *      y mostrarlas en el monitor serie.
 * 
 * Nota: Este proyecto usa Licencia MIT. Se recomienda (no obliga) mantener 
 * derivados como código libre, especialmente para fines educativos.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ds3231.h"
#include "esp_mac.h"
#include "sdkconfig.h"

// Etiqueta para mensajes de log
#define TAG "DS3231"

// Pines I2C
#define I2C_MASTER_SDA_IO           21      // Pin GPIO para SDA
#define I2C_MASTER_SCL_IO           22      // Pin GPIO para SCL
#define I2C_MASTER_NUM             I2C_NUM_0 // Puerto I2C a utilizar

// Variables globales
static float temperature;                    // Variable para almacenar la temperatura
static struct tm rtc_time;                   // Estructura para almacenar la hora

/**
 * @brief Inicializa el DS3231
 * 
 * @param dev Puntero a la estructura del dispositivo DS3231
 * @return esp_err_t Código de error ESP_OK si es exitoso
 */
static esp_err_t ds3231_init(i2c_dev_t *dev)
{
    esp_err_t ret;
    
    // Inicializar el descriptor del dispositivo DS3231
    ret = ds3231_init_desc(dev, I2C_MASTER_NUM, I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "No se pudo inicializar el descriptor del dispositivo DS3231: %s", 
                esp_err_to_name(ret));
        return ret;
    }
    
    // Verificar si el DS3231 está presente
    uint8_t data;
    ret = ds3231_get_aging_offset(dev, &data);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "No se pudo comunicar con el DS3231: %s", 
                esp_err_to_name(ret));
        return ret;
    }
    
    ESP_LOGI(TAG, "DS3231 inicializado correctamente");
    return ESP_OK;
}

/**
 * @brief Obtiene la hora actual del DS3231
 * 
 * @param dev Puntero a la estructura del dispositivo DS3231
 * @param timeinfo Puntero a la estructura para almacenar la hora
 * @return esp_err_t Código de error ESP_OK si es exitoso
 */
static esp_err_t get_current_time(i2c_dev_t *dev, struct tm *timeinfo)
{
    if (dev == NULL || timeinfo == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    
    esp_err_t ret = ds3231_get_time(dev, timeinfo);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al obtener la hora: %s", esp_err_to_name(ret));
        return ret;
    }
    
    return ESP_OK;
}

/**
 * @brief Obtiene la temperatura del DS3231
 * 
 * @param dev Puntero a la estructura del dispositivo DS3231
 * @param temp Puntero a la variable para almacenar la temperatura
 * @return esp_err_t Código de error ESP_OK si es exitoso
 */
static esp_err_t get_temperature(i2c_dev_t *dev, float *temp)
{
    if (dev == NULL || temp == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    
    esp_err_t ret = ds3231_get_temp_float(dev, temp);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al obtener la temperatura: %s", esp_err_to_name(ret));
        return ret;
    }
    
    return ESP_OK;
}

/**
 * @brief Función principal de la aplicación
 */
void app_main(void)
{
    i2c_dev_t dev = {0};  // Estructura del dispositivo DS3231
    
    // Inicializar el DS3231
    esp_err_t ret = ds3231_init(&dev);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error al inicializar el DS3231. Reiniciando...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        esp_restart();
    }
    
    ESP_LOGI(TAG, "Ejemplo de uso del DS3231 iniciado");
    
    // Bucle principal
    while (1) {
        // Obtener la hora actual
        if (get_current_time(&dev, &rtc_time) != ESP_OK) {
            ESP_LOGW(TAG, "No se pudo obtener la hora, reintentando...");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
        
        // Obtener la temperatura
        if (get_temperature(&dev, &temperature) != ESP_OK) {
            ESP_LOGW(TAG, "No se pudo obtener la temperatura, reintentando...");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
        
        // Mostrar la hora y temperatura formateadas
        ESP_LOGI(TAG, "%04d-%02d-%02d %02d:%02d:%02d, %.2f °C", 
                rtc_time.tm_year + 1900,  // Año desde 1900
                rtc_time.tm_mon + 1,      // Mes (0-11) -> (1-12)
                rtc_time.tm_mday,         // Día del mes (1-31)
                rtc_time.tm_hour,         // Horas (0-23)
                rtc_time.tm_min,          // Minutos (0-59)
                rtc_time.tm_sec,          // Segundos (0-59)
                temperature);
        
        // Esperar 1 segundo antes de la siguiente lectura
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    // Nota: En una aplicación real, deberías limpiar los recursos al salir
    // i2c_driver_delete(I2C_MASTER_NUM);
}