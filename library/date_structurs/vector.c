#include <stdio.h>
#include <malloc.h>
#include "vector.h"

//возвращает структуру-дескриптор вектор из n значений.
vector createVector(size_t n){
    vector res = {(int *) malloc(sizeof(int) * n), 0, n};
    if (res.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
        }
    return res;
}

//изменяет количество памяти, выделенное под хранение элементов вектора.
void reserve(vector *v, size_t newCapacity){
    if (newCapacity == 0) {
        v->data = NULL;
    } else {
        v->data = (int *) realloc(v->data, sizeof(int) * newCapacity);
    }
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    if (v->size > newCapacity) {
        v->size = newCapacity;
    }
    v->capacity = newCapacity;
}


//удаляет элементы из контейнера, но не освобождает выделенную память.
void clear(vector *v){
    v->size = 0;
}

//освобождает память, выделенную поднеиспользуемые элементы.
void shrinkToFit(vector *v){
    reserve(v, v->size);
}

//освобождает память, выделенную вектору.
void deleteVector(vector *v){
    free(v->data);
}

