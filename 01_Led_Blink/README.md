# 🚦 LED Blink - Ejemplo Básico

## 📋 Descripción

Este ejemplo demuestra cómo hacer parpadear un LED conectado al pin GPIO2 del ESP32. Es el "Hola Mundo" de la programación embebida y sirve como punto de partida para aprender a controlar pines GPIO.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- LED (opcional, ya que la mayoría de las placas tienen un LED integrado en el pin 2)
- Resistencia de 220Ω (si se usa un LED externo)
- Cables de conexión (si se usa un LED externo)

## 🔌 Conexiones

- LED integrado: Ya conectado al pin GPIO2 en la mayoría de las placas ESP32
- Para LED externo:
  - Ánodo del LED → Resistencia 220Ω → Pin GPIO2
  - Cátodo del LED → GND

## 🚀 Cómo usar

1. Conecta tu placa ESP32
2. Navega a este directorio
3. Configura el proyecto: `idf.py menuconfig`
4. Compila y flashea: `idf.py build flash monitor`
5. Observa el LED parpadeando con un intervalo de 1 segundo

## 📁 Estructura del Proyecto

```
01_Led_Blink/
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
