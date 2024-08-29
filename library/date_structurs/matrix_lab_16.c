#include "matrix.h"
#include <malloc.h>
#include <stdio.h>

//Задача 1: меняет местами строки в которых находятся максимальный и минимальный элементы.
void firstTask(matrix *m)  {
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

    swapRows(m, maxRowIndex, minRowIndex);
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
matrix fourthTask(matrix m){
    return getSquareOfMatrixIfSymmetric(m);
}

//Задача 5: транспонирует матрицу, если среди сумм элементов строк матрицы нет равных
void fifthTask(matrix *m){
    transposeIfMatrixHasNotEqualSumOfRows(*m);
}

//Задача 6: определяет, являются ли две матрицы взаимообратными
bool sixthTask(matrix m1, matrix m2){
    return isMutuallyInverseMatrices(m1, m2);
}


int main(){
    matrix a = createMatrixFromArray((int[]) {1, 0,
                                              0, 1},
                                     2, 2);
    matrix b = createMatrixFromArray((int[]) {1, 0,
                                              1, 1},
                                     2, 2);
    if (sixthTask(a, b)){
        printf("true");
    }else{
        printf("false");
    }

    return 0;
}