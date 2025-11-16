# 🎛️ Entrada Digital - Ejemplo Básico

## 📋 Descripción

Este ejemplo demuestra cómo leer el estado de un botón/pulsador conectado a un pin de entrada GPIO y controlar un LED en función de su estado. Cuando se presiona el botón, el LED se enciende, y cuando se suelta, se apaga.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- 1x Pulsador o botón táctil
- 1x Resistencia de 10kΩ (pull-down)
- 1x LED (opcional, puede usarse el integrado)
- 1x Resistencia de 220Ω (si se usa LED externo)
- Cables de conexión

## 🔌 Conexiones

- **Botón**:
  - Un extremo → Pin GPIO5
  - Otro extremo → 3.3V
  - Resistencia de 10kΩ entre GPIO5 y GND (pull-down)
- **LED**:
  - Ánodo → Resistencia 220Ω → Pin GPIO2
  - Cátodo → GND

> **Nota**: El botón usa una resistencia pull-up interna, por lo que la conexión se simplifica.

## 🚀 Cómo usar

1. Realiza las conexiones como se describe arriba
2. Navega a este directorio
3. Configura el proyecto: `idf.py menuconfig`
4. Compila y flashea: `idf.py build flash monitor`
5. Presiona el botón para encender el LED, suéltalo para apagarlo

## 📁 Estructura del Proyecto

```
02_GPIO_Input/
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
