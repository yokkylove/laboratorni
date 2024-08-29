#include "vector.h"
#include <assert.h>

//проверяет функцию pushBack, когда вектор полный.
void test_pushBack_fullVector1() {
    vector v = createVector(0);
    assert(isEmpty(&v) == 1);
    pushBack(&v, 1);
    pushBack(&v, 2);
    assert(v.size == 2);
    assert(v.capacity == 2);
    assert(isFull(&v) == 1);
    assert(v.data[0] == 1);
    assert(v.data[1] == 2);
}

//проверяет функцию pushBack, когда вектор заполнен и нуждается в изменении размера.
void test_pushBack_fullVector2() {
    vector v = createVector(0);
    assert(isEmpty(&v) == 1);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);
    assert(v.size == 3);
    assert(v.capacity == 4);
    assert(isFull(&v) == 0);
    assert(v.data[0] == 1);
    assert(v.data[1] == 2);
    assert(v.data[2] == 3);
}

//проверяет функцию pushBack, когда capacity = 1.
void test_pushBack_fullVector3() {
    vector v = createVector(1);
    assert(isEmpty(&v) == 1);
    pushBack(&v, 1);
    assert(v.size == 1);
    assert(v.capacity == 1);
    assert(isFull(&v) == 1);
    assert(v.data[0] == 1);
}

//проверяет функцию pushBack, когда вектор полон и size = 3.
void test_pushBack_fullVector4() {
    vector v = createVector(0);
    assert(isEmpty(&v) == 1);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);
    shrinkToFit(&v);
    assert(v.size == 3);
    assert(v.capacity == 3);
    assert(isFull(&v) == 1);
    assert(v.data[0] == 1);
    assert(v.data[1] == 2);
    assert(v.data[2] == 3);
}

//проверяет функцию pushBack, когда вектор пуст и size = 1.
void test_pushBack_emptyVector1() {
    vector v = createVector(1);
    pushBack(&v, 1);
    assert(v.data[0] == 1);
    popBack(&v);
    assert(isEmpty(&v) == 1);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

//проверяет функцию pushBack, когда вектор пуст и size = 0.
void test_pushBack_emptyVector2() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 14);
    pushBack(&v, 12);
    assert(isEmpty(&v) == 0);
    assert(v.size == 3);
    assert(v.capacity == 4);
    assert(v.data[0] == 1);
    assert(v.data[1] == 14);
    assert(v.data[2] == 12);
}

//проверяет функцию popBack с непустым вектором.
void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_pushBack_fullVector(){
    test_pushBack_fullVector1();
    test_pushBack_fullVector2();
    test_pushBack_fullVector3();
    test_pushBack_fullVector4();
}

void test_pushBack_emptyVector(){
    test_pushBack_emptyVector1();
    test_pushBack_emptyVector2();
}

void test(){
    test_pushBack_fullVector();
    test_pushBack_emptyVector();
    test_popBack_notEmptyVector();
}

int main(){
    test();

    return 0;
}