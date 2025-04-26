#include "matrix_oop.h"

Matrix::Matrix() : rows_(3), cols_(3) {
    matrix_.resize(rows_, std::vector<double>(cols_, 0));
}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    matrix_.resize(rows_, std::vector<double>(cols_, 0));
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {}

Matrix::Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), matrix_(std::move(other.matrix_)) {
    other.rows_ = 0;
    other.cols_ = 0;
}

Matrix::~Matrix() {}

bool Matrix::EqMatrix(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) return false;
    return matrix_ == other.matrix_;
}

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

void Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] *= num;
        }
    }
}

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

Matrix Matrix::Transpose() const {
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

Matrix Matrix::CalcComplements() const {
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix must be square");
    }
    Matrix complements(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            // Создаем матрицу, исключая i-ю строку и j-й столбец
            Matrix minor(rows_ - 1, cols_ - 1);
            for (int mi = 0, mji = 0; mi < rows_; ++mi) {
                for (int mj = 0, mjj = 0; mj < cols_; ++mj) {
                    if (mi != i && mj != j) {
                        minor(mji, mjj) = matrix_[mi][mj];
                        mjj++;
                        if (mjj == cols_ - 1) {
                            mjj = 0;
                            mji++;
                        }
                    }
                }
            }
            complements(i, j) = (i + j) % 2 == 0 ? minor.Determinant() : -minor.Determinant();
        }
    }
    return complements;
}

double Matrix::Determinant() const {
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix must be square");
    }
    if (rows_ == 1) { return matrix_[0][0]; }
    if (rows_ == 2) { return (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]); }
    double determinant = 0.0;
    for (int j = 0; j < cols_; ++j) {
        Matrix minor(rows_ - 1, cols_ - 1);
        for (int mi = 1; mi < rows_; ++mi) {
            for (int mj = 0; mj < cols_; ++mj) {
                if (mj < j) { minor(mi - 1, mj) = matrix_[mi][mj]; }
                else if (mj > j) { minor(mi - 1, mj - 1) = matrix_[mi][mj]; }
            }
        }
        determinant += (j % 2 == 0 ? 1 : -1) * matrix_[0][j] * minor.Determinant();
    }
    return determinant;
}

Matrix Matrix::InverseMatrix() const {
    if (Determinant() == 0) {
        throw std::invalid_argument("Matrix determinant cannot be 0");
    }
    double determinant = Determinant();
    Matrix complements = CalcComplements();
    Matrix inverse(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            inverse(j, i) = complements(i, j) / determinant;
        }
    }
    return inverse;
}

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

int Matrix::GetRows() const {
    return rows_;
}

int Matrix::GetCols() const {
    return cols_;
}
