#ifndef MATRIX_OOP_H
#define MATRIX_OOP_H

#include <iostream>
#include <vector>
#include <stdexcept>

class Matrix {
private:
    std::vector<std::vector<double>> matrix_;
    int rows_;
    int cols_;

public:
    // Конструкторы
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;

    // Деструктор
    ~Matrix();

    // Методы
    bool EqMatrix(const Matrix& other) const;
    void SumMatrix(const Matrix& other);
    void SubMatrix(const Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const Matrix& other);
    Matrix Transpose() const;
    Matrix CalcComplements() const;
    double Determinant() const;
    Matrix InverseMatrix() const;

    // Перегрузка операторов
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const double num) const;
    bool operator==(const Matrix& other) const;
    Matrix& operator=(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const double num);
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    // Методы доступа
    int GetRows() const;
    int GetCols() const;
};

#endif // MATRIX_OOP_H
