#include <stdio.h>
#include "matrix.h"
#include <assert.h>
#include <malloc.h>

void test_for_getMatrix1 () {
    matrix m = getMemMatrix(3, 3);
    assert(m.nCols == 3);
    assert(m.nRows == 3);
    assert(m.values != NULL);
}

void test_for_getMatrix2 () {
    matrix m = getMemMatrix(8, 1);
    assert(m.nCols == 1);
    assert(m.nRows == 8);
    assert(m.values != NULL);
}

void test_getMatrix () {
    test_for_getMatrix1();
    test_for_getMatrix2();
}

void test_for_getArrayOfMatrices1 () {
    int nMatrices = 4;
    matrix *ms = getMemArrayOfMatrices(nMatrices, 4, 6);
    for (int i = 0; i < nMatrices; i++) {
        assert(ms[i].nCols == 6);
        assert(ms[i].nRows == 4);
        assert(ms[i].values != NULL);
    }
}

void test_for_getArrayOfMatrices2 () {
    int nMatrices = 8;
    matrix *ms = getMemArrayOfMatrices(nMatrices, 9, 10);
    for (int i = 0; i < nMatrices; i++) {
        assert(ms[i].nCols == 10);
        assert(ms[i].nRows == 9);
        assert(ms[i].values != NULL);
    }
}

void test_getArrayOfMatrices () {
    test_for_getArrayOfMatrices1();
    test_for_getArrayOfMatrices2();
}

void test_for_freeMatrix1 () {
    int a[] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    matrix m = createMatrixFromArray(&a, 3, 3);
    freeMemMatrix(&m);
    assert(m.values != NULL);
}

void test_for_freeMatrix2 () {
    int a[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    matrix m = createMatrixFromArray(&a, 2, 5);
    freeMemMatrix(&m);
    assert(m.values != NULL);
}

void test_freeMatrix () {
    test_for_freeMatrix1();
    test_for_freeMatrix2();
}

void test_for_freeMatrices1 () {
    matrix m1;
    m1.nRows = 2;
    m1.nCols = 2;
    m1.values = malloc(sizeof(int) * m1.nRows * m1.nCols);

    matrix m2;
    m2.nRows = 3;
    m2.nCols = 3;
    m2.values = malloc(sizeof(int) * m2.nRows * m2.nCols);

    matrix m3;
    m3.nRows = 4;
    m3.nCols = 4;
    m3.values = malloc(sizeof(int) * m3.nRows * m3.nCols);
    int nMatrices = 3;
    matrix ms[3] = {m1, m2, m3};

    freeMemMatrices(ms, nMatrices);

    for (int i = 0; i < nMatrices; i++) {
        assert(ms[i].values != NULL);
    }
}

void test_for_freeMatrices2 () {
    matrix m1;
    m1.nRows = 9;
    m1.nCols = 1;
    m1.values = malloc(sizeof(int) * m1.nRows * m1.nCols);

    matrix m2;
    m2.nRows = 10;
    m2.nCols = 10;
    m2.values = malloc(sizeof(int) * m2.nRows * m2.nCols);

    matrix m3;
    m3.nRows = 7;
    m3.nCols = 23;
    m3.values = malloc(sizeof(int) * m3.nRows * m3.nCols);
    int nMatrices = 3;
    matrix ms[3] = {m1, m2, m3};

    freeMemMatrices(ms, nMatrices);

    for (int i = 0; i < nMatrices; i++) {
        assert(ms[i].values != NULL);
    }
}

void test_freeMatrices () {
    test_for_freeMatrix1();
    test_for_freeMatrix2();
}

void test_swapRows() {
    matrix a = createMatrixFromArray((int[]) {5,3,6,
                                              7,8,5,
                                              4,1,2},
                                     3,3);
    matrix b = createMatrixFromArray((int[]) {4,1,2,
                                              7,8,5,
                                              5,3,6},
                                     3,3);
    swapRows(&a, 0, 2);
    for (int i = 0; i < a.nRows; i++) {
        for (int j = 0; j < a.nCols; j++) {
            assert(a.values[i][j] == b.values[i][j]);
        }
    }
    freeMemMatrix(&a);
    freeMemMatrix(&b);
}

void test_swapCols() {
    matrix a = createMatrixFromArray((int[]) {5, 3, 6,
                                              7, 8, 5,
                                              4, 1, 2},
                                     3, 3);
    matrix b = createMatrixFromArray((int[]) {6, 3, 5,
                                              5, 8, 7,
                                              2, 1, 4},
                                     3, 3);
    swapColumns(a, 0, 2);
    for (int i = 0; i < a.nRows; i++) {
        for (int j = 0; j < a.nCols; j++) {
            assert(a.values[i][j] == b.values[i][j]);
        }
    }
    freeMemMatrix(&a);
    freeMemMatrix(&b);
}

void test_insertionSortRowsMatrixByRowCriteria () {
    int a[] = {5, 2, 1, 4, 3, 7, 6, 9, 0, 8, 2, 5};
    matrix m = createMatrixFromArray(&a, 3, 4);
    int b[] = {3, 7, 6, 9,0, 8, 2, 5, 5, 2, 1, 4,};
    matrix h = createMatrixFromArray(&b, 3, 4);

    insertionSortRowsMatrixByRowCriteria(m, getSum);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_selectionSortColsMatrixByColCriteria() {
    matrix a = createMatrixFromArray((int[]) {4, 3, 1, 2,
                                              2, 4, 3, 1,
                                              1, 2, 4, 3},
                                     3, 4);
    matrix b = createMatrixFromArray((int[]) {2, 4, 1, 3,
                                              1, 2, 3, 4,
                                              3, 1, 4, 2},
                                     3, 4);
    selectionSortColsMatrixByColCriteria(a, getSum);
    for (int i = 0; i < a.nRows; i++) {
        for (int j = 0; j < a.nCols; j++) {
            assert(a.values[i][j] == b.values[i][j]);
        }
    }
    freeMemMatrix(&a);
    freeMemMatrix(&b);
}

void test_isSquareMatrix() {
    matrix a = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},
                                     3, 3);
    assert(isSquareMatrix(&a) == true);
    matrix b = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6},
                                     2, 3);
    assert(isSquareMatrix(&b) == false);
    matrix c = createMatrixFromArray((int[]) {1, 2, 3},
                                     1, 3);
    assert(isSquareMatrix(&c) == false);
    matrix d = createMatrixFromArray((int[]) {1,
                                              2,
                                              3},
                                     3, 1);
    assert(isSquareMatrix(&d) == false);
    freeMemMatrix(&a);
    freeMemMatrix(&b);
    freeMemMatrix(&c);
    freeMemMatrix(&d);
}

