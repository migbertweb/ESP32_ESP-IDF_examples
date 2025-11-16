# 🚀 ESP32 ESP-IDF Examples

Colección de ejemplos básicos para ESP32 utilizando ESP-IDF y C embebido.

## 📋 Descripción

Este repositorio contiene ejemplos prácticos para aprender a programar el ESP32 utilizando el framework ESP-IDF. Cada ejemplo está diseñado para ser claro, conciso y educativo.

## 🛠️ Requisitos

- ESP-IDF v4.4 o superior
- ESP32 o ESP32-S2/S3/C3
- Toolchain de Xtensa (incluida en ESP-IDF)
- Python 3.7 o superior

## 📁 Estructura del Proyecto

```
ESP32_ESP-IDF_Examples/
├── 01_Led_Blink/         # Ejemplo de parpadeo de LED
├── 02_GPIO_Input/        # Lectura de entrada digital
├── 03_GPIO_Input_Interrupt/  # Interrupciones GPIO
├── 04_ADC_ESP32/         # Conversión analógico-digital
├── 05_Timer_Interrupt_Count/ # Temporizadores
├── 06_PWM_ESP32/         # Modulación por ancho de pulso
├── 07_DAC_with_ESP32/    # Conversor digital-analógico
├── 08_HALL_Sensor/       # Sensor de efecto Hall
├── 09_UART_Tx_Rx/        # Comunicación UART
├── 10_SPI_Master/        # Comunicación SPI (Maestro)
├── 11_Scan_I2C_Slave_Address/ # Escaneo I2C
├── 12_I2C_Master_with_Slave/  # Comunicación I2C
├── 13_ESP32_DS3231/      # Módulo de reloj en tiempo real
├── 14_I2C_LCD_16x2/      # Pantalla LCD 16x2 vía I2C
├── 15_SSD1306_ESP32/     # Pantalla OLED SSD1306
└── 16_DHT11_Oled_Display/ # Sensor DHT11 + Pantalla OLED
```

## 🚀 Cómo usar

1. Instala el framework ESP-IDF siguiendo la [guía oficial](https://docs.espressif.com/projects/esp-idf/)
2. Clona este repositorio
3. Navega a la carpeta del ejemplo deseado
4. Configura el puerto serie: `idf.py menuconfig`
5. Compila y flashea: `idf.py build flash monitor`

## 📄 Licencia

Este proyecto está bajo la licencia MIT. Ver [LICENSE](LICENSE) para más detalles.

## 🙏 Agradecimientos

- A la comunidad de Espressif por su excelente documentación
- A todos los contribuyentes de código abierto

## 📧 Contacto

- Autor: Migbertweb
- Repositorio: [GitHub](https://github.com/migbertweb/ESP32_ESP-IDF_Examples)

---

*Nota: Se recomienda (aunque no es obligatorio) que las obras derivadas mantengan este mismo espíritu de código libre y abierto, especialmente cuando se utilicen con fines educativos o de investigación.*
