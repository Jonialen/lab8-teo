# Laboratorio 8: Análisis de Complejidad Algorítmica

Este proyecto analiza y compara la complejidad temporal de tres algoritmos diferentes implementados en C++. Se mide el tiempo de ejecución para varios tamaños de entrada (`n`) y los resultados se visualizan en una gráfica generada con Python.

## Descripción del Proyecto

El proyecto se compone de dos partes principales:

1.  **Programa de Profiling (C++)**:
    - Implementado en `main.cpp`.
    - Mide el tiempo de ejecución (en milisegundos) de tres algoritmos con complejidades teóricas de O(n² log n), O(n) y O(n²).
    - Ejecuta las mediciones para un conjunto predefinido de tamaños de entrada `n`.
    - Guarda los resultados en un archivo `resultados_lab8.csv`.

2.  **Script de Análisis y Visualización (Python)**:
    - Implementado en `main.py`.
    - Automatiza la compilación y ejecución del programa C++.
    - Lee los datos del archivo `resultados_lab8.csv` usando la librería `pandas`.
    - Genera una gráfica comparativa de los tiempos de ejecución usando `matplotlib`.
    - La gráfica utiliza una escala logarítmica en el eje X para una mejor visualización.
    - Guarda la gráfica resultante como `profiling_plot.png`.

## Requisitos

- Un compilador de C++ (ej. `g++`).
- Python 3.6 o superior.
- Las librerías de Python listadas en `requirements.txt`.

## Instalación

1.  **Clonar el repositorio (si aplica)**:

    ```bash
    git clone <url-del-repositorio>
    cd <directorio-del-proyecto>
    ```

2.  **Crear un entorno virtual y activarlo (recomendado)**:

    ```bash
    python -m venv .venv
    source .venv/bin/activate
    ```

3.  **Instalar las dependencias de Python**:
    ```bash
    pip install -r requirements.txt
    ```

## Uso

Para ejecutar el proyecto completo (compilar, ejecutar y generar la gráfica), simplemente corre el script de Python:

```bash
python main.py
```

El script se encargará de:

1.  Compilar `main.cpp` en un ejecutable llamado `profiling_program`.
2.  Ejecutar `profiling_program`, que generará el archivo `resultados_lab8.csv`.
3.  Leer `resultados_lab8.csv` y generar la gráfica `profiling_plot.png`.

La gráfica también se mostrará en una ventana emergente.

## Resultados

- **Datos Crudos**: Los tiempos de ejecución se encuentran en `resultados_lab8.csv`.
- **Visualización**: La gráfica comparativa se guarda como `profiling_plot.png`.

## Autores

- Jonathan Díaz
- Luis Padilla
