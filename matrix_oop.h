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
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;

    ~Matrix();

    bool EqMatrix(const Matrix& other) const;
    void SumMatrix(const Matrix& other);
    void SubMatrix(const Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const Matrix& other);
    Matrix Transpose() const;
    Matrix CalcComplements() const;
    double Determinant() const;
    Matrix InverseMatrix() const;

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

    int GetRows() const;
    int GetCols() const;
};

#endif
