#include "matrix.h"
#include <malloc.h>

//размещает в динамической памяти матрицу размером nRows на nCols.
matrix getMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}

//размещает в динамической памяти массив из nMatrix матриц размером nRows на nCols.
matrix *getArrayOfMatrix(int nMatrix, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrix);
    for (int i = 0; i < nMatrix; i++)
        ms[i] = getMatrix(nRows, nCols);
    return ms;
}

//освобождает память, выделенную под хранение матрицы a.
void freeMatrix(matrix a) {
    for (int i = 0; i < a.nRows; i++)
        free(a.values[i]);
    free(a.values);
}

//освобождает память, выделенную под хранение массива a из k матриц.
void freeArrayOfMatrix(matrix *a, int k) {
    for (int i = 0; i < k; i++)
        freeMatrix(a[i]);
    return free(a);
}