void test_areTwoMatricesEqual() {
    matrix a = createMatrixFromArray((int[]) {1, 2, 3, 4,
                                              5, 6, 7, 8},
                                     2, 4);
    matrix b = createMatrixFromArray((int[]) {1, 2, 3, 4,
                                              5, 6, 7, 8},
                                     2, 4);
    assert(areTwoMatricesEqual(&a, &b));

    b.values[0][0] = 0;
    assert(!areTwoMatricesEqual(&a, &b));

    freeMemMatrix(&a);
    freeMemMatrix(&b);
}

void test_isEMatrix() {
    matrix a = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1},
                                     3, 3);
    matrix b = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 0},
                                     3, 3);
    matrix c = createMatrixFromArray((int[]) {1, 0, 0, 0,
                                              0, 1, 0, 0,
                                              0, 0, 1, 0},
                                     3, 4);

    assert(isEMatrix(&a) == true);
    assert(isEMatrix(&b) == false);
    assert(isEMatrix(&c) == false);

    freeMemMatrix(&a);
    freeMemMatrix(&b);
    freeMemMatrix(&c);
}

void test_isSymmetricMatrix() {
    matrix symmetric = createMatrixFromArray((int[]) {1, 2, 3,
                                                      2, 4, 5,
                                                      3, 5, 6},
                                             3, 3);
    assert(isSymmetricMatrix(&symmetric) == true);
    matrix asymmetric = createMatrixFromArray((int[]) {1, 2, 3,
                                                       4, 5, 6,
                                                       7, 8, 9},
                                              3, 3);
    assert(isSymmetricMatrix(&asymmetric) == false);
    freeMemMatrix(&symmetric);
    freeMemMatrix(&asymmetric);
}

void test_transposeSquareMatrix() {
    matrix a = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},
                                     3, 3);
    matrix b = createMatrixFromArray((int[]) {1, 4, 7,
                                              2, 5, 8,
                                              3, 6, 9},
                                     3, 3);
    transposeSquareMatrix(&a);
    for (int i = 0; i < a.nRows; i++) {
        for (int j = 0; j < a.nCols; j++) {
            assert(a.values[i][j] == b.values[i][j]);
        }
    }
    freeMemMatrix(&a);
    freeMemMatrix(&b);
}

void test_transposeMatrix() {
    matrix a = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},
                                     3, 3);
    matrix b = createMatrixFromArray((int[]) {1, 4, 7,
                                              2, 5, 8,
                                              3, 6, 9},
                                     3, 3);
    transposeMatrix(&a);
    assert(a.nRows == b.nRows);
    assert(a.nCols == b.nCols);
    for (int i = 0; i < a.nRows; i++)
        for (int j = 0; j < a.nCols; j++)
            assert(a.values[i][j] == b.values[i][j]);
    freeMemMatrix(&a);
    freeMemMatrix(&b);
}

void test_getMinValuePos() {
    matrix a = createMatrixFromArray((int[]) {5, 3, 6,
                                              7, 8, 5,
                                              4, 1, 2},
                                     3, 3);
    position expectedPos = {2, 1};
    position minPos = getMinValuePos(a);
    assert(minPos.rowIndex == expectedPos.rowIndex &&
           minPos.colIndex == expectedPos.colIndex);
    freeMemMatrix(&a);
}

void test_getMaxValuePos() {
    matrix a = createMatrixFromArray((int[]) {5, 3, 6,
                                              7, 8, 5,
                                              4, 1, 2},
                                     3, 3);
    position expectedPos = {2, 1};
    position maxPos = getMaxValuePos(a);
    assert(maxPos.rowIndex == expectedPos.rowIndex &&
           maxPos.colIndex == expectedPos.colIndex);
    freeMemMatrix(&a);
}

void test() {
    test_getMatrix();
    test_getArrayOfMatrices();
    test_freeMatrix();
    test_freeMatrices();
    test_swapRows();
    test_swapCols();
    test_insertionSortRowsMatrixByRowCriteria();
    test_selectionSortColsMatrixByColCriteria();
    test_isSquareMatrix();
    test_areTwoMatricesEqual();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_transposeSquareMatrix();
    test_transposeMatrix();
    test_getMinValuePos();
    test_getMaxValuePos();
}

