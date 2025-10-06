#include <atomic>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

// ------------------------
// Ejercicio 1
// Complejidad teórica: O(n^2 log n)
void ejercicio1(int n) {
  volatile int counter = 0;
  for (int i = n / 2; i <= n; i++) {
    for (int j = 1; j + n / 2 <= n; j++) {
      for (int k = 1; k <= n; k = k * 2) {
        counter++;
      }
    }
  }
}

// ------------------------
// Ejercicio 2
// Complejidad teórica: O(n)
void ejercicio2(int n) {
  if (n <= 1)
    return;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      break;
    }
  }
}

// ------------------------
// Ejercicio 3
// Complejidad teórica: O(n^2)
void ejercicio3(int n) {
  for (int i = 1; i <= n / 3; i++) {
    for (int j = 1; j <= n; j += 4) {
      volatile int x = i + j;
    }
  }
}

// BARRA DE PROGRESO
void showProgress(const string &label, atomic<bool> &done) {
  const int width = 40;
  int progress = 0;
  const int total = 100;

  while (!done) {
    float fraction = static_cast<float>(progress) / total;
    int pos = static_cast<int>(fraction * width);

    cout << "\r" << label << " [";
    for (int i = 0; i < width; ++i) {
      if (i < pos)
        cout << "=";
      else if (i == pos)
        cout << ">";
      else
        cout << " ";
    }
    cout << "] " << fixed << setprecision(1) << setw(5) << fraction * 100.0
         << "%" << flush;

    this_thread::sleep_for(milliseconds(100));
    progress = (progress + 3) % (total + 1);
  }

  cout << "\r" << label << " [";
  for (int i = 0; i < width; ++i)
    cout << "=";
  cout << "] 100.0%" << flush;
  cout << "\r" << label << " completado.             " << endl;
}

// MEDICION DE TIEMPO DE EJECUCION
double medirTiempo(void (*func)(int), int n, const string &label) {
  atomic<bool> done(false);
  thread barraProgreso([&]() { showProgress(label, done); });

  auto start = high_resolution_clock::now();
  func(n);
  auto end = high_resolution_clock::now();

  done = true;
  barraProgreso.join();

  duration<double, std::milli> elapsed = end - start;
  return elapsed.count();
}

// PROGRAMA PRINCIPAL
int main() {
  vector<int> tamanos = {1, 10, 100, 1000, 10000, 100000, 1000000};

  cout << "     ANALISIS DE COMPLEJIDAD DE ALGORITMOS     " << endl;

  cout << setw(10) << left << "n" << setw(18) << right << "Ejercicio 1 (ms)"
       << setw(18) << right << "Ejercicio 2 (ms)" << setw(18) << right
       << "Ejercicio 3 (ms)" << endl;
  cout << string(60, '-') << endl;

  ofstream csv("resultados_lab8.csv");
  csv << "n,Ejercicio1_ms,Ejercicio2_ms,Ejercicio3_ms\n";

  for (int n : tamanos) {
    cout << "\nProcesando n = " << n << "..." << endl;

    double t1 = medirTiempo(ejercicio1, n, "Ejercicio 1");
    double t2 = medirTiempo(ejercicio2, n, "Ejercicio 2");
    double t3 = medirTiempo(ejercicio3, n, "Ejercicio 3");

    cout << setw(10) << left << n << setw(18) << right << fixed
         << setprecision(3) << t1 << setw(18) << right << t2 << setw(18)
         << right << t3 << endl;

    csv << n << "," << fixed << setprecision(3) << t1 << "," << t2 << "," << t3
        << "\n";
  }

  csv.close();

  cout << "\nResultados guardados en: resultados_lab8.csv" << endl;
  cout << "Use el archivo CSV para graficar (input vs tiempo)." << endl;
  cout << "Sugerencia: Escala logarítmica en eje X." << endl;

  return 0;
}
