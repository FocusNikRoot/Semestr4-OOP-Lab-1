#include "matrix_oop.h"

// Базовый конструктор
Matrix::Matrix() : rows_(3), cols_(3) {
    matrix_.resize(rows_, std::vector<double>(cols_, 0));
}

// Параметризированный конструктор
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    matrix_.resize(rows_, std::vector<double>(cols_, 0));
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {}

// Конструктор переноса
Matrix::Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), matrix_(std::move(other.matrix_)) {
    other.rows_ = 0;
    other.cols_ = 0;
}

// Деструктор
Matrix::~Matrix() {}

// Проверка на равенство
bool Matrix::EqMatrix(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) return false;
    return matrix_ == other.matrix_;
}

// Сложение матриц
void Matrix::SumMatrix(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Different matrix dimensions");
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

// Вычитание матриц
void Matrix::SubMatrix(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Different matrix dimensions");
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

// Умножение на число
void Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] *= num;
        }
    }
}

// Умножение матриц
void Matrix::MulMatrix(const Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication");
    }
    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            for (int k = 0; k < cols_; ++k) {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    *this = result;
}

// Транспонирование матрицы
Matrix Matrix::Transpose() const {
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

// Вычисление алгебраических дополнений
Matrix Matrix::CalcComplements() const {
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix must be square");
    }
    // Реализация вычисления алгебраических дополнений
    // ...
    return Matrix(); // Возвращаем пустую матрицу как заглушку
}

// Вычисление определителя
double Matrix::Determinant() const {
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix must be square");
    }
    // Реализация вычисления определителя
    // ...
    return 0.0; // Заглушка
}

// Вычисление обратной матрицы
Matrix Matrix::InverseMatrix() const {
    if (Determinant() == 0) {
        throw std::invalid_argument("Matrix is singular and cannot be inverted");
    }
    // Реализация вычисления обратной матрицы
    // ...
    return Matrix(); // Возвращаем пустую матрицу как заглушку
}

// Перегрузка операторов
Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(*this);
    result.SumMatrix(other);
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(*this);
    result.SubMatrix(other);
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(*this);
    result.MulMatrix(other);
    return result;
}

Matrix Matrix::operator*(const double num) const {
    Matrix result(*this);
    result.MulNumber(num);
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    return EqMatrix(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        matrix_ = other.matrix_;
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    SumMatrix(other);
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    SubMatrix(other);
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    MulMatrix(other);
    return *this;
}

Matrix& Matrix::operator*=(const double num) {
    MulNumber(num);
    return *this;
}

double& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i][j];
}

const double& Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i][j];
}

// Методы доступа
int Matrix::GetRows() const {
    return rows_;
}

int Matrix::GetCols() const {
    return cols_;
}
