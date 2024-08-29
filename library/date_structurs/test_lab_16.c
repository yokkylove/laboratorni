#include <assert.h>
#include "matrix.h"
#include "matrix_lab_16.h"


void test_for_firstTask_1 () {
    int a[] = {1, 2, 3, 4, 5, 6,7 ,8 ,9};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {7, 8, 9, 4, 5, 6, 1, 2, 3};
    matrix h = createMatrixFromArray(&b, 3, 3);
    firstTask(&m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_for_firstTask_2 () {
    int a[] = {2, 34, 5, 1, 6, 7, 8, 23, 8};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {1, 6, 7,2, 34, 5, 8, 23, 8};
    matrix h = createMatrixFromArray(&b, 3, 3);
    firstTask(&m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_firstTask () {
    test_for_firstTask_1();
    test_for_firstTask_2();
}

void test_for_secondTask_1 () {
    int a[] = {2, 34, 5, 1, 6, 7, 8, 23, 8};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {1, 6, 7,8, 23, 8, 2, 34, 5, };
    matrix h = createMatrixFromArray(&b, 3, 3);
    secondTask(m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_for_secondTask_2 () {
    int a[] = {42, 56, 1, 23, 98, 34,9,3,4};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {9,3,4,42,56,1,23,98,34};
    matrix h = createMatrixFromArray(&b, 3, 3);
    secondTask(m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_secondTask () {
    test_for_secondTask_1();
    test_for_secondTask_2();
}

void test_for_thirdTask_1 () {
    int a[] = {22, 3, 1, 3, 5,77, 89, 45,2};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {1, 3, 22, 77, 5, 3, 2, 45, 89};
    matrix h = createMatrixFromArray(&b, 3, 3);
    thirdTask(m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_for_thirdTask_2 () {
    int a[] = {35,23,53,245,2345,3245,23453,455,345};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {23, 35, 53, 2345, 245, 3245, 455, 23453, 345};
    matrix h = createMatrixFromArray(&b, 3, 3);
    thirdTask(m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_thirdTask () {
    test_for_thirdTask_1();
    test_for_thirdTask_2();
}

void test_for_fourthTask_1 () {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
    m = fourthTask(m);
    matrix h = createMatrixFromArray(&b, 3, 3);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_for_fourthTask_2 () {
    int a[] = {9, 8,7,6,5,4,3,2,1};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {150, 126, 102, 96, 81, 66, 42, 36, 30};
    m = fourthTask(m);
    matrix h = createMatrixFromArray(&b, 3, 3);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_fourthTask () {
    test_for_fourthTask_1();
    test_for_fourthTask_2();
}

void test_for_fifthTask_1 () {
    int a[] = {1,2,3,4,5,6,7,8,9};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {1,4,7,2,5,8,3,6,9};
    matrix h = createMatrixFromArray(&b, 3, 3);
    fifthTask(&m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_for_fifthTask_2 () {
    int a[] = {2,34,234,24,2,34,2,345, 7};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {2,24,2,34,2,345,234,34,7};
    matrix h = createMatrixFromArray(&b, 3, 3);
    fifthTask(&m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_fifthTask () {
    test_for_fifthTask_1();
    test_for_fifthTask_2();
}

void test_for_sixthTask_1 () {
    int a[] = {2,34,234,24,2,34,2,345, 7};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {2,24,2,34,2,345,234,34,7};
    matrix h = createMatrixFromArray(&b, 3, 3);
    assert(!sixthTask(m, h));
}

void test_for_sixthTask_2 () {
    int a[] = {2,1,1,1};
    matrix m = createMatrixFromArray(&a, 2, 2);
    int b[] = {1, -1, -1, 2};
    matrix h = createMatrixFromArray(&b, 2, 2);
    assert(sixthTask(m, h));
}

void test_sixthTask () {
    test_for_sixthTask_1();
    test_for_sixthTask_2();
}

void test_for_seventhTask_1 () {
    int a[] = {3,2,5,4,1,3,6,3,3,2,1,2};
    matrix m = createMatrixFromArray(&a, 3, 4);
    long long res = seventhTask(m);
    assert(res == 20);
}

void test_for_seventhTask_2 () {
    int a[] = {2,34,234,24,2,34,2,345, 7,23,22,34};
    matrix m = createMatrixFromArray(&a, 3, 4);
    long long res = seventhTask(m);
    assert(res == 433);
}

void test_seventhTask () {
    test_for_seventhTask_1();
    test_for_seventhTask_2();
}

void test_for_eightTask_1 () {
    int a[] = {10,7,5,6,3,11,8,9,4,1,12,2};
    matrix m = createMatrixFromArray(&a, 3, 4);
    int res = eighthTask(m);
    assert(res == 5);
}

void test_for_eightTask_2 () {
    int a[] = {6, 8,9,2,7,12,3,4,10,11,5,1};
    matrix m = createMatrixFromArray(&a, 3, 4);
    int res = eighthTask(m);
    assert(res == 6);
}

void test_eightTask () {
    test_for_eightTask_1();
    test_for_eightTask_2();
}

void test_for_ninthTask_1 () {
    int a[] = {6,8,9,2,7,12,3,4,10,11,5,1};
    matrix m = createMatrixFromArray(&a, 6, 2);
    int b[] = {3,4,5,1,9,2,6,8,7,12,10,11};
    matrix h = createMatrixFromArray(&b, 6, 2);
    ninthTask(m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_for_ninthTask_2 () {
    int a[] = {1,12,3,1,5,2,6,4,67,234,5,2};
    matrix m = createMatrixFromArray(&a, 6, 2);
    int b[] = {3,1,5,2,5,2,6,4,1,12,67,234};
    matrix h = createMatrixFromArray(&b, 6, 2);
    ninthTask(m);
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_ninthTask () {
    test_for_ninthTask_1();
    test_for_ninthTask_2();
}

void test_for_tenthTask_1(){
    int a[] = {7, 1,2, 7,5, 4,4, 3,1, 6,8,0};
    matrix m = createMatrixFromArray(&a, 6, 2);
    assert(tenthTask(m) == 3);
}

void test_for_tenthTask_2(){
    int a[] = {7, 7,2, 7,5, 4,4, 3,1, 6,8,0};
    matrix m = createMatrixFromArray(&a,6, 2);
    assert(tenthTask(m) == 4);
}

void test_tenthTask () {
    test_for_tenthTask_1();
    test_for_tenthTask_2();
}

void test_for_eleventhTask_1(){
    int a[] = {3, 5, 5, 4,2, 3, 6, 7,12, 2, 1, 2};
    matrix m = createMatrixFromArray(&a, 3, 4);
    assert(eleventhTask(m) == 2);
}

void test_for_eleventhTask_2(){
    int a[] = {3, 5, 5, 4,2, 15, 6, 7,12, 2, 1, 2};
    matrix m = createMatrixFromArray(&a, 3, 4);
    assert(eleventhTask(m) == 3);
}

void test_eleventhTask () {
    test_for_eleventhTask_1();
    test_for_eleventhTask_2();
}

void test_for_twelvethTask_1(){
    int a[] = {1, 2, 3,4, 5, 6,7, 8, 1};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {1, 2, 3,1, 4, 7,7, 8, 1};
    matrix h = createMatrixFromArray(&b, 3, 3);
    twelvethTask(m);
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_for_twelvethTask_2(){
    int a[] = {2, 1, 3,4, 5, 6,7, 8, 1};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[] = {2, 1, 3,1, 5, 8,7, 8, 1};
    matrix h = createMatrixFromArray(&b, 3, 3);
    twelvethTask(m);
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            assert(m.values[i][j] == h.values[i][j]);
        }
    }
}

void test_twelvethTask () {
    test_for_twelvethTask_1();
    test_for_twelvethTask_2();
}

void test_for_thirteenthTask_1 () {
    int a[] = {7, 1, 1, 1, 1,6,2,2,5,4,2,3,1,3,7,9};
    matrix *ms = createArrayOfMatrixFromArray(&a, 4, 2, 2);
    int res = thirteenthTask(ms, 4);
    assert(res == 2);
}

void test_for_thirteenthTask_2 () {
    int a[] = {2,3,3,3,134,1,421,515,1235,23,123,34,14,1,41,9};
    matrix *ms = createArrayOfMatrixFromArray(&a, 4, 2, 2);
    int res = thirteenthTask(ms, 4);
    assert(res == 1);
}

void test_thirteenthTask () {
    test_for_thirteenthTask_1();
    test_for_thirteenthTask_2();
}

void test_for_sixteenthTask_1(){
    int a[] = {2, 3, 5, 5, 4, 6, 2, 3, 8, 12, 12,12,2,1,2};
    matrix m = createMatrixFromArray(&a, 3, 5);
    assert(sixteenthTask(m) == 2);
}

void test_for_sixteenthTask_2(){
    int a[] = {2, 6, 5, 5, 4, 6, 2, 3, 8, 12, 12,12,2,1,2};
    matrix m = createMatrixFromArray(&a, 3, 5);
    assert(sixteenthTask(m) == 1);
}

void test_sixteenthTask () {
    test_for_sixteenthTask_1();
    test_for_sixteenthTask_2();
}

void test_for_seventeenthTask_1(){
    int a[] = {12,5,3,7,11,0,5,9,10};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[3] = {1, 2, 3};
    assert(seventeenthTask(m, &b) == 2);
}

void test_for_seventeenthTask_2(){
    int a[] = {1,5,33,7,41,67, 5,9,18};
    matrix m = createMatrixFromArray(&a, 3, 3);
    int b[3] = {7,8,9};
    assert(seventeenthTask(m, &b) == 2);
}

void test_seventeenthTask ()  {
    test_for_seventeenthTask_1();
    test_for_seventeenthTask_2();
}

void test_for_eightteenthTask_1(){
    int a[] = {1, 2, 3, 4,5,6,7,8,9};
    matrix m = createMatrixFromArray(&a, 3, 3);
    assert(eightteenthTask(m) == 102);
}

void test_for_eightteenthTask_2(){
    int a[] = {12,5,3,7,11,0,5,9,10};
    matrix m = createMatrixFromArray(&a, 3, 3);
    assert(eightteenthTask(m) == 66);
}

void test_eightteenthTask () {
    test_for_eightteenthTask_1();
    test_for_eightteenthTask_2();
}

void test () {
    test_firstTask();
    test_secondTask();
    test_thirdTask();
    test_fourthTask();
    test_fifthTask();
    test_sixthTask();
    test_seventhTask();
    test_eightTask();
    test_ninthTask();
    test_tenthTask();
    test_eleventhTask();
    test_thirteenthTask();
    test_sixteenthTask();
    test_seventeenthTask();
    test_eightteenthTask();
}

int main () {
    test();

    return 0;
}
