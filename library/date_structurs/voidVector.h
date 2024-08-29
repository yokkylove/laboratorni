#ifndef GG_VOIDVECTOR_H
#define GG_VOIDVECTOR_H

#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct vectorVoid {
    void *data; // указатель на нулевой элемент вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
    size_t baseTypeSize; // размер базового типа:
                        // например, если вектор хранит int -
                        // то поле baseTypeSize = sizeof(int)
                        // если вектор хранит float -
                        // то поле baseTypeSize = sizeof(float)
} vectorVoid;

//возвращает структуру-дескриптор вектор из n значений.
vectorVoid createVectorV(size_t n, size_t baseTypeSize);

//изменяет количество памяти, выделенное под хранение элементов вектора.
void reserveV(vectorVoid *v, const size_t newCapacity);

//освобождает память, выделенную поднеиспользуемые элементы.
void shrinkToFitV(vectorVoid *v);

//удаляет элементы из контейнера, но не освобождает выделенную память.
void clearV(vectorVoid *v);

//освобождает память, выделенную вектору.
void deleteVectorV(vectorVoid *v);

//проверка на то, является ли вектор пустым.
bool isEmptyV(vectorVoid *v);

//проверка на то, является ли вектор полным.
bool isFullV(vectorVoid *v);

//возвращает i-ый элемент вектора v.
void getVectorValueV(vectorVoid *v, size_t index, void *destination);

//записывает на index-ый элемент вектора v значение, расположенное
//по адресу source.
void setVectorValueV(vectorVoid *v, size_t index, void *source);

//удаляет последний элемент из вектора.
void popBackV(vectorVoid *v);

//добавляет элемент x в конец вектора v.
void pushBackV(vectorVoid *v, void *source);

#endif //GG_VOIDVECTOR_H
