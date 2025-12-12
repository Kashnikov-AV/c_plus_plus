#pragma once
#include <cmath>

class abc_integral {
	private:
		double start, end, h;
		int N;
	public:
		abc_integral() {}
		abc_integral(double start1, double end1, int N1) { start = start1, end = end1, N=N1, h = fabs((end - start)) / N1; }
		~abc_integral() {}
		virtual double func(double) { return 0; }

		// метод прямоугольников
		double calc() {
			double sum = 0.0;
			for (int i = 0; i < N; i++) {
				sum += h * func(start + h * i);
			}
			return sum;
		}
};

class integral_cos : public abc_integral {
	public:
		integral_cos(double start, double end, int N) : abc_integral(start, end, N) {}
		~integral_cos() {}
		virtual double func(double x) {
			return cos(x);
		}
};

class integral_sin : public abc_integral {
	public:
		integral_sin(double start, double end, int N) : abc_integral(start, end, N) {}
		~integral_sin() {}
		virtual double func(double x) {
			return sin(x);
		}
};

class integral_exp : public abc_integral {
public:
	integral_exp(double start, double end, int N) : abc_integral(start, end, N) {}
	~integral_exp() {}
	virtual double func(double x) {
		return exp2(x);
	}
};