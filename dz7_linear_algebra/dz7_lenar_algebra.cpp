#include "myvector.h"
#include <iostream>
#include <windows.h>

int main() {

    // Создание векторов
    Vector<double> v1 = { 1, 2, 3 };
    Vector<double> v2 = { 4, 5, 6 };

    std::cout << "vector 1: " << v1 << std::endl;
    std::cout << "vector 2: " << v2 << std::endl;

    // Сложение
    Vector<double> sum = v1 + v2;
    std::cout << "sum: " << sum << std::endl;

    // Умножение на число
    Vector<double> mult = v1 * 2.5;
    std::cout << "v1 * 2.5: " << mult << std::endl;

    // Скалярное произведение
    double dot = v1.dot(v2);
    std::cout << "scalar mul: " << dot << std::endl;

    // Векторное произведение
    Vector<double> cross = v1.cross(v2);
    std::cout << "vec mul: " << cross << std::endl;

    // Создание матриц
    Matrix<double> m1 = { {1, 2, 3},
                        {4, 5, 6} };

    Matrix<double> m2 = { {1, 2},
                        {3, 4},
                        {5, 6} };

    std::cout << std::endl << "matrix 1:" << std::endl << m1;
    std::cout << "matrix 2:" << std::endl << m2;

    // Умножение матриц
    Matrix<double> m3 = m1 * m2;
    std::cout << "m1 * m2:" << std::endl << m3;

    // Вектор * Матрица
    Vector<double> rowVec = { 1, 2, 3 };
    Matrix<double> mat = { {4, 5},
                         {6, 7},
                         {8, 9} };
    Vector<double> res1 = rowVec * mat;
    std::cout << "vec * matrix: " << res1 << std::endl;

    // Матрица * Вектор
    Vector<double> colVec({ 1, 2, 3 }, false);  // столбец
    Vector<double> res2 = mat * colVec;
    std::cout << "matrix * vec:" << std::endl << res2;
    system("PAUSE");
    return 0;
}