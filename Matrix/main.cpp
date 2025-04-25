#include "matrix_oop.h"
#include <iostream>

int main() {
    Matrix A(2, 2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;

    Matrix B(2, 2);
    B(0, 0) = 5; B(0, 1) = 6;
    B(1, 0) = 7; B(1, 1) = 8;

    Matrix C = A + B;
    std::cout << "Сложение матриц:\n";
    for (int i = 0; i < C.GetRows(); ++i) {
        for (int j = 0; j < C.GetCols(); ++j) {
            std::cout << C(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
