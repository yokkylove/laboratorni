#ifndef GG_MATRIX_H
#define GG_MATRIX_H

#include <stdbool.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

//размещает в динамической памяти матрицу размером nRows на nCols.
matrix getMatrix(int nRows, int nCols);

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols.
matrix *getArrayOfMatrices(int nMatrices, int nRows, int nCols);

//освобождает память, выделенную под хранение матрицы m.
void freeMatrix(matrix m);

//освобождает память, выделенную под хранение массива ms из nMatrices матриц.
void freeMatrices(matrix *ms, int nMatrices);

//ввод матрицы m.
void inputMatrix(matrix *m);

//ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices);

//вывод матрицы m.
void outputMatrix(matrix m);

//вывод массива из nMatrices матриц, хранящейся по адресу ms.
void outputMatrices(matrix *ms, int nMatrices);

//обменивает строки с порядковыми номерами i1 и i2 в матрице m.
void swapRows(matrix m, int i1, int i2);

//обменивает колонки с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix m, int j1, int j2);

int getSum(int const *a, int n);

//выполняет сортировку вставками строк матрицы m по неубыванию
// значения функции criteria применяемой для строк.
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int const*, int));

//выполняет сортировку выбором столбцов матрицы m по неубыванию
//значения функции criteria применяемой для столбцов.
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int));

//возвращает значение ’истина’, если матрица m
//является квадратной, ложь – в противном случае.
bool isSquareMatrix(matrix *m);

//возвращает значение ’истина’, если матрицы m1 и m2 равны,
//ложь – в противном случае.
bool areTwoMatricesEqual(matrix *m1, matrix *m2);

//возвращает значение ’истина’, если матрица m
//является единичной, ложь – в противном случае.
bool isEMatrix(matrix *m);

//возвращает значение ’истина’, если матрица m
//является симметричной, ложь – в противном случае.
bool isSymmetricMatrix(matrix *m);

#endif //GG_MATRIX_H