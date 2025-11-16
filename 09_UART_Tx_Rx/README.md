# 📡 Comunicación UART - ESP32

## 📋 Descripción

Este ejemplo demuestra cómo configurar y utilizar el periférico UART (Universal Asynchronous Receiver/Transmitter) del ESP32 para comunicación serie bidireccional. El ejemplo envía un mensaje a través del puerto UART2 y está configurado para recibir datos del mismo puerto.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- Cable USB para programación y comunicación serial
- Opcional: Adaptador USB a UART (como FTDI) si se desea conectar a otro dispositivo

## 🔌 Conexiones

El ejemplo utiliza el UART2 del ESP32 con los siguientes pines por defecto:

- **UART2_TX**: GPIO17 (pin de transmisión)
- **UART2_RX**: GPIO16 (pin de recepción)
- **GND**: Conexión a tierra común

> **Nota**: Para probar la comunicación UART, puedes conectar estos pines a un adaptador USB-UART o a otro microcontrolador con UART.

## ⚙️ Configuración UART

- **Baud Rate**: 9600 bps
- **Bits de datos**: 8 bits
- **Paridad**: Sin paridad
- **Bits de parada**: 1 bit
- **Control de flujo**: Deshabilitado
- **Buffer de recepción**: 1024 bytes

## 🚀 Cómo usar

1. Realiza las conexiones necesarias según la sección anterior
2. Navega a este directorio
3. Configura el proyecto: `idf.py menuconfig`
4. Compila y flashea: `idf.py build flash monitor`
5. Abre un monitor serie en el puerto USB de la placa ESP32
6. El programa enviará el mensaje "Hi I am from ESP32" cada 500ms
7. Cualquier dato recibido se mostrará en el monitor serie

## 📊 Comportamiento Esperado

- El programa enviará continuamente el mensaje "Hi I am from ESP32" a través del UART2
- Cualquier dato recibido en el UART2 se mostrará en el monitor serie
- El formato de salida será: "Length: X, Data: [datos_recibidos]"

## 🔄 Conexión con un PC

Para probar la comunicación con una computadora:

1. Conecta el pin TX del ESP32 (GPIO17) al pin RX del adaptador USB-UART
2. Conecta el pin RX del ESP32 (GPIO16) al pin TX del adaptador USB-UART
3. Asegúrate de conectar las tierras (GND) juntas
4. Abre un terminal serie (como PuTTY o screen) configurado a 9600 baudios

## 📁 Estructura del Proyecto

```
09_UART_Tx_Rx/
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
