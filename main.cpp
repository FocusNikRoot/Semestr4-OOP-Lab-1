#include "matrix_oop.h"
#include <iostream>

int main() {
    Matrix A(2, 2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;

    Matrix B(3, 2);
    B(0, 0) = 5; B(0, 1) = 6;
    B(1, 0) = 7; B(1, 1) = 8;
    B(2, 0) = 4; B(2, 1) = 1;

    std::cout << "матрица A:\n";
    for (int i = 0; i < A.GetRows(); ++i) {
        for (int j = 0; j < A.GetCols(); ++j) {
            std::cout << A(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "матрица B:\n";
    for (int i = 0; i < B.GetRows(); ++i) {
        for (int j = 0; j < B.GetCols(); ++j) {
            std::cout << B(i, j) << " ";
        }
        std::cout << std::endl;
    }

    try {
        Matrix C = A + B;

        std::cout << "Сумма матриц:\n";
        for (int i = 0; i < C.GetRows(); ++i) {
            for (int j = 0; j < C.GetCols(); ++j) {
                std::cout << C(i, j) << " ";
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    try {
        Matrix D = B - A;

        std::cout << "Вычитание матриц:\n";
        for (int i = 0; i < D.GetRows(); ++i) {
            for (int j = 0; j < D.GetCols(); ++j) {
                std::cout << D(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    try {
        Matrix E = A * B;

        std::cout << "Перемножение матриц:\n";
        for (int i = 0; i < E.GetRows(); ++i) {
            for (int j = 0; j < E.GetCols(); ++j) {
                std::cout << E(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    try {
        Matrix F = B * 2;

        std::cout << "Умножение матрицы на число:\n";
        for (int i = 0; i < F.GetRows(); ++i) {
            for (int j = 0; j < F.GetCols(); ++j) {
                std::cout << F(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    Matrix G = B;
    std::cout << "Присвоение матрицы:\n";
    for (int i = 0; i < G.GetRows(); ++i) {
        for (int j = 0; j < G.GetCols(); ++j) {
            std::cout << G(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Сравнение матриц:\n" << (G == B) << std::endl;

    try {
        A += B;

        std::cout << "матрица А:\n";
        for (int i = 0; i < A.GetRows(); ++i) {
            for (int j = 0; j < A.GetCols(); ++j) {
                std::cout << A(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    system("pause");

    return 0;
}
