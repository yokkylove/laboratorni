#ifndef GG_VECTOR_H
#define GG_VECTOR_H

#include <stdint.h>
#include <stdbool.h>

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

//возвращает структуру-дескриптор вектор из n значений.
vector createVector(size_t n);

//изменяет количество памяти, выделенное под хранение элементов вектора.
void reserve(vector *v, size_t newCapacity);

//удаляет элементы из контейнера, но не освобождает выделенную память.
void clear(vector *v);

//освобождает память, выделенную поднеиспользуемые элементы.
void shrinkToFit(vector *v);

//освобождает память, выделенную вектору.
void deleteVector(vector *v);

//проверка на то, является ли вектор пустым
bool isEmpty(vector *v);

//проверка на то, является ли вектор полным
bool isFull(vector *v);

//возвращает i-ый элемент вектора v.
int getVectorValue(vector *v, size_t i);

//добавляет элемент x в конец вектора v.
void pushBack(vector *v, int x);

//удаляет последний элемент из вектора.
void popBack(vector *v);

#endif //GG_VECTOR_H