# 🤝 Comunicación I2C Maestro-Esclavo - ESP32

## 📋 Descripción

Este ejemplo demuestra cómo configurar un ESP32 como maestro I2C para comunicarse con un dispositivo esclavo. El código lee datos de un dispositivo esclavo en la dirección I2C 0x0C y los muestra en el monitor serie.

## 🛠️ Hardware Requerido

- 2 placas de desarrollo ESP32 (una como maestro y otra como esclavo)
- Cables de conexión (jumpers)
- Resistencias de pull-up (4.7kΩ recomendado) si los dispositivos no las tienen integradas

## 🔌 Conexiones

Conecta las dos placas ESP32 de la siguiente manera:

| ESP32 Maestro | ESP32 Esclavo | Descripción |
|---------------|---------------|-------------|
| GPIO21 (SDA)  | GPIO21 (SDA)  | Línea de datos |
| GPIO22 (SCL)  | GPIO22 (SCL)  | Línea de reloj |
| 3.3V          | 3.3V          | Alimentación |
| GND           | GND           | Tierra común |

> **Nota**: Asegúrate de conectar las resistencias de pull-up (4.7kΩ recomendado) en las líneas SDA y SCL a 3.3V si tus dispositivos no las tienen integradas.

## ⚙️ Configuración I2C

- **Modo**: Maestro
- **Dirección del esclavo**: 0x0C
- **Pines SDA/SCL con pull-up habilitado**: Sí
- **Velocidad del reloj**: 10 KHz
- **Puerto I2C**: I2C_NUM_0

## 🚀 Cómo usar

1. Carga el código de ejemplo de esclavo I2C en la segunda placa ESP32
2. Realiza las conexiones según la tabla anterior
3. Asegúrate de que ambas placas estén correctamente alimentadas
4. Navega a este directorio
5. Configura el proyecto: `idf.py menuconfig`
6. Compila y flashea: `idf.py build flash monitor`
7. Observa los datos recibidos del esclavo en el monitor serie

## 📊 Comportamiento Esperado

1. El maestro I2C intentará leer 14 bytes del dispositivo esclavo en la dirección 0x0C
2. Los datos recibidos se mostrarán en el monitor serie cada segundo
3. Si el esclavo está configurado correctamente, verás los datos que envía

Ejemplo de salida:
```
Datos I2C recibidos: Hola, ESP32!
Datos I2C recibidos: Hola, ESP32!
...
```

## 🔄 Configuración del Dispositivo Esclavo

Para que este ejemplo funcione, necesitas tener un dispositivo esclavo I2C configurado en la dirección 0x0C. Puedes usar otro ESP32 con un ejemplo de esclavo I2C o cualquier otro dispositivo compatible con I2C.

## 📁 Estructura del Proyecto

```
12_I2C_Master_with_Slave/
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
