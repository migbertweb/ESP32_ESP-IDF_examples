# 🔊 Conversor Digital-Analógico (DAC) - ESP32

## 📋 Descripción

Este ejemplo demuestra cómo utilizar el Convertidor Digital-Analógico (DAC) integrado en el ESP32. El DAC convierte señales digitales en señales analógicas, permitiendo generar formas de onda o niveles de voltaje controlados por software. En este ejemplo, se genera una señal de rampa ascendente y descendente en el canal 1 del DAC (GPIO25).

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32 (con DAC integrado)
- Osciloscopio o multímetro para medir la señal de salida (opcional)
- Cable de conexión (si se desea conectar a un circuito externo)

## 🔌 Conexiones

- **Salida DAC**:
  - Canal 1 (GPIO25) → Conectar a un osciloscopio o multímetro
  - GND → Tierra del osciloscopio/multímetro

> **Nota**: El ESP32 tiene dos canales DAC:
> - Canal 1: GPIO25 (DAC1)
> - Canal 2: GPIO26 (DAC2)
> Este ejemplo utiliza solo el Canal 1.

## 📊 Especificaciones del DAC

- **Resolución**: 8 bits (0-255)
- **Rango de voltaje de salida**: 0V a 3.3V
- **Canales**: 2 (DAC1 en GPIO25 y DAC2 en GPIO26)
- **Frecuencia de actualización**: Depende del código (en este ejemplo, ~20Hz)

## 🚀 Cómo usar

1. Realiza las conexiones como se describe arriba
2. Navega a este directorio
3. Configura el proyecto: `idf.py menuconfig`
4. Compila y flashea: `idf.py build flash monitor`
5. Observa la señal en el osciloscopio o el voltaje en el multímetro

## 📈 Comportamiento Esperado

- La salida del DAC generará una señal de rampa que sube de 0 a 3.3V y luego baja de 3.3V a 0V de forma continua.
- Cada paso de la rampa tendrá una duración de 50ms.
- En el monitor serie se mostrarán los valores digitales (0-255) que se están enviando al DAC.

## 📁 Estructura del Proyecto

```
07_DAC_with_ESP32/
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
