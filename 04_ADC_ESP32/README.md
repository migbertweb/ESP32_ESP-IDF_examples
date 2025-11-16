# 📊 Conversión Analógico-Digital (ADC) - ESP32

## 📋 Descripción

Este ejemplo demuestra cómo utilizar el módulo ADC (Convertidor Analógico-Digital) integrado en el ESP32. Lee valores de voltaje de un pin analógico (ADC1_CHANNEL_0 - GPIO36) y los muestra a través del puerto serie. El ADC del ESP32 tiene una resolución de 12 bits (0-4095) y puede medir voltajes de 0V a 3.3V.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- 1x Potenciómetro de 10kΩ o cualquier sensor analógico
- Cables de conexión
- Protoboard (opcional)

## 🔌 Conexiones

- **Potenciómetro**:
  - Patilla central → GPIO36 (ADC1_CHANNEL_0)
  - Patilla lateral → 3.3V
  - Otra patilla lateral → GND

> **Nota**: Si usas un sensor analógico, conecta la salida al pin GPIO36, VCC a 3.3V y GND a tierra.

## 🚀 Cómo usar

1. Realiza las conexiones como se describe arriba
2. Navega a este directorio
3. Configura el proyecto: `idf.py menuconfig`
4. Compila y flashea: `idf.py build flash monitor`
5. Gira el potenciómetro y observa cómo cambian los valores en el monitor serie

## 📊 Interpretación de los Valores

- **0**: 0V
- **2048**: ~1.65V (mitad del rango)
- **4095**: 3.3V (máximo)

## 📁 Estructura del Proyecto

```
04_ADC_ESP32/
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
