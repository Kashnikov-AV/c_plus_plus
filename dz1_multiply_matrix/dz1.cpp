#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <functional>
#include <vector>
#include <random>
#include <cmath>
#include <array>

#define SEED 100

using namespace std;

int main() {

    int M, N, K;
    cout << "A(m,n)*B(n,k)=C(m,k)" << endl;
    cout << "Enter m" << endl;
    cin >> M;
    cout << "Enter n" << endl;
    cin >> N;
    cout << "Enter k" << endl;
    cin >> K;
    cout << endl;

    // matrix A
    double* array_A = new double[M * N];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            array_A[i*M+j] = 0.;

    std::mt19937 mt(SEED);
    std::uniform_real_distribution<double> dist(1., 10.);
    for (size_t i = 0; i < M * N; i++)
    {
        array_A[i] = dist(mt);
    }

    cout << "matrix A" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << array_A[i * M + j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    // matrix B
    double* array_B = new double[N * K];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < K; j++)
            array_B[i * M + j] = 0.;

    for (size_t i = 0; i < N * K; i++)
    {
        array_B[i] = dist(mt);
    }

    cout << "matrix B" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            cout << array_B[i * N + j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    //multiply matrix
    //matrix C
    double* array_C = new double[M * K];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < K; j++)
            array_C[i * M + j] = 0.;

    for (int i = 0; i < M; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < K; j++)
                array_C[i * N + j] += array_A[i * N + k] * array_B[k * N + j];

    cout << "matrix C" << endl;
    for (int i = 0; i < M; i++) {
        for (int k = 0; k < K; k++) {
            cout << array_C[i*M+k] << "\t";
        }
        cout << endl;
    }

    return 0;
}