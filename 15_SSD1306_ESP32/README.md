# 🖥️ Pantalla OLED SSD1306 - ESP32

## 📋 Descripción

Este ejemplo muestra cómo controlar una pantalla OLED monocromática de 128x64 píxeles con controlador SSD1306 utilizando un ESP32. La comunicación se realiza a través del protocolo I2C, lo que permite una conexión sencilla con solo 4 cables.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- Módulo OLED SSD1306 de 0.96" o 1.3" con interfaz I2C
- Cables de conexión (jumpers)
- Fuente de alimentación adecuada (3.3V o 5V según el módulo)

## 🔌 Conexiones

Conecta el módulo SSD1306 al ESP32 de la siguiente manera:

| Módulo SSD1306 | ESP32 | Descripción |
|----------------|-------|-------------|
| VCC            | 3.3V  | Alimentación (algunos módulos aceptan 5V) |
| GND            | GND   | Tierra común |
| SDA            | GPIO21| Línea de datos I2C |
| SCL            | GPIO22| Línea de reloj I2C |

> **Nota**: Algunos módulos SSD1306 tienen pines etiquetados como SDA/SCL, mientras que otros pueden usar SDL/SDA. Verifica la documentación de tu módulo.

## ⚙️ Configuración I2C

- **Modo**: Maestro
- **Pines SDA/SCL**: GPIO21/GPIO22
- **Frecuencia del reloj I2C**: 400 KHz (estándar para SSD1306)
- **Dirección I2C típica del SSD1306**: 0x3C o 0x3D (depende del módulo)

## 🚀 Cómo usar

1. Conecta el módulo SSD1306 al ESP32 según la tabla de conexiones
2. Asegúrate de que el módulo esté correctamente alimentado
3. Navega a este directorio
4. Configura el proyecto: `idf.py menuconfig`
   - Verifica la dirección I2C del SSD1306 en la configuración
   - Ajusta los pines SDA/SCL si es necesario
5. Compila y flashea: `idf.py build flash monitor`
6. Observa el mensaje en la pantalla OLED

## 📊 Comportamiento Esperado

La pantalla OLED mostrará varias líneas de texto centradas:
```
   Hello World!
   SSD1306 OLED
   with ESP32
   ESP-IDF
   Embedded C
```

## 🔍 Dirección I2C del SSD1306

Si la pantalla no muestra ningún texto, es posible que la dirección I2C sea diferente. Puedes usar un escáner I2C para encontrar la dirección correcta. Las direcciones más comunes son 0x3C y 0x3D.

## 🛠️ Funciones Disponibles

El controlador SSD1306 proporciona las siguientes funciones:

- `init_ssd1306()`: Inicializa la pantalla OLED
- `ssd1306_clear()`: Borra la pantalla
- `ssd1306_print_str(x, y, texto, invertir)`: Muestra texto en la posición (x,y)
  - x: Posición horizontal (0-127)
  - y: Posición vertical (múltiplos de 8 o 10, dependiendo de la fuente)
  - texto: Cadena de texto a mostrar
  - invertir: true para texto en negativo
- `ssd1306_display()`: Actualiza la pantalla con los cambios
- `ssd1306_draw_pixel(x, y, color)`: Dibuja un píxel en (x,y)
- `ssd1306_draw_line()`, `ssd1306_draw_rect()`, `ssd1306_draw_circle()`: Funciones de dibujo básicas

## 📁 Estructura del Proyecto

```
15_SSD1306_ESP32/
├── CMakeLists.txt      # Configuración principal de CMake
├── main/
│   ├── CMakeLists.txt # Configuración del componente principal
│   ├── ssd1306.c      # Controlador SSD1306
│   ├── ssd1306.h      # Encabezado del controlador
│   ├── font8x8_basic.h # Fuente de 8x8 píxeles
│   └── main.c         # Código fuente principal
└── README.md          # Este archivo
```

## 📄 Licencia

Este proyecto está bajo la licencia MIT. Ver [LICENSE](../../LICENSE) para más detalles.

## 🔗 Recursos Adicionales

- [Hoja de datos del SSD1306](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
- [Documentación de ESP-IDF I2C](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2c.html)
- [Guía de conexión SSD1306](https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/)

---

*Nota: Se recomienda (aunque no es obligatorio) que las obras derivadas mantengan este mismo espíritu de código libre y abierto, especialmente cuando se utilicen con fines educativos o de investigación.*
