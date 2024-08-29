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

//Задача 7: находит сумму максимальных элементов всех псевдодиагоналей
long long seventhTask(matrix m){
    return findSumOfMaxesOfPseudoDiagonal(m);
}

//Задача 8: находит минимальный элемент в выделенной области
int eighthTask(matrix m){
    return getMinInArea(m);
}

//Задача 9: сортирует по расстоянию до начала координат
void ninthTask(matrix m){
    return sortByDistances(m);
}

//Задача 10: определяет количество классов эквивалентных строк данной прямоугольной матрицы
int tenthTask(matrix m){
    return countEqClassesByRowsSum(m);
}

int main(){
    matrix a = createMatrixFromArray((int[]) {6, 8, 9, 2,
                                              7, 12, 3, 4,
                                              10, 11, 5, 1},
                                     3, 4);
    matrix b = createMatrixFromArray((int[]) {3, 2, 5, 4, 6, 8,
                                              1, 3, 6, 3, 4, 6,
                                              3, 2, 1, 2, 7, 9},
                                     3, 6);
    printf("%d", eighthTask(a));

    return 0;
}