#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "matrix.h"
#include <math.h>

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
        printf("\n");
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
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                return false; // Найден повторяющийся элемент
            }
        }
    }
    return true; // Все элементы уникальны
}

//транспонирует матрицу, если среди сумм элементов строк матрицы нет равных
void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long sum_rows[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        sum_rows[i] = getSum(m.values[i], m.nCols);
    }
    if (isUnique(&sum_rows, m.nRows)){
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

//определяет, являются ли две матрицы взаимообратными
bool isMutuallyInverseMatrices(matrix m1, matrix m2){
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols) {
        return false; // Матрицы должны иметь одинаковое количество строк и столбцов
    }

    // Проверка произведения матриц на равенство единичной матрице
    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            int sum = 0;
            for (int k = 0; k < m1.nCols; k++) {
                sum += m1.values[i][k] * m2.values[k][j];
            }
            if (i == j && sum != 1) {
                return false; // Элементы на главной диагонали должны быть равны 1
            } else if (i != j && sum != 0) {
                return false; // Элементы вне главной диагонали должны быть равны 0
            }
        }
    }

    return true; // Матрицы взаимнообратные
}

int max(int a, int b){
    return a > b ? a : b;
}

//находит сумму максимальных элементов всех псевдодиагоналей
long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    long long sum = 0;
    for (int i = 0; i < m.nRows; i++) {
        m.values[i][i] = 0;
    }

    for (int k = 0; k < m.nCols + m.nRows - 1; k++) {
        int maxInDiagonal = INT_MIN;
        int col = max(0, k - m.nRows + 1);
        int row = max(0, m.nRows - k - 1);

        while (col < m.nCols && row < m.nRows) {
            maxInDiagonal = max(maxInDiagonal, m.values[row][col]);
            col++;
            row++;
        }
        sum += maxInDiagonal;
    }

    return sum;
}

//находит минимальный элемент в выделенной области
int getMinInArea(matrix m){
    int maxRow = 0, maxCol = 0;
    int i, j;

    // Находим индексы максимального элемента
    for (i = 0; i < m.nRows; i++) {
        for (j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > m.values[maxRow][maxCol]) {
                maxRow = i;
                maxCol = j;
            }
        }
    }

    int min[m.nRows * m.nCols];
    // Находим минимальный элемент в "ёлочке"
    int minVal = m.values[maxRow][maxCol];
    for (i = 0; i <= maxRow; i++) {
        for (j = 0; j < m.nCols; j++) {
            int difference = abs(maxRow - i);
            if ((abs(maxCol - j)) <= difference) {
                if (m.values[i][j] < minVal) {
                    minVal = m.values[i][j];
                }
            }
        }
    }

    return minVal;
}

//вычисляет расстояние до начала координат
float getDistance(int *a, int n) {
    float distance = 0.0;
    for (int i = 0; i < n; i++) {
        distance += a[i] * a[i];
    }
    return sqrt(distance);
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    for (int i = 1; i < m.nRows; i++) {
        int *currentRow = m.values[i];
        int j = i - 1;
        while (j >= 0 && criteria(m.values[j], m.nCols) > criteria(currentRow, m.nCols)) {
            m.values[j + 1] = m.values[j];
            j--;
        }
        m.values[j + 1] = currentRow;
    }
}

//сортирует по расстоянию до начала координат
void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

//функция сравнения, которая используется в функции qsort() для сортировки массива long long
int cmp_long_long(const void *pa, const void *pb) {
    const long long *a = (const long long *)pa;
    const long long *b = (const long long *)pb;
    return (*a > *b) - (*a < *b);
}

// эта функция считает количество уникальных элементов в массиве a длиной n
int countNUnique(long long *a, int n) {
    int count = 0;
    long long prev = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] != prev) {
            count++;
            prev = a[i];
        }
    }
    return count + 1;
}

// эта функция считает количество эквивалентных классов по суммам строк в матрице m
int countEqClassesByRowsSum(matrix m) {
    long long sums[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        int sum = 0;
        for (int j = 0; j < m.nCols; j++) {
            sum += m.values[i][j];
        }
        sums[i] = sum;
    }

    qsort(sums, m.nRows, sizeof(long long), cmp_long_long);
    return countNUnique(sums, m.nRows);
}

//определяет количество особых элементов матрицы
int getNSpecialElement(matrix m) {
    int count = 0;

    for (int j = 0; j < m.nCols; j++) {
        for (int i = 0; i < m.nRows; i++) {
            int sum = 0;
            for (int k = 0; k < m.nRows; k++) {
                if (k != i) {
                    sum += m.values[k][j];
                }
            }

            if (m.values[i][j] > sum) {
                count++;
            }
        }
    }

    return count;
}

//ищет минимальный элемент в первой строке матрицы
position getLeftMin(matrix m) {
    position minPos;
    minPos.rowIndex = 0;
    minPos.colIndex = 0;
    int minValue = m.values[0][0];
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minPos.rowIndex = i;
                minPos.colIndex = j;
            }
        }
    }
    return minPos;
}

