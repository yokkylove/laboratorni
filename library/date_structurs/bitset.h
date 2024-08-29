# ifndef GG_BITSET_H
# define GG_BITSET_H

# include <stdint.h>
# include <stdbool.h>

typedef struct bitset {
    uint32_t values ; // множество
    uint32_t maxValue ; // максимальный элемент универсума
} bitset;

// возвращает пустое множество c универсумом 0, 1,..., maxValue
bitset bitset_create (unsigned maxValue);

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in (bitset set, unsigned int value);

// возвращает значение ’истина’, если множества set1 и set2 равны
// иначе - ’ложь’
bool bitset_isEqual (bitset set1, bitset set2);

// возвращает значение ’истина’ если множество subset
// является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset (bitset subset, bitset set);

// добавляет элемент value в множество set
void bitset_insert (bitset *set, unsigned int value);

// удаляет элемент value из множества set
void bitset_deleteElement (bitset *set, unsigned int value);

// возвращает объединение множеств set1 и set2
bitset bitset_union (bitset set1, bitset set2);

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection (bitset set1, bitset set2);

// возвращает разность множеств set1 и set2
bitset bitset_difference (bitset set1, bitset set2);

// возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetricDifference (bitset set1, bitset set2);

// возвращает дополнение до универсума множества set
bitset bitset_complement (bitset set);

// вывод множества set
void bitset_print (bitset set);

//проверяет, является ли set1 строгим подмножеством set2, то есть содержит
// ли set1 все элементы set2 и имеет меньшее количество элементов.
bool bitset_isStrictInclusion(bool *set1, bool *set2);

// проверяет, является ли множество set1 включенным в множество set2.
bool bitset_isInclusion(bool *set1, bool *set2);

#endif