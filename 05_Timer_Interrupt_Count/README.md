# ⏱️ Temporizador con Interrupción - ESP32

## 📋 Descripción

Este ejemplo demuestra cómo utilizar el temporizador de hardware del ESP32 para generar interrupciones periódicas. El temporizador incrementa un contador cada 10 milisegundos (10,000 microsegundos) y muestra el valor actual del contador a través del puerto serie. Este es un ejemplo fundamental para comprender cómo programar tareas que deben ejecutarse en intervalos regulares sin bloquear el bucle principal.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- Cable USB para programación y alimentación
- Computadora con puerto USB y terminal serie

## 🔌 Conexiones

Este ejemplo no requiere conexiones externas ya que utiliza únicamente las capacidades internas del ESP32. El contador se muestra a través del puerto serie.

## 🚀 Cómo usar

1. Conecta tu placa ESP32 al puerto USB de tu computadora
2. Navega a este directorio
3. Configura el proyecto: `idf.py menuconfig`
4. Compila y flashea: `idf.py build flash monitor`
5. Observa cómo se incrementa el contador en el monitor serie

## ⚙️ Configuración del Temporizador

- **Período**: 10,000 microsegundos (10ms)
- **Modo**: Periódico (se repite automáticamente)
- **Resolución**: 1 microsegundo (máxima precisión)
- **Contador**: Entero sin signo de 16 bits (0-65535)

## 📊 Salida Esperada

Verás una secuencia de números incrementándose en el monitor serie:
```
1
2
3
...
```
Cada número se incrementa cada 10ms.

## 📁 Estructura del Proyecto

```
05_Timer_Interrupt_Count/
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
