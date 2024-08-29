#include "matrix.h"
#include "matrix_lab_16.h"

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
    sortByDistances(m);
}

//Задача 10: определяет количество классов эквивалентных строк данной прямоугольной матрицы
int tenthTask(matrix m){
    return countEqClassesByRowsSum(m);
}

//Задача 11: определяет количество особых элементов матрицы
int eleventhTask(matrix m){
    return getNSpecialElement(m);
}

//Задача 12: заменяет предпоследнюю строку матрицы первым из столбцов, в котором находится минимальный элемент матрицы
void twelvethTask(matrix m){
    swapPenultimateRow(m);
}

//Задача 13: определяет число матриц, строки которых упорядочены по неубыванию элементов
int thirteenthTask(matrix *ms, int nMatrix){
    countNonDescendingRowsMatrices(ms, nMatrix);
}

//Задача 14: Выводит матрицы, имеющие наибольшее число нулевых строк
void fourteenthTask(matrix *ms, int nMatrix){
    printMatrixWithMaxZeroRows(ms, nMatrix);
}

//Задача 15: выводит матрицы с наименьшей нормой
void fifteenthTask(matrix *ms, int nMatrix){
    printMatricesWithMinNorm(ms, nMatrix);
}

//Задача 16: определяет количество особых элементов в матрице
int sixteenthTask(matrix m){
    getNSpecialElement2(m);
}

//Задача 17: принимает матрицу m и массив целых чисел b,
//и возвращает индекс вектора из матрицы m,
//у которого угол между ним и вектором b максимален.
int seventeenthTask(matrix m, int *b){
    return getVectorIndexWithMaxAngle(m, b);
}

//Задача 18: Находит скалярное произведение строки,
//в которой находится наибольший элемент матрицы, на столбец с наименьшим элементом.
long long eightteenthTask(matrix m){
    return getSpecialScalarProduct(m);
}