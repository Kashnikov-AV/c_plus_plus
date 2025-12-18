#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

class grid {
private:
    int N; // кол-во ячеек квадратной сетки
    double* ptr; // массив ячеек
    double h; // шаг сетки
    const double eps = 0.0001; // параметр точности
    int iter = 0; // кол-во итераций
    const int walks_per_point = 10000; // количество случайных блужданий на точку

    // граничные условия
    void set_boundary_conditions() {
        for (int j = 0; j < N; j++) {
            ptr[j] = exp(1 - j * h); // верхняя граница
        }

        for (int i = 0; i < N; i++) {
            ptr[i * N] = exp(1 - i * h); // левая граница
        }

        for (int j = 0; j < N; j++) {
            ptr[N * (N - 1) + j] = 1.0; // нижняя граница
        }

        for (int i = 0; i < N; i++) {
            ptr[i * N + (N - 1)] = 1.0; // правая граница
        }
    }

    // Функция для проверки, находится ли точка на границе
    bool is_boundary(int i, int j) {
        return (i == 0 || i == N - 1 || j == 0 || j == N - 1);
    }

    // Функция для получения граничного значения в точке (если точка на границе)
    double get_boundary_value(int i, int j) {
        if (i == 0) return exp(1 - j * h); // верхняя граница
        if (j == 0) return exp(1 - i * h); // левая граница
        if (i == N - 1) return 1.0; // нижняя граница
        if (j == N - 1) return 1.0; // правая граница
        return 0.0; // внутренняя точка
    }

    // Случайное блуждание из точки (i,j) до достижения границы
    double random_walk(int start_i, int start_j) {
        int i = start_i;
        int j = start_j;

        // Блуждаем до достижения границы
        while (!is_boundary(i, j)) {
            // Генерируем случайное направление: 0-вверх, 1-вправо, 2-вниз, 3-влево
            int direction = rand() % 4;

            switch (direction) {
            case 0: i = std::max(i - 1, 0); break;     // вверх
            case 1: j = std::min(j + 1, N - 1); break;  // вправо
            case 2: i = std::min(i + 1, N - 1); break;  // вниз
            case 3: j = std::max(j - 1, 0); break;    // влево
            }
        }

        // Возвращаем граничное значение
        return get_boundary_value(i, j);
    }

public:
    grid() { N = 0; ptr = nullptr; h = 0; srand(time(NULL)); };

    grid(int N1) {
        N = N1;
        ptr = new double[N * N];
        h = 1.0 / (N - 1);
        memset(ptr, 0, N * N * sizeof(double));
        srand(time(NULL)); // инициализация генератора случайных чисел
        set_boundary_conditions();
    }

    ~grid() {
        delete[] ptr;
    }

    // Запрет копирования для избежания проблем с памятью
    grid(const grid&) = delete;
    grid& operator=(const grid&) = delete;

    void print_grid() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << ptr[i * N + j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << "iter=" << iter << std::endl;
    }

    // Метод Монте-Карло для решения уравнения Лапласа
    double calc_monte_carlo() {
        double max_diff = 0.0;

        // Сохраняем старые значения для сравнения
        double* old_values = new double[N * N];
        memcpy(old_values, ptr, N * N * sizeof(double));

        // Обрабатываем только внутренние точки
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                double sum = 0.0;

                // Выполняем несколько случайных блужданий из текущей точки
                for (int walk = 0; walk < walks_per_point; walk++) {
                    sum += random_walk(i, j);
                }

                // Среднее значение по всем блужданиям
                double new_value = sum / walks_per_point;

                // Обновляем значение в точке
                ptr[i * N + j] = new_value;

                // Вычисляем максимальное изменение
                double diff = std::abs(new_value - old_values[i * N + j]);
                if (diff > max_diff) {
                    max_diff = diff;
                }
            }
        }

        delete[] old_values;
        iter++;

        return max_diff;
    }

    // Функция для решения уравнения методом Монте-Карло до достижения точности
    void solve_monte_carlo() {
        double diff;
        int max_iterations = 100;

        std::cout << "Solving using Monte Carlo method..." << std::endl;

        do {
            diff = calc_monte_carlo();
            std::cout << "Iteration " << iter << ", max difference: " << diff << std::endl;

            if (iter >= max_iterations) {
                std::cout << "Maximum iterations reached" << std::endl;
                break;
            }

        } while (diff > eps);

        std::cout << "Solution completed in " << iter << " iterations" << std::endl;
    }

    double get_eps() { return eps; }
    int get_iterations() { return iter; }
};