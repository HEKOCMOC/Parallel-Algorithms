//#pragma GCC target("avx2")

#include <iostream>
#include <math.h>
#include <cmath>
#include <chrono>

using namespace std;

typedef double(*pointFunc)(double);

double f(double x) {
  return (sin(x*x+2*x));
}

double simpson_integral(pointFunc f, double a, double b, int n) {
  const double h = (b-a)/n;
  double k1 = 0, k2 = 0;

  //#pragma ivdep
  for(int i = 1; i < n; i += 2) {
    k1 += f(a + i*h);
    k2 += f(a + (i+1)*h);
  }

  return h/3*(f(a) + 4*k1 + 2*k2);
}

int main() {
  auto begin = std::chrono::steady_clock::now();
  double a, b, eps;
  double s1, s;
  int n = 1; //начальное число шагов

  cout << "Введите левую границу интегрирования a = ";
  cin >> a;
  cout << "\nВведите правую границу интегрирования b = ";
  cin >> b;
  cout << "\nВведите требуемую точность eps = ";
  cin >> eps;

  s1 = simpson_integral(f, a, b, n); //первое приближение для интеграла
  do {
    s = s1;     //второе приближение
    n = 2 * n;  //увеличение числа шагов в два раза,
                //т.е. уменьшение значения шага в два раза
    s1 = simpson_integral(f, a, b, n);
  }
  while (fabs(s1 - s) > eps);  //сравнение приближений с заданной точностью
  
  auto end = std::chrono::steady_clock::now();
  auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

  cout << "\nИнтеграл = " << s1 << endl;
  std::cout << "Время расчета интеграла составило: " << elapsed_ms.count() << " ms\n";
}