//заменяет предпоследнюю строку матрицы первым из столбцов, в котором находится минимальный элемент матрицы
void swapPenultimateRow(matrix m) {
    position minPos = getLeftMin(m);
    int element = m.values[m.nRows - (m.nRows - 1)][minPos.colIndex];
    for (int i = 0; i < m.nCols; i++) {
        m.values[m.nRows - 2][i] = m.values[i][minPos.colIndex];
    }
    m.values[m.nRows - 2][1] = element;
}

//Возвращает - "истина", если матрица отсортирована, иначе - "ложь"
bool isNonDescendingSorted(int *a, int n) {
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i-1]) {
            return false;
        }
    }
    return true;
}

//Если хотя бы одна
//строка не является неубывающей, функция возвращает false,
//иначе возвращает true.
bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        if (!isNonDescendingSorted(m.values[i], m.nCols)) {
            return false;
        }
    }
    return true;
}

//Определяет число матриц, строки которых упорядочены по неубыванию элементов
int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int count = 0;
    for (int i = 0; i < nMatrix; i++) {
        if (hasAllNonDescendingRows(ms[i])) {
            count++;
        }
    }

    return count;
}

//Счетчик значений
int countValues(const int *a, int n, int value) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == value) {
            count++;
        }
    }
    return count;
}

//Cчетчик нолевых строк
int countZeroRows(matrix m) {
    int count = 0;
    for (int i = 0; i < m.nRows; i++) {
        int zeroCount = countValues(m.values[i], m.nCols, 0);
        if (zeroCount == m.nCols) {
            count++;
        }
    }
    return count;
}

//Выводит матрицы, имеющие наибольшее
//число нулевых строк
void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int maxZeroRows = 0;
    for (int i = 0; i < nMatrix; i++) {
        int zeroRows = countZeroRows(ms[i]);
        if (zeroRows > maxZeroRows) {
            maxZeroRows = zeroRows;
        }
    }
    for (int i = 0; i < nMatrix; i++) {
        if (countZeroRows(ms[i]) == maxZeroRows)
            outputMatrix(ms[i]);
        printf("\n");
    }
}

//Находит макс. норму матрицы
int getMaxNorm(matrix m) {
    int maxNorm = 0;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            int absValue = abs(m.values[i][j]);
            if (absValue > maxNorm) {
                maxNorm = absValue;
            }
        }
    }
    return maxNorm;
}

//Выводит матрицы с наименьшей нормой.
void printMatricesWithMinNorm(matrix *ms, int nMatrix) {
    int minNorm = getMaxNorm(ms[0]);
    for (int i = 1; i < nMatrix; i++) {
        int norm = getMaxNorm(ms[i]);
        if (norm < minNorm) {
            minNorm = norm;
        }
    }

    for (int i = 0; i < nMatrix; i++) {
        if (getMaxNorm(ms[i]) == minNorm) {
            outputMatrix(ms[i]);
            printf("\n");
        }
    }
}

int min2(int a, int b) {
    return (a < b) ? a : b;
}

//определяет количество особых элементов в матрице
int getNSpecialElement2(matrix m) {
    int special_elements = 0;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            int is_special = 1;
            // Проверяем элемент на "особенность"
            for (int k = 0; k < j; k++) {
                if (m.values[i][k] >= m.values[i][j]) {
                    is_special = 0;
                    break;
                }
            }
            for (int k = j + 1; k < m.nCols; k++) {
                if (m.values[i][k] <= m.values[i][j]) {
                    is_special = 0;
                    break;
                }
            }
            if (is_special) {
                special_elements++;
            }
        }
    }
    return special_elements - 2;
}

//принимает два массива целых чисел a и b и их длину n, и возвращает скалярное произведение этих векторов.
double getScalarProduct(int *a, int *b, int n) {
    double product = 0;
    for (int i = 0; i < n; i++) {
        product += a[i] * b[i];
    }
    return product;
}

//принимает массив целых чисел a и его длину n, и возвращает длину вектора.
double getVectorLength(int *a, int n) {
    double length = 0;
    for (int i = 0; i < n; i++) {
        length += a[i] * a[i];
    }
    return sqrt(length);
}

//принимает два массива целых чисел a и b и их длину n, и возвращает косинус угла между векторами.
double getCosine(int *a, int *b, int n) {
    double product = getScalarProduct(a, b, n);
    double lengthA = getVectorLength(a, n);
    double lengthB = getVectorLength(b, n);

    if (lengthA == 0 || lengthB == 0) {
        return -1; // Error: Division by zero
    }

    return product / (lengthA * lengthB);
}

//принимает матрицу m и массив целых чисел b,
// и возвращает индекс вектора из матрицы m,
// у которого угол между ним и вектором b максимален.
int getVectorIndexWithMaxAngle(matrix m, int *b) {
    int maxIndex = -1;
    double maxAngle = -2;

    for (int i = 0; i < m.nRows; i++) {
        double angle = getCosine(b, m.values[i], m.nCols);
        if (angle > maxAngle) {
            maxAngle = angle;
            maxIndex = i;
        }
    }

    return maxIndex;
}