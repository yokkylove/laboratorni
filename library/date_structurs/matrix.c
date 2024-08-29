#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "matrix.h"

//размещает в динамической памяти матрицу размером nRows на nCols
matrix getMemMatrix (int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++) {
        values[i] = (int *) malloc(sizeof(int) * nCols);
    }

    return (matrix){values, nRows, nCols};
}

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols.
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);

    return ms;
}

//освобождает память, выделенную под хранение матрицы m.
void freeMemMatrix(matrix *m) {
    free (m->values);
}

//освобождает память, выделенную под хранение массива ms из nMatrices матриц.
void freeMemMatrices(matrix *ms, int nMatrices) {
    for(int i = 0; i < nMatrices; i++) {
        free (ms[i].values);
    }
}

//ввод матрицы m.
void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++)
            scanf("%d ", &m->values[i][j]);
        scanf("\n");
    }
}

//ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices) {
    for (int k = 0; k < nMatrices; k++) {
        inputMatrix(&ms[k]);
    }
}

// вывод матрицы m.
void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);
        printf("\n");
    }
}

//вывод массива из nMatrices матриц, хранящейся по адресу ms.
void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
    }
}

void swap_pointers(int **a, int **b) {
    int *t = *a;
    *a = *b;
    *b = t;
}

// обмен строк с порядковыми номерами i1 и i2 в матрице m.
void swapRows(matrix* m, int i1, int i2) {
    if (i1 < 0 || i1 >= m->nRows || i2 < 0 || i2 >= m->nRows) {
        return;
    }

    int *temp = m->values[i1];
    m->values[i1] = m->values[i2];
    m->values[i2] = temp;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix m, int j1, int j2) {
    assert(0 <= j1 && j1 < m.nCols);
    assert(0 <= j2 && j2 < m.nCols);
    for (int i = 0; i < m.nRows; i++)
        swap(&m.values[i][j1], &m.values[i][j2]);
}

// функция-критерий для сравнения строк по сумме элементов
long long getSum(int* a, int nCols) {
    long long sum = 0;
    for (int i = 0; i < nCols; i++) {
        sum += a[i];
    }

    return sum;
}

// функция-критерий для сравнения строк по максимальному элементу
int getMax(int* a, int n) {
    assert(n > 0);
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

// выполняет сортировку вставками строк
//матрицы m по неубыванию значения функции criteria применяемой для строк
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) {
    int *criteriaValues = (int*)malloc(sizeof(int) * m.nRows);
    for (int i = 0; i < m.nRows; i++)
        criteriaValues[i] = criteria(m.values[i], m.nCols);
    for (int i = 0; i < m.nRows; i++) {
        int minIndex = i;
        for (int j = i + 1; j < m.nRows; j++)
            if (criteriaValues[j] > criteriaValues[minIndex])
                minIndex = j;
        if (i != minIndex) {
            swap_pointers(&criteriaValues[i], &criteriaValues[minIndex]);
            swapRows(&m, i, minIndex);
        }
    }
    free(criteriaValues);
}

//выполняет сортировку выбором столбцов
//матрицы m по неубыванию значения функции criteria применяемой для столбцов
void selectionSortColsMatrixByColCriteria(matrix a, int (*criteria)(int*, int)) {
    int *criteriaValues = (int*)malloc(sizeof(int) * a.nCols);
    int *column = (int*)malloc(sizeof(int) * a.nRows);
    for (int j = 0; j < a.nCols; j++) {
        for (int i = 0; i < a.nRows; i++)
            column[i] = a.values[i][j];
        criteriaValues[j] = criteria(column, a.nCols);
    }
    for (int i = 0; i < a.nCols; i++) {
        int minIndex = i;
        for (int j = i + 1; j < a.nCols; j++)
            if (criteriaValues[j] < criteriaValues[minIndex])
                minIndex = j;
        if (i != minIndex) {
            swap(&criteriaValues[i], &criteriaValues[minIndex]);
            swapColumns(a, i, minIndex);
        }
    }
    free(column);
    free(criteriaValues);
}



//возвращает значение ’истина’, если
//матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix *m) {
    return (m->nCols == m->nRows);
}

// возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противно
bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) {
        return false;
    }
    for (int i = 0; i < m1->nRows; i++) {
        for (int j = 0; j < m1->nCols; j++) {
            if (m1->values[i][j] != m2->values[i][j]) {
                return false;
            }
        }
    }
    return true;
}

//возвращает значение ’истина’, если матрица
//m является единичной, ложь – в противном случае.
bool isEMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }
    int n = m->nRows;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == j) != m->values[i][j]) {
                return false;
            }
        }
    }
    return true;
}

//возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < i; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }

    return true;
}

//транспонирует квадратную
//матрицу m.
void transposeSquareMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            int temp = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = temp;
        }
    }
}

//транспонирует матрицу m.
void transposeMatrix(matrix *m) {
    matrix t = getMemMatrix(m->nRows, m->nCols);
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            t.values[j][i] = m->values[i][j];
        }
    }
    freeMemMatrix(&m);
    *m = t;
}

//возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m) {
    position min_pos = {0, 0};
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (m.values[i][j] <
                m.values[min_pos.rowIndex][min_pos.colIndex])
                min_pos = (position){i, j};
    return min_pos;
}

//возвращает позицию максимального элемента матрицы m.
position getMaxValuePos(matrix m){
    int maxVal = m.values[0][0];
    position maxPos = {0, 0};
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > maxVal) {
                maxVal = m.values[i][j];
                maxPos.rowIndex = i;
                maxPos.colIndex = j;
            }
        }
    }
    return maxPos;
}

// возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;

    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

//возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных
//в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}

// функция-критерий для сравнения строк по минимальному элементу
int getMin(int const * a, int n) {
    assert(n > 0);
    int min = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < min)
            min = a[i];
    return min;
}

//сортирует строки по неубывнию наибольших элементов строк
void sortRowsByMaxElement(matrix a) {
    int *max = (int*)malloc(sizeof(int) * a.nRows);
    for (int i = 0; i < a.nRows; i++)
        max[i] = getMax(a.values[i], a.nCols);
    for (int i = 0; i < a.nRows; i++) {
        int minIndex = i;
        for (int j = i + 1; j < a.nRows; j++)
            if (max[j] < max[minIndex])
                minIndex = j;
        if (i != minIndex) {
            swap(&max[i], &max[minIndex]);
            swapRows(&a, i, minIndex);
        }
    }
    free(max);
}

//упорядочивает столбцы матрицы по неубыванию минимальных элементов столбцов
void sortColsByMinElemnt(matrix a, int (*criteria)(int const*, int)) {
    int *criteriaValues = (int*)malloc(sizeof(int) * a.nCols);
    int *column = (int*)malloc(sizeof(int) * a.nRows);
    for (int j = 0; j < a.nCols; j++) {
        for (int i = 0; i < a.nRows; i++)
            column[i] = a.values[i][j];
        criteriaValues[j] = criteria(column, a.nCols);
    }
    for (int i = 0; i < a.nCols; i++) {
        int minIndex = i;
        for (int j = i + 1; j < a.nCols; j++)
            if (criteriaValues[j] < criteriaValues[minIndex])
                minIndex = j;
        if (i != minIndex) {
            swap(&criteriaValues[i], &criteriaValues[minIndex]);
            swapColumns(a, i, minIndex);
        }
    }
    free(column);
    free(criteriaValues);
}

//умножает матрицы
matrix mulMatrices(matrix m1, matrix m2) {
    if (m1.nCols != m2.nRows) {
        // Матрицы нельзя перемножить
        matrix result = {NULL, 0, 0};
        return result;
    }

    matrix result;
    result.nRows = m1.nRows;
    result.nCols = m2.nCols;

    result.values = (int **)malloc(result.nRows * sizeof(int *));
    for (int i = 0; i < result.nRows; i++) {
        result.values[i] = (int *)malloc(result.nCols * sizeof(int));
    }

    for (int i = 0; i < result.nRows; i++) {
        for (int j = 0; j < result.nCols; j++) {
            result.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return result;
}

//Если матрица симметрична, получите квадрат матрицы
matrix getSquareOfMatrixIfSymmetric(matrix m) {
    if (!isSymmetricMatrix(&m)) {
        return mulMatrices(m, m);
    }
}

//проверяет элементы на уникальность
bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) {
                return false; // Найден повторяющийся элемент
            }
        }
    }
    return true; // Все элементы уникальны
}

//транспонирует матрицу, если среди сумм элементов строк матрицы нет равных
void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    int sum_rows[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        sum_rows[i] = getSum(m.values[i], m.nCols);
    }
    if (!isUnique(&sum_rows, m.nRows)){
        for (int i = 0; i < m.nRows; i++) {
            long long sum = getSum(m.values[i], m.nCols);
            for (int j = i + 1; j < m.nRows; j++) {
                if (sum != getSum(m.values[j], m.nCols)) {
                    transposeSquareMatrix(&m);
                    return;
                }
            }
        }
    }
}