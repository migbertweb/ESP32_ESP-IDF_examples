# 🕒 Reloj de Tiempo Real DS3231 - ESP32

## 📋 Descripción

Este ejemplo demuestra cómo utilizar el módulo RTC (Reloj de Tiempo Real) DS3231 con un ESP32. El DS3231 es un reloj de tiempo real de alta precisión que mantiene la hora incluso cuando el ESP32 está apagado, gracias a su batería de respaldo. Este ejemplo lee y muestra la hora y la temperatura del DS3231.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- Módulo DS3231 RTC con batería de respaldo (CR2032)
- Cables de conexión (jumpers)
- Resistencias de pull-up (4.7kΩ recomendado) si el módulo no las tiene integradas

## 🔌 Conexiones

Conecta el módulo DS3231 al ESP32 de la siguiente manera:

| Módulo DS3231 | ESP32 | Descripción |
|---------------|-------|-------------|
| VCC           | 3.3V  | Alimentación |
| GND           | GND   | Tierra común |
| SDA           | GPIO21| Línea de datos I2C |
| SCL           | GPIO22| Línea de reloj I2C |

> **Nota**: El DS3231 ya incluye resistencias de pull-up internas, pero si experimentas problemas de comunicación, puedes añadir resistencias externas de 4.7kΩ entre SDA y 3.3V, y entre SCL y 3.3V.

## ⚙️ Configuración I2C

- **Modo**: Maestro
- **Pines SDA/SCL**: GPIO21/GPIO22
- **Frecuencia del reloj I2C**: 100 KHz (estándar)
- **Dirección I2C del DS3231**: 0x68

## 🚀 Cómo usar

1. Conecta el módulo DS3231 al ESP32 según la tabla de conexiones
2. Asegúrate de que la batería de respaldo (CR2032) esté instalada
3. Navega a este directorio
4. Configura el proyecto: `idf.py menuconfig`
5. Compila y flashea: `idf.py build flash monitor`
6. Observa la salida en el monitor serie

## 📊 Comportamiento Esperado

El programa leerá continuamente la hora y la temperatura del DS3231 y las mostrará en el monitor serie cada segundo:

```
I (1234) TIME: 2023-11-16 19:30:45, 23.50 deg Cel
I (2234) TIME: 2023-11-16 19:30:46, 23.50 deg Cel
...
```

## 📅 Configuración de la Hora

Para establecer la hora en el DS3231, necesitarás modificar el código para incluir la función `ds3231_set_time()`. Por ejemplo:

```c
struct tm timeinfo = {
    .tm_year = 123,  // Año - 1900 (2023 - 1900 = 123)
    .tm_mon = 10,    // Mes (0-11, 10 = Noviembre)
    .tm_mday = 16,   // Día del mes (1-31)
    .tm_hour = 19,   // Hora (0-23)
    .tm_min = 30,    // Minutos (0-59)
    .tm_sec = 0      // Segundos (0-59)
};

esp_err_t err = ds3231_set_time(&dev, &timeinfo);
if (err != ESP_OK) {
    ESP_LOGE(TAG, "Error al establecer la hora: %s", esp_err_to_name(err));
}
```

## 🌡️ Características del DS3231

- Precisión: ±2ppm de 0°C a +40°C (±3.5ppm de -40°C a +85°C)
- Rango de temperatura operativo: -40°C a +85°C
- Baja corriente de reposo: 200nA (típico)
- Salida de alarma programable
- Salida de onda cuadrada programable
- Incluye sensor de temperatura con precisión de ±3°C

## 📁 Estructura del Proyecto

```
13_ESP32_DS3231/
├── CMakeLists.txt      # Configuración principal de CMake
├── main/
│   ├── CMakeLists.txt # Configuración del componente principal
│   ├── ds3231.c       # Controlador DS3231
│   ├── ds3231.h       # Encabezado del controlador
│   └── main.c         # Código fuente principal
└── README.md          # Este archivo
```

## 📄 Licencia

Este proyecto está bajo la licencia MIT. Ver [LICENSE](../../LICENSE) para más detalles.

## 🔗 Recursos Adicionales

- [Hoja de datos del DS3231](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf)
- [Documentación de ESP-IDF I2C](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2c.html)

---

*Nota: Se recomienda (aunque no es obligatorio) que las obras derivadas mantengan este mismo espíritu de código libre y abierto, especialmente cuando se utilicen con fines educativos o de investigación.*
