# 🌡️ Sensor DHT11 con Pantalla OLED - ESP32

## 📋 Descripción

Este ejemplo muestra cómo leer datos de temperatura y humedad del sensor DHT11 y mostrarlos en una pantalla OLED SSD1306 utilizando un ESP32. El proyecto utiliza comunicación I2C para la pantalla OLED y un protocolo de un solo cable para el sensor DHT11.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- Módulo DHT11 (sensor de temperatura y humedad)
- Pantalla OLED SSD1306 de 128x64 píxeles
- Cables de conexión (jumpers)
- Protoboard
- Resistencias de 4.7KΩ (pull-up para DHT11)

## 🔌 Diagrama de Conexiones

### Conexión del DHT11
| DHT11 | ESP32 | Descripción |
|-------|-------|-------------|
| VCC   | 3.3V  | Alimentación |
| DATA  | GPIO4 | Línea de datos (con resistencia pull-up de 4.7KΩ a 3.3V) |
| GND   | GND   | Tierra común |

### Conexión del OLED SSD1306
| OLED  | ESP32 | Descripción |
|-------|-------|-------------|
| VCC   | 3.3V  | Alimentación |
| GND   | GND   | Tierra común |
| SDA   | GPIO21| Línea de datos I2C |
| SCL   | GPIO22| Línea de reloj I2C |

## ⚙️ Configuración

- **DHT11**:
  - Pin de datos: GPIO4
  - Tiempo de espera: 5 segundos (configurable)

- **SSD1306 (I2C)**:
  - Dirección I2C: 0x3C (puede variar según el módulo)
  - Pines SDA/SCL: GPIO21/GPIO22
  - Frecuencia I2C: 400 KHz

## 🚀 Cómo usar

1. Conecta el hardware según el diagrama de conexiones
2. Navega al directorio del proyecto
3. Configura el proyecto: `idf.py menuconfig`
   - Verifica la configuración de pines si es necesario
   - Ajusta el tiempo de espera del DHT11 si es necesario
4. Compila el proyecto: `idf.py build`
5. Flashea el firmware: `idf.py -p [PUERTO] flash`
6. Monitorea la salida: `idf.py monitor`

## 📊 Comportamiento Esperado

- La pantalla OLED mostrará la temperatura y humedad actuales
- Los valores se actualizarán solo cuando cambien
- Los mensajes de depuración se enviarán por el puerto serie

## 📁 Estructura del Proyecto

```
16_DHT11_Oled_Display/
├── CMakeLists.txt          # Configuración principal de CMake
├── main/
│   ├── CMakeLists.txt     # Configuración del componente principal
│   ├── dht11.c            # Controlador del sensor DHT11
│   ├── dht11.h            # Encabezado del controlador DHT11
│   ├── ssd1306.c          # Controlador de la pantalla OLED
│   ├── ssd1306.h          # Encabezado del controlador OLED
│   └── main.c             # Código fuente principal
└── README.md              # Este archivo
```

## 📄 Licencia

Este proyecto está bajo la licencia MIT. Ver [LICENSE](../../LICENSE) para más detalles.

## 🔍 Solución de Problemas

- **El DHT11 no responde**:
  - Verifica las conexiones de alimentación y tierra
  - Asegúrate de que la resistencia pull-up esté correctamente conectada
  - Prueba con un tiempo de espera mayor en la configuración

- **La pantalla no muestra nada**:
  - Verifica la dirección I2C del módulo OLED (generalmente 0x3C o 0x3D)
  - Comprueba las conexiones SDA y SCL
  - Asegúrate de que la pantalla esté recibiendo alimentación

## 🔗 Recursos Adicionales

- [Hoja de datos del DHT11](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)
- [Hoja de datos del SSD1306](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
- [Documentación de ESP-IDF](https://docs.espressif.com/projects/esp-idf/)

---

*Nota: Se recomienda (aunque no es obligatorio) que las obras derivadas mantengan este mismo espíritu de código libre y abierto, especialmente cuando se utilicen con fines educativos o de investigación.*
