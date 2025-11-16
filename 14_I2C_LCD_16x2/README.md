# 🖥️ Pantalla LCD 16x2 con I2C - ESP32

## 📋 Descripción

Este ejemplo muestra cómo controlar una pantalla LCD 16x2 con interfaz I2C utilizando un ESP32. La comunicación se realiza a través del protocolo I2C, lo que reduce significativamente el número de pines necesarios en comparación con la interfaz paralela tradicional.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- Módulo LCD 16x2 con interfaz I2C (generalmente basado en el chip PCF8574)
- Cables de conexión (jumpers)
- Fuente de alimentación adecuada (5V para la mayoría de los módulos LCD)

## 🔌 Conexiones

Conecta el módulo LCD I2C al ESP32 de la siguiente manera:

| Módulo LCD I2C | ESP32 | Descripción |
|----------------|-------|-------------|
| VCC            | 5V    | Alimentación |
| GND            | GND   | Tierra común |
| SDA            | GPIO21| Línea de datos I2C |
| SCL            | GPIO22| Línea de reloj I2C |

> **Nota**: Algunos módulos LCD I2C pueden funcionar con 3.3V, pero la mayoría requieren 5V. Verifica las especificaciones de tu módulo.

## ⚙️ Configuración I2C

- **Modo**: Maestro
- **Pines SDA/SCL**: GPIO21/GPIO22
- **Frecuencia del reloj I2C**: 100 KHz (estándar)
- **Dirección I2C típica del LCD**: 0x27 o 0x3F (puede variar según el fabricante)

## 🚀 Cómo usar

1. Conecta el módulo LCD I2C al ESP32 según la tabla de conexiones
2. Asegúrate de que el módulo LCD esté correctamente alimentado
3. Navega a este directorio
4. Configura el proyecto: `idf.py menuconfig`
   - Verifica la dirección I2C del LCD en la configuración
   - Ajusta los pines SDA/SCL si es necesario
5. Compila y flashea: `idf.py build flash monitor`
6. Observa el mensaje en la pantalla LCD

## 📊 Comportamiento Esperado

La pantalla LCD mostrará dos líneas de texto:
```
Hello world!
from @voidlooop
```

## 🔍 Dirección I2C del LCD

Si el LCD no muestra ningún texto, es posible que la dirección I2C sea diferente. Puedes usar un escáner I2C para encontrar la dirección correcta. La dirección más común es 0x27 o 0x3F.

## 🛠️ Funciones Disponibles

El controlador LCD proporciona las siguientes funciones:

- `lcd_init()`: Inicializa la pantalla LCD
- `lcd_clear()`: Borra la pantalla y coloca el cursor en la posición (0,0)
- `lcd_put_cursor(fila, columna)`: Mueve el cursor a la posición especificada
  - Fila: 0 (primera fila) o 1 (segunda fila)
  - Columna: 0 a 15 (para LCD 16x2)
- `lcd_send_string(texto)`: Envía una cadena de texto a la pantalla LCD
- `lcd_send_char(caracter)`: Envía un solo carácter a la pantalla LCD

## 📁 Estructura del Proyecto

```
14_I2C_LCD_16x2/
├── CMakeLists.txt      # Configuración principal de CMake
├── main/
│   ├── CMakeLists.txt # Configuración del componente principal
│   ├── i2c_lcd.c      # Controlador LCD I2C
│   ├── i2c_lcd.h      # Encabezado del controlador
│   └── main.c         # Código fuente principal
└── README.md          # Este archivo
```

## 📄 Licencia

Este proyecto está bajo la licencia MIT. Ver [LICENSE](../../LICENSE) para más detalles.

## 🔗 Recursos Adicionales

- [Documentación de ESP-IDF I2C](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2c.html)
- [Hoja de datos del PCF8574](https://www.ti.com/lit/ds/symlink/pcf8574.pdf)
- [Especificaciones de displays LCD HD44780](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)

---

*Nota: Se recomienda (aunque no es obligatorio) que las obras derivadas mantengan este mismo espíritu de código libre y abierto, especialmente cuando se utilicen con fines educativos o de investigación.*
