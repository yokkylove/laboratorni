#include "ordered_array.h"
#include <malloc.h>

// Уменьшает выделенную память под массив данных в структуре ordered_array_set, если size меньше capacity.
void ordered_array_set_shrink_in_size(ordered_array_set *a) {
    if (a->size != a->capacity) {
        a->data = (int *) realloc(a->data, sizeof(int) * a->size);
        a->capacity = a->size;
    }
}

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create (size_t capacity){
    return (ordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set ordered_array_set_create_from_array ( const int *a, size_t size){
    ordered_array_set set = ordered_array_set_create(size);
    for (size_t i = 0; i < size; i++) {
        ordered_array_set_insert(&set, *(a + i));
    }
    ordered_array_set_shrink_in_size(&set);

    return set;
}

// возвращает значение позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t ordered_array_set_in (ordered_array_set *set, int value){
    return binarySearch_(set->data, set->size, value);
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_isEqual (ordered_array_set set1, ordered_array_set set2){
    if (set1.size != set2.size) {
        return 0;
    }
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool ordered_array_set_isSubset (ordered_array_set subset, ordered_array_set set){
    for (size_t i = 0; i < subset.size; i++) {
        bool found = false;
        for (size_t j = 0; j < set.size; j++) {
            if (subset.data[i] == set.data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void ordered_array_set_isAbleAppend (ordered_array_set *set){
    assert(set -> size < set -> capacity);
}

// добавляет элемент value в множество set
void ordered_array_set_insert (ordered_array_set *set, int value){
    size_t index = ordered_array_set_in(set, value);
    if (index == set->size) {
        ordered_array_set_isAbleAppend(set);

        size_t i;
        for (i = set->size; (i > 0 && set->data[i - 1] > value); i--) {
            set->data[i] = set->data[i - 1];
        }
        set->data[i] = value;
        set->size++;
    }
}

// удаляет элемент value из множества set
void ordered_array_set_deleteElement (ordered_array_set *set, int value){
    size_t index = ordered_array_set_in(set, value);

    if (index != set->size) {
        deleteByPosSaveOrder_(set->data, &set->size, index);
    }
}

// возвращает объединение множеств set1 и set2
ordered_array_set ordered_array_set_union (ordered_array_set set1, ordered_array_set set2){
    size_t new_capacity = set1.size + set2.size;
    ordered_array_set set = ordered_array_set_create(new_capacity);
    size_t i = 0;
    size_t j = 0;
    while (i < set1.size && j < set2.size) {
        if (j == set2.size || set1.data[i] < set2.data[j]) {
            set.data[set.size] = set1.data[i];
            set.size++;
            i++;
        } else if (i == set1.size || set1.data[i] > set2.data[j]) {
            set.data[set.size] = set2.data[j];
            set.size++;
            j++;
        } else {
            set.data[set.size] = set1.data[i];
            set.size++;
            i++;
            j++;
        }
    }
    while (i < set1.size) {
        set.data[set.size] = set1.data[i];
        set.size++;
        i++;
    }
    while (j < set2.size) {
        set.data[set.size] = set2.data[j];
        set.size++;
        j++;
    }
    ordered_array_set_shrink_in_size(&set);

    return set;
}

// возвращает пересечение множеств set1 и set2
ordered_array_set ordered_array_set_intersection (ordered_array_set set1, ordered_array_set set2){
    size_t new_capacity = set1.size < set2.size ? set1.size : set2.size;
    ordered_array_set set = ordered_array_set_create(new_capacity);
    size_t i = 0;
    size_t j = 0;
    while (i != set1.size && j != set2.size) {
        if (set1.data[i] < set2.data[j]) {
            i++;
        } else if (set1.data[i] > set2.data[j]) {
            j++;
        } else {
            set.data[set.size] = set1.data[i];
            set.size++;
            i++;
            j++;
        }
    }
    ordered_array_set_shrink_in_size(&set);

    return set;
}

// возвращает разность множеств set1 и set2
ordered_array_set ordered_array_set_difference (ordered_array_set set1, ordered_array_set set2){
    size_t new_capacity = set1.size;
    ordered_array_set set = ordered_array_set_create(new_capacity);
    size_t i = 0;
    size_t j = 0;
    while (i < set1.size) {
        if (j == set2.size || set1.data[i] < set2.data[j]) {
            set.data[set.size] = set1.data[i];
            set.size++;
            i++;
        } else if (set1.data[i] > set2.data[j]) {
            j++;
        } else {
            i++;
        }
    }
    ordered_array_set_shrink_in_size(&set);

    return set;
}

// возвращает симметрическую разность множеств set1 и set2
ordered_array_set ordered_array_set_symmetricDifference (ordered_array_set set1, ordered_array_set set2){
    ordered_array_set universum = ordered_array_set_union(set1, set2);
    ordered_array_set intersection = ordered_array_set_intersection(set1, set2);

    ordered_array_set symmetric = ordered_array_set_complement(intersection, universum);

    ordered_array_set_delete(&intersection);
    ordered_array_set_delete(&universum);

    return symmetric;
}

// возвращает дополнение до универсума universumSet множества set
ordered_array_set ordered_array_set_complement (ordered_array_set set, ordered_array_set universumSet){
    size_t new_capacity = universumSet.size;
    ordered_array_set new_set = ordered_array_set_create(new_capacity);
    size_t i = 0, j = 0;
    while (i < universumSet.size) {
        if (j < set.size && universumSet.data[i] == set.data[j]) {
            i++;
            j++;
        } else {
            new_set.data[new_set.size] = universumSet.data[i];
            new_set.size++;
            i++;
        }
    }
    ordered_array_set_shrink_in_size(&new_set);
    assert(ordered_array_set_isSubset(new_set, universumSet));

    return new_set;
}

// вывод множества set
void ordered_array_set_print (ordered_array_set set){
    printf("{");
    int is_empty = 1;
    for (size_t i = 0; i < set.size; i++) {
        printf("%d, ", *(set.data + i));
        is_empty = 0;
    }
    if (is_empty) {
        printf("}\n");
    } else {
        printf("\b\b}\n");
    }
}

// освобождает память, занимаемую множеством set
void ordered_array_set_delete (ordered_array_set * set){
    free(set -> data);
    set -> data = NULL;
    set -> size = 0;
    set -> capacity = 0;
}

// проверяет, является ли множество set1 включенным в множество set2.
bool ordered_array_set_isInclusion(ordered_array_set set1,
                                   ordered_array_set set2) {
    if (set1.size > set2.size)
        return false;

    size_t j = ordered_array_set_in(&set2, set1.data[0]);
    if (j == set2.size)
        return false;

    for (size_t i = 0; i < set1.size; ++i)
        if (set1.data[i] != set2.data[j])
            return false;

    return true;
}

//проверяет, является ли set1 строгим подмножеством set2, то есть содержит ли set1 все элементы set2 и имеет меньшее количество элементов.
bool ordered_array_set_isStrictInclusion(ordered_array_set set1,
                                         ordered_array_set set2) {
    if (set1.size >= set2.size)
        return false;
    ordered_array_set_isInclusion(set1, set2);
}
