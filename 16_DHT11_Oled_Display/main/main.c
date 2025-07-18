#include <stdio.h>              // Standard I/O functions
#include <string.h>             // For string manipulation
#include "dht11.h"              // DHT11 sensor driver (user-defined or library)
#include "freertos/FreeRTOS.h"  // Core FreeRTOS definitions
#include <ssd1306.h>            // OLED display driver

// GPIO pin connected to DHT11 data line
#define CONFIG_DHT11_PIN GPIO_NUM_4

// Timeout threshold for DHT11 reading in seconds
#define CONFIG_CONNECTION_TIMEOUT 5

// Main application entry point
void app_main() {
  
  // Declare and configure the DHT11 sensor structure
  dht11_t dht11_sensor;
  dht11_sensor.dht11_pin = CONFIG_DHT11_PIN;

  // Initialize the SSD1306 OLED display
  init_ssd1306();

  // Buffers to hold temperature and humidity strings for display
  char temp_str[20];
  char humidity_str[25];

  // Infinite loop to continuously read and display data
  while (1) {
    // Static variables to store previous temperature and humidity
    static uint8_t prev_temp = 0xFF; // 0xFF indicates undefined initial state
    static uint8_t prev_hum  = 0xFF;

    // Read sensor values; returns 0 on success
    if (!dht11_read(&dht11_sensor, CONFIG_CONNECTION_TIMEOUT)) {
      // Cast sensor readings to 8-bit unsigned integers
      uint8_t curr_temp = (uint8_t)dht11_sensor.temperature;
      uint8_t curr_hum  = (uint8_t)dht11_sensor.humidity;

      // Update display only if values have changed
      if (curr_temp != prev_temp || curr_hum != prev_hum) {
        // Clear previous content from OLED
        ssd1306_clear();

        // Format temperature and humidity strings
        sprintf(temp_str,     "Temp: %dC", curr_temp);
        sprintf(humidity_str, "Humidity: %d%%", curr_hum);

        // Print strings on specific coordinates of the OLED
        ssd1306_print_str(25, 18, temp_str, false);     // Temperature at mid-screen
        ssd1306_print_str(8,  28, humidity_str, false); // Humidity below it

        // Push buffer content to OLED
        ssd1306_display();

        // Store current values for future comparison
        prev_temp = curr_temp;
        prev_hum  = curr_hum;
      }
    }

    // Delay between sensor reads to avoid over-sampling
    vTaskDelay(2000 / portTICK_PERIOD_MS); // 2 seconds
  }
}