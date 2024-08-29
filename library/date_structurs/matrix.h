#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include <stdbool.h>
#include <stddef.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

// функция-критерий для сравнения строк по сумме элементов
long long getSum(int *a, int nCols);

// функция-критерий для сравнения строк по максимальному элементу
int getMax(int* a, int n);

//размещает в динамической памяти матрицу размером nRows на nCols
matrix getMemMatrix(int nRows, int nCols);

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols.
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

//освобождает память, выделенную под хранение матрицы m.
void freeMemMatrix(matrix *m);

//освобождает память, выделенную под хранение массива ms из nMatrices матриц.
void freeMemMatrices(matrix *ms, int nMatrices);

//ввод матрицы m.
void inputMatrix(matrix *m);

//ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices);

// вывод матрицы m.
void outputMatrix(matrix m);

//вывод массива из nMatrices матриц, хранящейся по адресу ms.
void outputMatrices(matrix *ms, int nMatrices);

// обмен строк с порядковыми номерами i1 и i2 в матрице m.
void swapRows(matrix *m, int i1, int i2);

//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix m, int j1, int j2);

// выполняет сортировку вставками строк
//матрицы m по неубыванию значения функции criteria применяемой для строк
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int));

//выполняет сортировку выбором столбцов
//матрицы m по неубыванию значения функции criteria применяемой для столбцов
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int));

//возвращает значение ’истина’, если
//матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix *m);

// возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противно
bool areTwoMatricesEqual(matrix *m1, matrix *m2);

//возвращает значение ’истина’, если матрица
//m является единичной, ложь – в противном случае.
bool isEMatrix(matrix *m);

//возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix *m);

//транспонирует квадратную
//матрицу m.
void transposeSquareMatrix(matrix *m);

//транспонирует матрицу m.
void transposeMatrix(matrix *m);

//возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m);

//возвращает позицию максимального элемента матрицы m.
position getMaxValuePos(matrix m);

// возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols);

//возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных
//в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);

// функция-критерий для сравнения строк по минимальному элементу
int getMin(int const * a, int n);

//сортирует строки по неубывнию наибольших элементов строк
void sortRowsByMaxElement(matrix a);

void swap(int *a, int *b);

//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix m, int j1, int j2);

//упорядочивает столбцы матрицы по неубыванию минимальных элементов столбцов
void sortColsByMinElemnt(matrix a, int (*criteria)(int const*, int));

//умножает матрицы
matrix mulMatrices(matrix m1, matrix m2);

//Если матрица симметрична, получите квадрат матрицы
matrix getSquareOfMatrixIfSymmetric(matrix m);

//проверяет элементы на уникальность
bool isUnique(long long *a, int n);

//транспонирует матрицу, если среди сумм элементов строк матрицы нет равных
void transposeIfMatrixHasNotEqualSumOfRows(matrix m);

//определяет, являются ли две матрицы взаимообратными
bool isMutuallyInverseMatrices(matrix m1, matrix m2);

//находит сумму максимальных элементов всех псевдодиагоналей
long long findSumOfMaxesOfPseudoDiagonal(matrix m);

//находит минимальный элемент в выделенной области
int getMinInArea(matrix m);

//вычисляет расстояние до начала координат
float getDistance(int *a, int n);

//сортирует по расстоянию до начала координат
void sortByDistances(matrix m);

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int));

// эта функция считает количество эквивалентных классов по суммам строк в матрице m
int countEqClassesByRowsSum(matrix m);

// эта функция считает количество уникальных элементов в массиве a длиной n
int countNUnique(long long *a, int n);

//определяет количество особых элементов матрицы
int getNSpecialElement(matrix m);

//ищет минимальный элемент в первой строке матрицы
position getLeftMin(matrix m);

//заменяет предпоследнюю строку матрицы первым из столбцов, в котором находится минимальный элемент матрицы
void swapPenultimateRow(matrix m);

//Возвращает - "истина", если матрица отсортирована, иначе - "ложь"
bool isNonDescendingSorted(int *a, int n);

//Если хотя бы одна
//строка не является неубывающей, функция возвращает false,
//иначе возвращает true.
bool hasAllNonDescendingRows(matrix m);

//Определяет число матриц, строки которых упорядочены по неубыванию элементов
int countNonDescendingRowsMatrices(matrix *ms, int nMatrix);

//Счетчик значений
int countValues(const int *a, int n, int value);

//Cчетчик нолевых строк
int countZeroRows(matrix m);

//Выводит матрицы, имеющие наибольшее
//число нулевых строк
void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix);

//Находит макс. норму матрицы
int getMaxNorm(matrix m);

//Выводит матрицы с наименьшей нормой.
void printMatricesWithMinNorm(matrix *ms, int nMatrix);

//определяет количество особых элементов в матрице
int getNSpecialElement2(matrix m);

//принимает два массива целых чисел a и b и их длину n, и возвращает скалярное произведение этих векторов.
double getScalarProduct(int *a, int *b, int n);

//принимает массив целых чисел a и его длину n, и возвращает длину вектора.
double getVectorLength(int *a, int n);

//принимает два массива целых чисел a и b и их длину n, и возвращает косинус угла между векторами.
double getCosine(int *a, int *b, int n);

//принимает матрицу m и массив целых чисел b,
// и возвращает индекс вектора из матрицы m,
// у которого угол между ним и вектором b максимален.
int getVectorIndexWithMaxAngle(matrix m, int *b);

//вычисляет скалярное произведение строки i и столбца j матрицы m
long long getScalarProductRowAndCol(matrix m, int i, int j);

//Находит скалярное произведение строки,
// в которой находится наибольший элемент матрицы, на столбец с наименьшим элементом.
long long getSpecialScalarProduct(matrix m);

#endif
