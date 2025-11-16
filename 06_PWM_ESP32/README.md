# 🎛️ Modulación por Ancho de Pulso (PWM) - ESP32

## 📋 Descripción

Este ejemplo demuestra cómo utilizar el módulo LED Control (LEDC) del ESP32 para generar señales PWM (Modulación por Ancho de Pulso). El ejemplo hace parpadear un LED conectado al pin GPIO2 con un efecto de atenuación gradual (fade) tanto de encendido como de apagado. El LEDC es un controlador flexible que puede generar señales PWM en múltiples pines con diferentes configuraciones de frecuencia y resolución.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- 1x LED (puede ser el integrado en la placa en el pin 2 o uno externo)
- 1x Resistencia de 220Ω (si se usa un LED externo)
- Cables de conexión (si se usa un LED externo)

## 🔌 Conexiones

- **LED integrado**:
  - Ya conectado al pin GPIO2 en la mayoría de las placas ESP32
- **Para LED externo**:
  - Ánodo del LED → Resistencia 220Ω → Pin GPIO2
  - Cátodo del LED → GND

## 🎛️ Configuración PWM

- **Modo de velocidad**: Baja velocidad (LEDC_LOW_SPEED_MODE)
- **Resolución**: 8 bits (valores de 0 a 255)
- **Frecuencia**: 5000 Hz (5 kHz)
- **Canal**: Canal 0
- **Temporizador**: Timer 0

## 🚀 Cómo usar

1. Realiza las conexiones como se describe arriba
2. Navega a este directorio
3. Configura el proyecto: `idf.py menuconfig`
4. Compila y flashea: `idf.py build flash monitor`
5. Observa el efecto de atenuación gradual del LED

## 📊 Comportamiento Esperado

El LED se atenuará gradualmente desde apagado (0%) hasta el máximo brillo (100%) y luego volverá a atenuarse hasta apagarse, repitiendo este ciclo continuamente.

## 📁 Estructura del Proyecto

```
06_PWM_ESP32/
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
