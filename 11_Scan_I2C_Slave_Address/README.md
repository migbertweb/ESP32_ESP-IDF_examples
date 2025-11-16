# 🔍 Escáner de Direcciones I2C - ESP32

## 📋 Descripción

Este ejemplo implementa un escáner de direcciones I2C para el ESP32. Escanea todas las direcciones I2C posibles (1-127) e informa qué direcciones tienen dispositivos conectados. Es una herramienta muy útil para depuración y desarrollo con dispositivos I2C.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- Dispositivo(s) I2C para escanear (opcional)
- Cables de conexión (jumpers)
- Resistencias de pull-up (4.7kΩ recomendado) si los dispositivos no las tienen integradas

## 🔌 Conexiones

El ejemplo utiliza el puerto I2C0 del ESP32 con los siguientes pines por defecto:

| Pin ESP32 | Función I2C | Descripción |
|-----------|-------------|-------------|
| GPIO21    | SDA         | Línea de datos |
| GPIO22    | SCL         | Línea de reloj |
| 3.3V      | VCC         | Alimentación |
| GND       | GND         | Tierra común |

> **Nota**: Asegúrate de conectar las resistencias de pull-up (4.7kΩ recomendado) en las líneas SDA y SCL a 3.3V si tus dispositivos I2C no las tienen integradas.

## ⚙️ Configuración I2C

- **Modo**: Maestro
- **Velocidad del reloj**: 1 MHz
- **Pines SDA/SCL con pull-up habilitado**: Sí
- **Puerto I2C**: I2C_NUM_0

## 🚀 Cómo usar

1. Realiza las conexiones según la tabla anterior
2. Asegúrate de que los dispositivos I2C estén correctamente alimentados
3. Navega a este directorio
4. Configura el proyecto: `idf.py menuconfig`
5. Compila y flashea: `idf.py build flash monitor`
6. Observa los resultados del escaneo en el monitor serie

## 📊 Comportamiento Esperado

1. El programa iniciará el escaneo del bus I2C
2. Escaneará todas las direcciones I2C posibles (1-127)
3. Para cada dirección, intentará establecer comunicación
4. Mostrará las direcciones donde se encuentren dispositivos
5. Al finalizar, mostrará un resumen del escaneo

Ejemplo de salida:
```
Escaneando bus I2C...
Dispositivo encontrado en la dirección 0x3C
Dispositivo encontrado en la dirección 0x68
Escaneo I2C completado
```

## 🔍 Direcciones I2C Comunes

Algunas direcciones I2C comunes para referencia:

| Dispositivo | Dirección (hex) |
|-------------|-----------------|
| OLED SSD1306 | 0x3C o 0x3D |
| MPU6050 | 0x68 o 0x69 |
| BMP280 | 0x76 o 0x77 |
| LCD 16x2 | 0x27 o 0x3F |
| RTC DS3231 | 0x68 |
| EEPROM 24Cxx | 0x50-0x57 |

## 📁 Estructura del Proyecto

```
11_Scan_I2C_Slave_Address/
├── CMakeLists.txt      # Configuración principal de CMake
├── main/
│   ├── CMakeLists.txt # Configuración del componente principal
│   └── main.c         # Código fuente principal
└── README.md          # Este archivo
```

## 📄 Licencia

Este proyecto está bajo la licencia MIT. Ver [LICENSE](../../LICENSE) para más detalles.

---

*Nota: Se recomienda (aunque no es obligatorio) que las obras derivadas mantengan este mismo espíritu de código libre y abierto, especialmente cuando se utilicen con fines educativos o de investigación.*
