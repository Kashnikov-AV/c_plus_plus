#pragma once
#include <cstring>
#include <iostream>
#include <cmath>

class grid {
	private:
		int N; //кол-во ячеек квадратной сетки
		double* ptr; // массив ячеек
		double* prev_ptr;
		double h; // шаг сетки
		const double eps = 0.0001; // параметр разности
		int iter = 0; // кол-во итераций
		// граничные условия
		void set_boundary_conditions() {
				for (int j = 0; j < N; j++) {
					ptr[j] = exp(1 - j * h);
				}

				for (int i = 0; i < N; i++) {
					ptr[i*N] = exp(1 - i * h);
				}

				for (int j = 0; j < N; j++) {
					ptr[N*(N-1)+j] = 1.0;
				}

				for (int i = 0; i < N; i++) {
					ptr[i * N + (N-1)] = 1.0;
				}
		}
	public:
		grid() { N = 0; ptr = nullptr; h = 0; };
		grid(int N1) {
			N = N1;
			ptr = new double[N*N];
			prev_ptr = new double[N * N];
			h = 1.0 / (N-1);
			memset(ptr, 0, N * N * sizeof(double));
			set_boundary_conditions();
		}
		~grid() {}

		void print_grid() {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					std::cout << ptr[i*N+j] << "\t";
				}
				std::cout << std::endl;
			}
			std::cout << "iter=" << iter << std::endl;
		}

		double calc_laplas() {
			double* tmp;
			tmp = ptr;
			ptr = prev_ptr;
			prev_ptr = tmp;

			iter++;

			// расчет новой сетки
			for (int i = 1; i < N-1; i++) {
				for (int j = 1; j < N-1; j++) {
					ptr[i*N+j] = 0.25*(prev_ptr[(i - 1) * N + j] + prev_ptr[(i + 1) * N + j] + prev_ptr[i * N + (j - 1)] + prev_ptr[i * N + (j + 1)]);
				}
				set_boundary_conditions();
			}

			// расчет нормы
			double new_eps = 0;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					new_eps += (ptr[i * N + j] - prev_ptr[i * N + j]) * h * h;
				}
			}

			return new_eps;
		}

		double get_eps() { return eps; }
};