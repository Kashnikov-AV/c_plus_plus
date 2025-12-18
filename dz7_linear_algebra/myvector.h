#pragma once
#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <cmath>

// ============ КЛАСС ВЕКТОР ============
template<typename T>
class Vector {
private:
    T* data;
    int size_;
    bool isRow;  // true - строка, false - столбец

public:
    // Конструкторы
    Vector() : data(nullptr), size_(0), isRow(true) {}

    Vector(int n, bool row = true) : size_(n), isRow(row) {
        data = new T[n];
        for (int i = 0; i < n; i++) data[i] = T(0);
    }

    Vector(T* arr, int n, bool row = true) : size_(n), isRow(row) {
        data = new T[n];
        for (int i = 0; i < n; i++) data[i] = arr[i];
    }

    Vector(std::initializer_list<T> list, bool row = true) : size_(list.size()), isRow(row) {
        data = new T[size_];
        int i = 0;
        for (auto val : list) data[i++] = val;
    }

    // Копирование
    Vector(const Vector& other) : size_(other.size_), isRow(other.isRow) {
        data = new T[size_];
        for (int i = 0; i < size_; i++) data[i] = other.data[i];
    }

    // Деструктор
    ~Vector() {
        delete[] data;
    }

    // Присваивание
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size_ = other.size_;
            isRow = other.isRow;
            data = new T[size_];
            for (int i = 0; i < size_; i++) data[i] = other.data[i];
        }
        return *this;
    }

    // Доступ к элементам
    T& operator[](int i) { return data[i]; }
    const T& operator[](int i) const { return data[i]; }

    // Размеры
    int size() const { return size_; }
    int rows() const { return isRow ? 1 : size_; }
    int cols() const { return isRow ? size_ : 1; }
    bool isRowVector() const { return isRow; }

    // Транспонирование
    void transpose() { isRow = !isRow; }
    Vector transposed() const {
        Vector result(*this);
        result.transpose();
        return result;
    }

    // Сложение векторов
    Vector operator+(const Vector& other) const {
        Vector result(size_, isRow);
        for (int i = 0; i < size_; i++) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    // Вычитание векторов
    Vector operator-(const Vector& other) const {
        Vector result(size_, isRow);
        for (int i = 0; i < size_; i++) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    // Умножение на число
    Vector operator*(T scalar) const {
        Vector result(size_, isRow);
        for (int i = 0; i < size_; i++) {
            result[i] = data[i] * scalar;
        }
        return result;
    }

    friend Vector operator*(T scalar, const Vector& vec) {
        return vec * scalar;
    }

    // Скалярное умножение (вектор * вектор)
    T dot(const Vector& other) const {
        T result = 0;
        for (int i = 0; i < size_; i++) {
            result += data[i] * other[i];
        }
        return result;
    }

    // Векторное умножение (только 3D)
    Vector cross(const Vector& other) const {
        Vector result(3, isRow);
        result[0] = data[1] * other[2] - data[2] * other[1];
        result[1] = data[2] * other[0] - data[0] * other[2];
        result[2] = data[0] * other[1] - data[1] * other[0];
        return result;
    }

    // Норма вектора
    T norm() const {
        T sum = 0;
        for (int i = 0; i < size_; i++) {
            sum += data[i] * data[i];
        }
        return std::sqrt(sum);
    }

    // Вывод
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        if (vec.isRow) {
            os << "[ ";
            for (int i = 0; i < vec.size_; i++) {
                os << vec[i] << " ";
            }
            os << "]";
        }
        else {
            for (int i = 0; i < vec.size_; i++) {
                os << "[ " << vec[i] << " ]" << std::endl;
            }
        }
        return os;
    }
};

// ============ КЛАСС МАТРИЦА ============
template<typename T>
class Matrix {
private:
    T* data;
    int rows_;
    int cols_;

public:
    // Конструкторы
    Matrix() : data(nullptr), rows_(0), cols_(0) {}

    Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        data = new T[rows * cols];
        for (int i = 0; i < rows * cols; i++) data[i] = T(0);
    }

    Matrix(std::initializer_list<std::initializer_list<T>> list) {
        rows_ = list.size();
        cols_ = list.begin()->size();
        data = new T[rows_ * cols_];

        int i = 0;
        for (auto row : list) {
            int j = 0;
            for (auto val : row) {
                data[i * cols_ + j] = val;
                j++;
            }
            i++;
        }
    }

    // Копирование
    Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
        data = new T[rows_ * cols_];
        for (int i = 0; i < rows_ * cols_; i++) data[i] = other.data[i];
    }

    // Деструктор
    ~Matrix() {
        delete[] data;
    }

    // Присваивание
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] data;
            rows_ = other.rows_;
            cols_ = other.cols_;
            data = new T[rows_ * cols_];
            for (int i = 0; i < rows_ * cols_; i++) data[i] = other.data[i];
        }
        return *this;
    }

    // Доступ к элементам
    T& operator()(int i, int j) { return data[i * cols_ + j]; }
    const T& operator()(int i, int j) const { return data[i * cols_ + j]; }

    // Размеры
    int rows() const { return rows_; }
    int cols() const { return cols_; }

    // Транспонирование
    Matrix transposed() const {
        Matrix result(cols_, rows_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    // Умножение на число
    Matrix operator*(T scalar) const {
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_ * cols_; i++) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    friend Matrix operator*(T scalar, const Matrix& mat) {
        return mat * scalar;
    }

    // Умножение матриц
    Matrix operator*(const Matrix& other) const {
        Matrix result(rows_, other.cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < other.cols_; j++) {
                T sum = 0;
                for (int k = 0; k < cols_; k++) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    // Матрица * Вектор (вектор должен быть столбцом)
    Vector<T> operator*(const Vector<T>& vec) const {
        Vector<T> result(rows_, false);  // столбец

        for (int i = 0; i < rows_; i++) {
            T sum = 0;
            for (int j = 0; j < cols_; j++) {
                sum += (*this)(i, j) * vec[j];
            }
            result[i] = sum;
        }

        return result;
    }

    // Вектор * Матрица (вектор должен быть строкой)
    friend Vector<T> operator*(const Vector<T>& vec, const Matrix& mat) {
        Vector<T> result(mat.cols(), true);  // строка

        for (int j = 0; j < mat.cols(); j++) {
            T sum = 0;
            for (int i = 0; i < mat.rows(); i++) {
                sum += vec[i] * mat(i, j);
            }
            result[j] = sum;
        }

        return result;
    }

    // Вывод матрицы
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
        for (int i = 0; i < mat.rows_; i++) {
            os << "[ ";
            for (int j = 0; j < mat.cols_; j++) {
                os << mat(i, j) << " ";
            }
            os << "]" << std::endl;
        }
        return os;
    }
};

#endif // LINEAR_ALGEBRA_H