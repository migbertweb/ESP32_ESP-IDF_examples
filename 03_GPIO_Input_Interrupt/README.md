# 🎯 Interrupción por GPIO - Ejemplo Avanzado

## 📋 Descripción

Este ejemplo demuestra cómo utilizar interrupciones por hardware en el ESP32. Cuando se presiona un botón conectado a un pin configurado para interrupciones, se incrementa un contador y se muestra su valor por el puerto serie. Este método es más eficiente que el polling (como en el ejemplo anterior) ya que el microcontrolador puede estar en modo de bajo consumo mientras espera el evento.

## 🛠️ Hardware Requerido

- Placa de desarrollo ESP32
- 1x Pulsador o botón táctil
- 1x Resistencia de 10kΩ (pull-down)
- Cables de conexión

## 🔌 Conexiones

- **Botón**:
  - Un extremo → Pin GPIO5
  - Otro extremo → 3.3V
  - Resistencia de 10kΩ entre GPIO5 y GND (pull-down)

> **Nota**: El botón usa una resistencia pull-up interna, por lo que la conexión se simplifica.

## 🚀 Cómo usar

1. Realiza las conexiones como se describe arriba
2. Navega a este directorio
3. Configura el proyecto: `idf.py menuconfig`
4. Compila y flashea: `idf.py build flash monitor`
5. Presiona el botón y observa cómo se incrementa el contador en el monitor serie

## 📊 Características del Código

- Configuración de interrupción por flanco de subida (GPIO_INTR_POSEDGE)
- Uso de IRAM_ATTR para la rutina de servicio de interrupción (ISR)
- Contador de interrupciones global
- Manejo de rebotes mediante variable de estado

## 📁 Estructura del Proyecto

```
03_GPIO_Input_Interrupt/
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
