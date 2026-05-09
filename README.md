# Proyecto Final ADA — Andres Toro, Jeronimo Rodríguez y Erick Guerrero

## Descripción

Este proyecto corresponde a la práctica final integradora de la asignatura de **Análisis y Diseño de Algoritmos (ADA)**.

La aplicación fue desarrollada en **C++17** y trabaja sobre el dataset:

```txt
WA_Fn-UseC_-Telco-Customer-Churn.csv
```

El proyecto integra tres paradigmas algorítmicos:

- Divide y Vencerás
- Algoritmos Codiciosos
- Programación Dinámica

Todo el pipeline se ejecuta en una sola corrida y genera automáticamente los archivos solicitados en `results/`.

---

# Objetivos

- Aplicar MergeSort y búsqueda binaria sobre datos reales.
- Construir un MST usando Kruskal y Union-Find.
- Resolver el problema de Mochila 0-1 usando programación dinámica.
- Integrar todos los módulos en un pipeline coherente.
- Analizar complejidades teóricas y comportamiento empírico.

---

# Estructura del Proyecto

```text
ADA_PF_Toro_Rodriguez_Guerrero/
│
├── README.md
│
├── data/
│   └── WA_Fn-UseC_-Telco-Customer-Churn.csv
│
├── results/
│   ├── solicitudes_ordenadas.csv
│   ├── busquedas_A.txt
│   ├── mst_red.txt
│   └── asignacion_bw.txt
│
├── src/
│   ├── parser.cpp / parser.hpp
│   ├── mergesort.cpp / mergesort.hpp
│   ├── binary_search.cpp / binary_search.hpp
│   ├── graph.cpp / graph.hpp
│   ├── kruskal.cpp / kruskal.hpp
│   ├── knapsack.cpp / knapsack.hpp
│   └── main.cpp
│
└── report/
    └── Informe.pdf
```

---

# Tecnologías Utilizadas

- Lenguaje: C++
- Estándar: C++17
- Compilador: g++
- Librerías utilizadas:
  - `vector`
  - `algorithm`
  - `chrono`
  - `fstream`
  - `iostream`

---

# Compilación

Ubicarse en la carpeta raíz del proyecto y ejecutar:

```bash
g++ -std=c++17 -O2 -o ada_pf src/main.cpp src/*.cpp
```

---

# Ejecución

```bash
./ada_pf data/WA_Fn-UseC_-Telco-Customer-Churn.csv
```

La ejecución genera automáticamente todos los archivos de salida en la carpeta `results/`.

---

# Dataset Utilizado

Dataset utilizado:

- Telecom Customer Churn (Kaggle)

Archivo:

```txt
WA_Fn-UseC_-Telco-Customer-Churn.csv
```

## Campos utilizados

| Campo CSV | Interpretación |
|---|---|
| `customerID` | Identificador de solicitud |
| `tenure` | Prioridad de servicio |
| `MonthlyCharges` | Valor mensual |
| `TotalCharges` | Peso para mochila |
| `Churn` | Estado de la solicitud |

---

# Módulo A — Divide y Vencerás

## Funcionalidades

- Parseo del CSV
- MergeSort estable
- Búsqueda binaria recursiva
- Medición de tiempos
- Exportación de resultados

---

## MergeSort

Se implementó MergeSort para ordenar las solicitudes por `tenure` descendente.

### Complejidad temporal

```txt
T(n) = 2T(n/2) + Θ(n) ⇒ Θ(n log n)
```

### Justificación

MergeSort fue elegido sobre QuickSort porque:

- Es estable.
- Garantiza complejidad `O(n log n)` en el peor caso.
- Tiene comportamiento predecible sobre datasets grandes.

---

## Búsqueda Binaria Recursiva

Se implementó búsqueda binaria recursiva sobre el arreglo ordenado para localizar la primera solicitud cuyo tenure sea mayor o igual a `k`.

### Complejidad

```txt
T(n) = O(log n)
```

---

## Consultas Ejecutadas

| Consulta | Valor |
|---|---|
| Q_A01 | 72 |
| Q_A02 | 60 |
| Q_A03 | 45 |
| Q_A04 | 30 |
| Q_A05 | 12 |

---

## Análisis Empírico

Se realizaron pruebas con:

- 1000 registros
- 3500 registros
- 7043 registros

