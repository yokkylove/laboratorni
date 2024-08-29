#include "matrix.h"
#include <malloc.h>
#include <stdio.h>

//размещает в динамической памяти матрицу размером nRows на nCols.
matrix getMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols.
matrix *getArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMatrix(nRows, nCols);
    return ms;
}

//освобождает память, выделенную под хранение матрицы m.
void freeMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        free(m.values[i]);
    free(m.values);
}

//освобождает память, выделенную под хранение массива ms из nMatrices матриц.
void freeMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMatrix(ms[i]);
    free(ms);
}

//ввод матрицы m.
void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++)
        for (int j = 0; j < m->nCols; j++)
            scanf("%d", &m->values[i][j]);
}

//ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(&ms[i]);
}

//вывод матрицы m.
void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);
        printf("\n");
    }
}

//вывод массива из nMatrices матриц, хранящейся по адресу ms.
void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++){
        outputMatrix(ms[i]);
    }
}