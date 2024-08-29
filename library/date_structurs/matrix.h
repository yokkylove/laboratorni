#ifndef GG_MATRIX_H
#define GG_MATRIX_H

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
matrix *getArrayOfMatrix(int nMatrices, int nRows, int nCols);

//освобождает память, выделенную под хранение матрицы a.
void freeMatrix(matrix a);

//освобождает память, выделенную под хранение массива a из k матриц.
void freeArrayOfMatrix(matrix *a, int k);



#endif //GG_MATRIX_H
