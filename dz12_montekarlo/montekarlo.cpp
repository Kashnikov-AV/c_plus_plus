#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iomanip>

class grid {
private:
    int N;
    double* ptr;
    double h;
    const double eps = 0.0001;
    const int walks = 5000;
    const double tol = 0.1;

    void set_boundary() {
        for (int j = 0; j < N; j++) {
            ptr[j] = exp(1 - j * h);
            ptr[(N - 1) * N + j] = 1.0;
        }
        for (int i = 0; i < N; i++) {
            ptr[i * N] = exp(1 - i * h);
            ptr[i * N + (N - 1)] = 1.0;
        }
    }

    bool on_boundary(double i, double j) {
        return (i <= tol || i >= N - 1 - tol || j <= tol || j >= N - 1 - tol);
    }

    double boundary_value(double i, double j) {
        if (i <= tol) return exp(1 - j * h);
        if (j <= tol) return exp(1 - i * h);
        if (i >= N - 1 - tol) return 1.0;
        return 1.0;
    }

    double random_walk(double start_i, double start_j) {
        double i = start_i, j = start_j;

        while (!on_boundary(i, j)) {
            int dir = rand() % 4;
            switch (dir) {
            case 0: i = fmax(i - 1, 0); break;
            case 1: j = fmin(j + 1, N - 1); break;
            case 2: i = fmin(i + 1, N - 1); break;
            case 3: j = fmax(j - 1, 0); break;
            }
        }
        return boundary_value(i, j);
    }

public:
    grid(int size) : N(size) {
        ptr = new double[N * N];
        h = 1.0 / (N - 1);
        memset(ptr, 0, N * N * sizeof(double));
        srand(time(NULL));
        set_boundary();
    }

    ~grid() { delete[] ptr; }

    void print() {
        std::cout << std::fixed << std::setprecision(4);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                std::cout << std::setw(8) << ptr[i * N + j] << " ";
            std::cout << std::endl;
        }
    }

    void monte_carlo() {
        std::cout << "Computing with " << walks << " walks per point..." << std::endl;
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                double sum = 0;
                for (int k = 0; k < walks; k++)
                    sum += random_walk(i, j);
                ptr[i * N + j] = sum / walks;
            }
        }
        std::cout << "Monte Carlo calculation completed." << std::endl;
    }
};

int main() {
    int size;
    std::cout << "Grid size: ";
    std::cin >> size;

    grid g(size);

    std::cout << "\nInitial grid (boundary conditions)" << std::endl;
    g.print();

    g.monte_carlo();

    std::cout << "\nFinal grid (after Monte Carlo)" << std::endl;
    g.print();

    system("PAUSE");
    return 0;
}