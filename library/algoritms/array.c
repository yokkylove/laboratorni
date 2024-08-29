#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "array.h"

// ввод массива data размера n
void inputArray_(int * const a, const size_t n){
    for(size_t i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
}

// вывод массива data размера n
void outputArray_(const int * const a, const size_t n){
    for(size_t i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

// возвращает значение первого вхождения элемента x
// в массиве a размера n при его наличии, иначе - n
size_t linearSearch_(const int *a, const size_t n, int x) {
    for (size_t i = 0; i < n; i++) {
        if (a[i] == x) {
            return i;
        }
    }
}

// возвращает позицию вхождения элемента x
// в отсортированном массиве a размера n при его наличии, иначе - SIZE_MAX
size_t binarySearch_( const int *a, size_t n, int x){
    size_t left = 0;
    size_t right = n - 1;
    while (left <= right){
        size_t middle = left + (right - left) / 2;
        if (a[middle] < x){
            left = middle + 1;
        } else if (a[middle > x]) {
            right = middle - 1;
        } else {
            return middle;
        }
    }
    return SIZE_MAX;
}

// возвращает позицию первого элемента равного или большего x
// в отсортированном массиве a размера n
// при отсутствии такого элемента возвращает n
size_t binarySearchMoreOrEqual_(const int *a, size_t n, int x){
    if (a[0] >= x) {
        return 0;
    }
    size_t left = 0;
    size_t right = n;
    while (right - left > 1) {
        size_t middle = left + (right - left) / 2;
        if (a[middle] < x){
            left = middle;
        } else {
            right = middle;
        }
    }
    return right;
}

// вставка элемента со значением value
// в массив data размера n на позицию pos
void insert_(int * const a, size_t * const n, const size_t pos, const int value){
    assert(pos < *n);
    if (*n != 0){
        size_t lowBound = (pos == 0) ? SIZE_MAX : pos;
        (*n)++;
        for (size_t i = *n; i != lowBound; i--){
            a[i] = a[i - 1];
        }
        a[pos] = value;
    } else {
        (*n)++;
        a[pos] = value;
    }
}

// добавление элемента value в конец массива data размера n
void append_(int * const a, size_t * const n, const int value){
    a[*n] = value;
    (*n)++;
}

// удаление из массива data размера n элемента на позиции pos
// с сохранением порядка оставшихся элементов
void deleteByPosSaveOrder_ (int *a, size_t *n, const size_t pos){
    for (size_t i = pos; i < *n - 1; i++){
        a[i] = a[i + 1];
    }
    (*n)--;
}

// удаление из массива data размера n элемента на позиции pos
// без сохранения порядка оставшихся элементов
// размер массива data уменьшается на единицу
void deleteByPosUnsaveOrder_(int *a, size_t *n, const size_t pos){
    a[pos] = a[*n - 1];
    (*n)--;
}

// возвращает значение ’истина’ если все элементы
// массива data размера n соответствует функции-предикату predicate
// иначе - ’ложь’
int all_(const int *a, size_t n, int (*predicate) (int)){
    for (size_t i = 0; i < n; i++){
        if (predicate(a[i])){
            return 1;
        }
    }
    return 0;
}

// возвращает значение ’истина’ если хотя бы один элемент
// массива data размера n соответствует функции-предикату predicate
// иначе - ’ложь’
int any_(const int *a, size_t n, int (*predicate) (int)){
    for (size_t i = 0; i < n; i++){
        if (predicate(a[i])){
            return 1;
        }
    }
    return 0;
}

// применяет функцию predicate ко всем элементам массива source
// размера n и сохраняет результат в массиве dest размера n
void forEach_(const int *source, int *dest, const size_t n, const int (*predicate) (int)){
    for (size_t i = 0; i < n; i++){
        dest[i] = predicate(source[i]);
    }
}

// возвращает количество элементов массива data размера n
// удовлетворяющих функции-предикату predicate
int countIf_(const int * const a, const size_t n, int (*predicate) (int)){
    int count = 0;
    for (size_t i = 0; i < n; i++){
        count += predicate(a[i]);
    }
    return count;
}

// удаляет из массива data размера n все элементы, удовлетворяющие
// функции-предикату deletePredicate, записывает в n новый размер
// массива
void deleteIf_(int * const a, size_t * const n, int (*deletePredicate) (int)){
    size_t iRead = 0;
    while (iRead < *n && !deletePredicate(a[iRead])){
        iRead++;
    }
    size_t iWrite = iRead;
    while (iRead < *n){
        if (!deletePredicate(a[iRead])){
            a[iWrite] = a[iRead];
            iWrite++;
        }
        iRead++;
    }
    *n = iWrite;
}