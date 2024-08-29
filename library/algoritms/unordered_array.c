#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "unordered_array.h"

// возвращает пустое множество для capacity элементов
unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

//Уменьшает размер внутреннего массива данных unordered_array_set до его фактического размера.
// Если размер внутреннего массива данных не равен его текущей ёмкости,
// то происходит перевыделение памяти под массив данных так, чтобы его ёмкость равнялась его фактическому размеру.
static void unordered_array_set_shrink_in_size(unordered_array_set* a) {
    if (a -> size != a -> capacity) {
        a -> data = (int*)realloc(a -> data, sizeof(int) * a -> size);
        a -> capacity = a -> size;
    }
}

// возвращает множество, состоящее из элементов массива a размера size.
unordered_array_set unordered_array_set_create_from_array(const int* a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++) {
        unordered_array_set_insert(&set, a[i]);
    }
    unordered_array_set_shrink_in_size(&set);

    return set;
}

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
size_t unordered_array_set_in (unordered_array_set * set , int value ) {
    return linearSearch_(set -> data, set -> size, value);
}

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
size_t unordered_array_set_isSubset (unordered_array_set subset, unordered_array_set set) {
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

//Сравнивает два целых числа, представленных в виде указателей на void.
static int compare_ints(const void* a, const void* b) {
    return *(int* ) a - *(int* ) b;
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size) {
        return 0;
    }
    qsort(set1.data, set1.size, sizeof(int), compare_ints);
    qsort(set2.data, set2.size, sizeof(int), compare_ints);

    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set -> size < set -> capacity);
}

// добавляет элемент value в множество set
void unordered_array_set_insert(unordered_array_set* set, int value) {
    if (unordered_array_set_in(set, value) == set -> size) {
        unordered_array_set_isAbleAppend(set);
        append_(set -> data, &set -> size, value);
    }
}

// удаляет элемент value из множества set
void unordered_array_set_deleteElement(unordered_array_set* set, int value) {
    size_t index_value = unordered_array_set_in(set, value);

    if (index_value < set -> size) {
        set->data[index_value] = set->data[set->size - 1];
        (set->size)--;
    }
}

// возвращает объединение множеств set1 и set2.
unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size + set2.size;
    unordered_array_set set = unordered_array_set_create(new_capacity);
    for (size_t i = 0; i < set1.size; i++) {
        set.data[i] = set1.data[i];
        set.size++;
    }
    for (size_t i = 0; i < set2.size; i++) {
        unordered_array_set_insert(&set, set2.data[i]);
    }
    unordered_array_set_shrink_in_size(&set);

    return set;
}

// возвращает пересечение множеств set1 и set2
unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size < set2.size ? set1.size : set2.size;
    unordered_array_set set = unordered_array_set_create(new_capacity);
    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(&set2, set1.data[i]) != set2.size) {
            unordered_array_set_insert(&set, set1.data[i]);
        }
    }
    return set;
}

// возвращает разность множеств set1 и set2
unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size;
    unordered_array_set set = unordered_array_set_create(new_capacity);
    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(&set2, set1.data[i]) == set2.size) {
            unordered_array_set_insert(&set, set1.data[i]);
        }
    }
    return set;
}

// возвращает дополнение до универсума множества set
unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet) {
    size_t new_capacity = universumSet.size;
    unordered_array_set new_set = unordered_array_set_create(new_capacity);
    for (size_t i = 0; i < universumSet.size; i++) {
        if (unordered_array_set_in(&set, universumSet.data[i]) == set.size) {
            unordered_array_set_insert(&new_set, universumSet.data[i]);
        }
    }
    assert(unordered_array_set_isSubset(new_set, universumSet));

    return new_set;
}

// возвращает симметрическую разность множеств set1 и set2
unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set universum = unordered_array_set_union(set1, set2);
    unordered_array_set intersection = unordered_array_set_intersection(set1, set2);

    unordered_array_set symmetric = unordered_array_set_complement(intersection, universum);

    unordered_array_set_delete(&intersection);
    unordered_array_set_delete(&universum);

    return symmetric;
}

// вывод множества set
void unordered_array_set_print(unordered_array_set set) {
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
void unordered_array_set_delete (unordered_array_set * set) {
    free(set -> data);
    set -> data = NULL;
    set -> size = 0;
    set -> capacity = 0;
}

// проверяет, является ли множество set1 включенным в множество set2.
bool unordered_array_set_isInclusion(unordered_array_set set1,
                                     unordered_array_set set2) {
    if (set1.size > set2.size)
        return false;

    qsort(set1.data, set1.size, sizeof(int), compare_ints);
    qsort(set2.data, set2.size, sizeof(int), compare_ints);

    size_t j = unordered_array_set_in(&set2, set1.data[0]);
    if (j == set2.size)
        return false;
    for (size_t i = 0; i < set1.size; ++i)
        if (set1.data[i] != set2.data[j])
            return false;

    return true;
}
//проверяет, является ли set1 строгим подмножеством set2, то есть содержит ли set1 все элементы set2 и
//имеет меньшее количество элементов.
bool unordered_array_set_isStrictInclusion(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size >= set2.size)
        return false;

    unordered_array_set_isInclusion(set1, set2);
}
