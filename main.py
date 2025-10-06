# main.py (main.py)

import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import sys
from pathlib import Path

# Compila y ejecuta el programa en C++
def build_and_run_cpp():
    cpp_file = "main.cpp"  # Nombre del archivo fuente C++
    exe_file = "profiling_program"

    # Verifica que el archivo exista
    if not Path(cpp_file).exists():
        print(f"Error: No se encontro el archivo {cpp_file}")
        sys.exit(1)

    # Compilar el programa con g++
    print("Compilando programa C++...")
    compile_cmd = ["g++", "-std=c++17", "-O2", cpp_file, "-o", exe_file]
    result = subprocess.run(compile_cmd, capture_output=True, text=True)

    if result.returncode != 0:
        print("Error durante la compilacion:")
        print(result.stderr)
        sys.exit(1)

    print("Compilacion completada correctamente.\n")

    # Ejecutar el programa
    print("Ejecutando programa de profiling...\n")
    run_result = subprocess.run(["./" + exe_file], text=True)

    if run_result.returncode != 0:
        print("Error durante la ejecucion del programa.")
        sys.exit(1)

    print("\nEjecucion completada.\n")


# Lee el archivo CSV generado y grafica los resultados
def plot_results(csv_path="profiling_results.csv"):
    if not Path(csv_path).exists():
        print(f"Error: No se encontro el archivo {csv_path}")
        sys.exit(1)

    # Carga el archivo CSV en un DataFrame
    data = pd.read_csv(csv_path)

    print("\nDatos leidos del CSV:")
    print(data)

    # Crea una figura de Matplotlib
    plt.figure(figsize=(10, 6))

    # Grafica cada algoritmo
    plt.plot(data["n"], data["Algoritmo1_ms"], marker="o", label="Algoritmo 1 (O(n^2 log n))")
    plt.plot(data["n"], data["Algoritmo2_ms"], marker="s", label="Algoritmo 2 (O(n))")
    plt.plot(data["n"], data["Algoritmo3_ms"], marker="^", label="Algoritmo 3 (O(n^2))")

    # Configura los ejes
    plt.xscale("log")
    plt.xlabel("Tamano (n)")
    plt.ylabel("Tiempo (ms)")
    plt.title("Analisis de complejidad temporal")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.legend()
    plt.tight_layout()

    # Guarda la grafica como imagen
    output_image = "profiling_plot.png"
    plt.savefig(output_image, dpi=300)
    print(f"\nGrafica guardada como: {output_image}")

    # Muestra la grafica en pantalla
    plt.show()


# Programa principal
if __name__ == "__main__":
    # Paso 1: Ejecutar el programa C++
    build_and_run_cpp()

    # Paso 2: Generar graficas
    plot_results()