Los tiempos fueron medidos usando:

```cpp
std::chrono::high_resolution_clock
```

---

## Archivos Generados

- `results/solicitudes_ordenadas.csv`
- `results/busquedas_A.txt`

---

# Módulo B — Algoritmo Codicioso

## Construcción del Grafo

Se construyó un grafo completo de:

- 20 nodos
- 190 aristas

Cada registro `i` fue asignado al grupo:

```txt
i mod 20
```

El costo entre nodos se calculó usando el promedio de `MonthlyCharges`.

---

## Kruskal + Union-Find

Se implementó el algoritmo de Kruskal utilizando:

- Unión por rango
- Compresión de caminos

### Complejidad

```txt
T(n) = O(E log E)
```

---

## Propiedad Codiciosa

La optimalidad del algoritmo se justifica usando el:

- Lema del ciclo

Seleccionar la arista de menor peso que no forme ciclo garantiza mantener una solución óptima global.

---

## Verificación

Se verificó manualmente el MST sobre el subgrafo inducido de los primeros 5 nodos.

---

## Archivo Generado

- `results/mst_red.txt`

---

# Módulo C — Programación Dinámica

## Problema de Mochila 0-1

Capacidad máxima:

```txt
W = 500
```

Se utilizaron las primeras 50 solicitudes activas (`Churn = No`) con mayor tenure.

---

## Definiciones

### Peso

```txt
TotalCharges
```

### Valor

```txt
MonthlyCharges * 10
```

---

## Recurrencia

```txt
DP[i][w] = max(DP[i−1][w], DP[i−1][w−wi] + vi)
```

---

## Complejidad

```txt
T(n) = Θ(nW)
```

---

## Backtracking

Se implementó reconstrucción de solución para recuperar:

- Solicitudes seleccionadas
- customerID incluidos
- Valor total óptimo

---

## Fallo del Enfoque Codicioso

Se construyó un contraejemplo explícito donde el enfoque por ratio:

```txt
v_i / w_i
```

no produce la solución óptima.

---

## Pseudopolinomialidad

La complejidad depende de:

- `n`
- `W`

Por ello, el algoritmo es pseudopolinomial y no polinomial estricto.

---

## Archivo Generado

- `results/asignacion_bw.txt`

---

# Integración del Pipeline

El proyecto integra los tres módulos en un único flujo:

1. El Módulo A ordena las solicitudes.
2. El Módulo B construye el MST usando el dataset.
3. El Módulo C utiliza la salida ordenada del Módulo A.

Toda la ejecución ocurre en un solo comando.

---

# Verificación de Resultados

| Propiedad | Valor |
|---|---|
| Registros cargados | 7043 |
| TotalCharges nulo | 11 |
| Churn = No | 5174 |
| tenure máximo | 72 |
| tenure mínimo | 0 |
| MonthlyCharges promedio | 64.76 |

---

# Relación con la Rúbrica

## Módulo A

- MergeSort estable
- Búsqueda binaria recursiva
- Análisis empírico
- Complejidad formal

## Módulo B

- Kruskal correcto
- Union-Find optimizado
- Verificación manual
- Lema del ciclo

## Módulo C

- Tabulación correcta
- Backtracking
- Contraejemplo codicioso
- Pseudopolinomialidad

## Pipeline

- Integración completa
- Ejecución en un solo comando
- Generación automática de resultados

---

# Herramientas Utilizadas

- C++17
- g++
- GitHub
- Dataset Telecom Customer Churn

---

# Referencias

- Telecom Customer Churn Dataset — Kaggle
- Material del curso ADA
- Documentación oficial de C++
- Bibliografía sobre:
  - MergeSort
  - Kruskal
  - Programación Dinámica

---

# Roles del Equipo

| Integrante | Responsabilidad |
|---|---|
| Andres Toro | Módulo A |
| Jeronimo Rodríguez | Módulo B |
| Erick Guerrero | Módulo C e integración |

---

# Conclusiones

- MergeSort permitió ordenar eficientemente más de 7000 registros.
- La búsqueda binaria redujo significativamente los tiempos de consulta.
- Kruskal permitió construir una red de costo mínimo.
- La programación dinámica garantizó la solución óptima para la asignación de ancho de banda.
- El proyecto permitió comparar paradigmas algorítmicos sobre datos reales.

---
