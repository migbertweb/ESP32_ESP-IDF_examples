# 🧲 Sensor de Efecto Hall - ESP32

## 📋 Descripción

Este ejemplo muestra cómo utilizar el sensor de efecto Hall integrado en el ESP32. El sensor de efecto Hall puede detectar campos magnéticos y generar un voltaje proporcional a la intensidad del campo. En este ejemplo, se lee el valor del sensor y se enciende un LED cuando se detecta un campo magnético fuerte.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32 (con sensor Hall integrado)
- 1x LED (opcional, ya que muchas placas tienen uno integrado)
- 1x Resistencia de 220Ω (si se usa un LED externo)
- Imán permanente (para probar el sensor)

## 🔌 Conexiones

- **LED** (si se usa uno externo):
  - Ánodo → Resistencia 220Ω → Pin GPIO12
  - Cátodo → GND

> **Nota**: El sensor de efecto Hall está integrado en el chip ESP32 y no requiere conexiones externas. 
> El LED integrado en la placa de desarrollo (si está disponible) puede usarse en lugar de un LED externo.

## 🎛️ Funcionamiento del Sensor Hall

- **Rango típico de valores**: Aproximadamente 100-300 en condiciones normales (sin campo magnético)
- **Respuesta a campos magnéticos**: 
  - Los valores aumentan cuando se acerca el polo sur de un imán
  - Los valores disminuyen cuando se acerca el polo norte de un imán
- **Umbral de detección**: En este ejemplo, se enciende un LED cuando el valor es menor a 100

## 🚀 Cómo usar

1. Conecta el LED si estás usando uno externo
2. Navega a este directorio
3. Configura el proyecto: `idf.py menuconfig`
4. Compila y flashea: `idf.py build flash monitor`
5. Observa los valores del sensor en el monitor serie
6. Acerca un imán al ESP32 y observa cómo cambian los valores
7. El LED se encenderá cuando detecte un campo magnético fuerte

## 📊 Comportamiento Esperado

- En el monitor serie se mostrarán los valores del sensor Hall en tiempo real
- Los valores típicos sin imán están alrededor de 100-300 (puede variar según la placa)
- Al acercar un imán, los valores cambiarán significativamente
- El LED se encenderá cuando el valor del sensor sea menor a 100

## 📁 Estructura del Proyecto

```
08_HALL_Sensor/
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
