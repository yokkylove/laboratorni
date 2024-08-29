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

//проверяет работоспособность функции atVector.
void test_atVector_notEmptyVector1() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(&(v.data[0]) == atVector(&v, 0));
}

//проверяет работоспособность функции atVector.
void test_atVector_notEmptyVector2() {
    vector v = createVector(0);
    pushBack(&v, 10);
    pushBack(&v, 11);
    pushBack(&v, 12);
    assert(&(v.data[2]) == atVector(&v, 2));
    assert(v.data[1] == 11);
}

//проверяет работоспособность функции atVector.
void test_atVector_requestToLastElement1() {
    vector v = createVector(0);
    pushBack(&v, 10);
    pushBack(&v, 11);
    pushBack(&v, 12);
    assert(&(v.data[2]) == atVector(&v, 2));
    assert(v.data[2] == 12);
}

//проверяет работоспособность функции atVector.
void test_atVector_requestToLastElement2() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(&(v.data[0]) == atVector(&v, 0));
    assert(v.data[0] == 10);
}

//проверяет работоспособность функции atVector.
void test_atVector_requestToLastElement3() {
    vector v = createVector(0);
    pushBack(&v, 10);
    pushBack(&v, 15);
    popBack(&v);
    assert(&(v.data[0]) == atVector(&v, 0));
    assert(v.data[0] == 10);
}

//проверяет работоспособность функции back.
void test_back_ElementsInVector1() {
    vector v = createVector(0);
    pushBack(&v, 25);
    pushBack(&v, 2);
    pushBack(&v, 2003);
    assert(&(v.data[2]) == back(&v));
    assert(v.data[2] == 2003);
}

//проверяет работоспособность функции back.
void test_back_ElementsInVector2() {
    vector v = createVector(0);
    pushBack(&v, 25);
    pushBack(&v, 2);
    pushBack(&v, 2003);
    popBack(&v);
    assert(&(v.data[1]) == back(&v));
    assert(v.data[v.size - 1] == 2);
}

//проверяет работоспособность функции back.
void test_back_oneElementInVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(&(v.data[0]) == back(&v));
    assert(v.data[0] == 10);
}

//проверяет работоспособность функции front.
void test_front_oneElementInVector() {
    vector v = createVector(0);
    pushBack(&v, 25);
    assert(&(v.data[0]) == front(&v));
    assert(v.data[0] == 25);
}

//проверяет работоспособность функции front.
void test_front_elementsInVector() {
    vector v = createVector(0);
    pushBack(&v, 25);
    pushBack(&v, 22);
    pushBack(&v, 1);
    assert(&(v.data[0]) == front(&v));
    assert(v.data[0] == 25);
}

void test_atVector(){
    test_atVector_notEmptyVector1();
    test_atVector_notEmptyVector2();
    test_atVector_requestToLastElement1();
    test_atVector_requestToLastElement2();
    test_atVector_requestToLastElement3();
}

void test_back(){
    test_back_ElementsInVector1();
    test_back_ElementsInVector2();
    test_back_oneElementInVector();
}

void test_front(){
    test_front_elementsInVector();
    test_front_oneElementInVector();
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
    test_front();
    test_back();
    test_atVector();
}

int main(){
    test();

    return 0;
}