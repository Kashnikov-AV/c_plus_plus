#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

void print_grid(double** grid, int cells);
double** generate_grid(int cells);
void set_diffusion(double** grid, double** new_grid, int cells, double tau, double h);
void free_grid(double** grid, int cells);

int main() {
    // кол-во ячеек в сетке
    int cells = 7;
    // шаг сетки
    double h = 1.0 / (cells - 1);
    // шаг по времени
    double tau = 0.01 * h;
    // кол-во итераций по времени
    int iterations = 8;

    cout << "h=" << h << endl;
    cout << "tau=" << tau << endl;
    cout << "generated grid:" << endl;

    double** grid = generate_grid(cells);
    print_grid(grid, cells);

    // расчет сеток
    for (int iter = 0; iter < iterations; iter++) {
        double** new_grid = generate_grid(cells);
        set_diffusion(grid, new_grid, cells, tau, h);

        cout << "Iteration " << iter + 1 << ":" << endl;
        print_grid(new_grid, cells);

        // Освобождаем старую сетку и заменяем на новую
        free_grid(grid, cells);
        grid = new_grid;
    }

    // Освобождаем последнюю сетку
    free_grid(grid, cells);
    system("PAUSE");
    return 0;
}

void set_diffusion(double** grid, double** new_grid, int cells, double tau, double h) {
    double factor = tau / (h * h);

    // применение дифф оператора для внутренних ячеек
    for (int i = 1; i < cells - 1; i++) {
        for (int j = 1; j < cells - 1; j++) {
            new_grid[i][j] = grid[i][j] + factor *
                (grid[i + 1][j] + grid[i - 1][j] +
                    grid[i][j + 1] + grid[i][j - 1] -
                    4 * grid[i][j]);
        }
    }

    // копируем граничные условия
    for (int i = 0; i < cells; i++) {
        new_grid[i][0] = grid[i][0];           // левая граница
        new_grid[i][cells - 1] = grid[i][cells - 1]; // правая граница
    }
    for (int j = 0; j < cells; j++) {
        new_grid[0][j] = grid[0][j];           // верхняя граница
        new_grid[cells - 1][j] = grid[cells - 1][j]; // нижняя граница
    }
}

void print_grid(double** grid, int cells) {
    for (int i = 0; i < cells; i++) {
        for (int j = 0; j < cells; j++) {
            cout << grid[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

double** generate_grid(int cells) {
    double** grid = new double* [cells];
    for (int i = 0; i < cells; i++) {
        grid[i] = new double[cells];
    }

    // Инициализация нулями
    for (int i = 0; i < cells; i++) {
        for (int j = 0; j < cells; j++) {
            grid[i][j] = 0.0;
        }
    }

    // Устанавливаем 1 в центре
    int center = cells / 2;
    grid[center][center] = 1.0;

    return grid;
}

void free_grid(double** grid, int cells) {
    for (int i = 0; i < cells; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}