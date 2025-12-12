#include <iostream>
#include <cmath>
#include <vector>
#include <array>

// численное интегрирование
double integral(double a, double b, double(*func)(double));

double quadro_f(double x);

double linear_f(double x);

using namespace std;

int main() {

    double pi = 2 * acos(0.0);

    cout << "sin(-pi/2, pi/2)" << endl;
    cout << integral(-pi / 2, pi / 2, sin) << endl;
    cout << "cos(-pi/2, pi/2)" << endl;
    cout << integral(-pi / 2, pi / 2, cos) << endl;
    cout << "x^2(-4, 4)" << endl;
    cout << integral(-4, 4, quadro_f) << endl;
    cout << "x(0, 6)" << endl;
    cout << integral(0, 6, linear_f) << endl;

    system("PAUSE");
    return 0;
}

double integral(double a, double b, double(*func)(double)) {
    // точность вычисления кол-во итераций
    int iter = 100000;

    double delta_x = (b - a) / iter;

    double sum_integral = 0;

    for (int i = 0; i < iter; i++) {
        double x1 = a + i * delta_x;
        double x2 = a + i * delta_x + delta_x;

        double y1 = func(x1);
        double y2 = func(x2);

        sum_integral += 0.5 * delta_x * (y1 + y2);
    }

    return abs(round(sum_integral * 10000) / 10000);
}

double quadro_f(double x) {
    return x * x;
}

double linear_f(double x) {
    return x;
}

