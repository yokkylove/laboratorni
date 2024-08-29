#include "matrix.h"
#include <malloc.h>

//Задача 1: меняет местами строки в которых находятся максимальный и минимальный элементы.
void firstTask(matrix *m) {
    int maxRowIndex = 0;
    int minRowIndex = 0;
    int maxVal = m->values[0][0];
    int minVal = m->values[0][0];

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] > maxVal) {
                maxVal = m->values[i][j];
                maxRowIndex = i;
            }
            if (m->values[i][j] < minVal) {
                minVal = m->values[i][j];
                minRowIndex = i;
            }
        }
    }
}

//Задача 2: упорядочивает строки матрицы по неубыванию наибольших
void secondTask(matrix m){
    for (int i = 0; i < m.nRows; i++) {
        sortRowsByMaxElement(m);
    }
}

//Задача 3: упорядочивает столбцы матрицы по неубыванию минимальных элементов столбцов
void thirdTask(matrix a){
    sortColsByMinElemnt(a, getMin);
}

//Задача 4: заменяет квадратную матрицу её квадратом
matrix fouthTask(matrix m){
    return getSquareOfMatrixIfSymmetric(m);
}

//Задача 5: транспонирует матрицу, если среди сумм элементов строк матрицы нет равных
void fifthTask(matrix *m){
    transposeIfMatrixHasNotEqualSumOfRows(*m);
}

int main(){
    matrix a = createMatrixFromArray((int[]) {5, 3, 6,
                                              7, 8, 5,
                                              4, 8, 2},
                                     3, 3);
    fifthTask(&a);
    outputMatrix(a);

    return 0;
}