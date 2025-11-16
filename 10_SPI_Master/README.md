# 🚀 Comunicación SPI - Modo Maestro - ESP32

## 📋 Descripción

Este ejemplo demuestra cómo configurar y utilizar el periférico SPI (Serial Peripheral Interface) en modo maestro en el ESP32. El ejemplo inicializa el bus SPI2 y envía datos periódicamente a través de la interfaz SPI, mostrando tanto los datos transmitidos como los recibidos.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- Dispositivo esclavo SPI (como otro ESP32 en modo esclavo, sensor, pantalla, etc.)
- Cables de conexión (jumpers)
- Opcional: Lógica analizadora para depuración

## 🔌 Conexiones

El ejemplo utiliza el SPI2 del ESP32 con los siguientes pines por defecto:

| Pin ESP32 | Función SPI | Descripción |
|-----------|-------------|-------------|
| GPIO12    | MOSI        | Salida de datos del maestro |
| GPIO13    | MISO        | Entrada de datos al maestro |
| GPIO15    | SCLK        | Señal de reloj |
| GPIO14    | CS          | Selección de chip (activo bajo) |
| GND       | GND         | Tierra común |

> **Nota**: Asegúrate de conectar los pines correctamente al dispositivo esclavo. Si estás conectando dos placas ESP32, verifica los niveles de voltaje y las conexiones de tierra.

## ⚙️ Configuración SPI

- **Velocidad del reloj**: 1 MHz
- **Modo SPI**: 0 (CPOL=0, CPHA=0)
- **Tamaño de palabra**: 8 bits
- **Orden de bits**: MSB primero
- **Modo de transferencia**: Full-duplex

## 🚀 Cómo usar

1. Realiza las conexiones según la tabla anterior
2. Asegúrate de que el dispositivo esclavo esté correctamente alimentado
3. Navega a este directorio
4. Configura el proyecto: `idf.py menuconfig`
5. Compila y flashea: `idf.py build flash monitor`
6. Observa los mensajes en el monitor serie

## 📊 Comportamiento Esperado

- El programa enviará continuamente el mensaje "Hi I am from ESP32" a través de SPI
- Los datos recibidos (si los hay) se mostrarán en el monitor serie
- El formato de salida será:
  ```
  Transmitted: Hi I am from ESP32
  Received: [datos_recibidos]
  ```

## 🔄 Conexión con otro ESP32 (Esclavo)

Para probar la comunicación entre dos placas ESP32:

1. Carga un ejemplo de esclavo SPI en la segunda placa
2. Conecta los pines MOSI, MISO, SCLK y CS entre las placas
3. Asegúrate de conectar las tierras (GND) juntas
4. Verifica que los niveles de voltaje sean compatibles

## 📁 Estructura del Proyecto

```
10_SPI_Master/
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
