#include <stdio.h>
#include "bitset.h"

// возвращает пустое множество c универсумом 0, 1,..., maxValue
bitset bitset_create (unsigned maxValue){
    bitset newBitset;
    newBitset.values = 0; // пустое множество
    newBitset.maxValue = maxValue;
    return newBitset;
}

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in (bitset set, unsigned int value){
    if (value > set.maxValue) {
        return false; // значение value больше максимального элемента универсума
    }
    return (set.values & (1 << value)) != 0; // проверяет наличие value в множестве values
}

// возвращает значение ’истина’, если множества set1 и set2 равны
// иначе - ’ложь’
bool bitset_isEqual (bitset set1, bitset set2){
    if (set1.maxValue != set2.maxValue) {
        return false; // разные максимальные элементы универсума
    }
    return set1.values == set2.values;
}

// возвращает значение ’истина’ если множество subset
// является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset (bitset subset, bitset set){
    if (subset.maxValue != set.maxValue) {
        return false; // разные максимальные элементы универсума
    }
    return (subset.values & set.values) == subset.values;
}

// добавляет элемент value в множество set
void bitset_insert (bitset *set, unsigned int value){
    if (value <= set->maxValue) {
        set->values |= (1 << value); // устанавливаем бит для элемента value
    }
}

// удаляет элемент value из множества set
void bitset_deleteElement (bitset *set, unsigned int value){
    if (value <= set->maxValue) { // Проверяем, что значение value не превышает максимального элемента
        set->values &= ~(1 << value); // Операция побитового И с инвертированным значением сдвига
    }
}

// возвращает объединение множеств set1 и set2
bitset bitset_union (bitset set1, bitset set2){
    bitset result;
    result.maxValue = set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue;
    result.values = set1.values | set2.values;
    return result;
}

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection (bitset set1, bitset set2){
    bitset result;
    result.maxValue = set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue;
    result.values = set1.values & set2.values;
    return result;
}

// возвращает разность множеств set1 и set2
bitset bitset_difference (bitset set1, bitset set2){
    bitset result;
    result.maxValue = set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue;
    result.values = set1.values & ~set2.values; // используем побитовую операцию "и" и инверсию для нахождения разности
    return result;
}

// возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetricDifference (bitset set1, bitset set2){
    bitset result;
    result.maxValue = set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue;
    result.values = (set1.values | set2.values) & ~(set1.values & set2.values); // используем побитовые операции для нахождения симметрической разности
    return result;
}

// возвращает дополнение до универсума множества set
bitset bitset_complement (bitset set){
    bitset complement;
    complement.values = ~set.values & ((1 << set.maxValue) - 1);
    complement.maxValue = set.maxValue;
    return complement;
}

// вывод множества set
void bitset_print (bitset set){
    printf("{ ");
    for (uint32_t i = 0; i < set.maxValue; i++) {
        if (set.values & (1 << i)) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}

// Преобразование массива булевых значений в целочисленное значение,
// представляющее битовый набор
int cmp_bitset_(const bool *set) {
    int n = 10;
    int bSet = 0;
    int degree = 1;
    while (n-- >= 0) {
        if (set[n])
            bSet += degree;
        degree <<= 1;
    }
    return bSet;
}

// проверяет, является ли множество set1 включенным в множество set2.
bool bitset_isInclusion(bool *set1, bool *set2) {
    int bSet1 = cmp_bitset_(set1);
    int bSet2 = cmp_bitset_(set2);
    if (bSet1 > bSet2)
        return false;
    return (bSet2 & bSet1) == bSet1;
}

//проверяет, является ли set1 строгим подмножеством set2, то есть содержит
// ли set1 все элементы set2 и имеет меньшее количество элементов.
bool bitset_isStrictInclusion(bool *set1, bool *set2) {
    int bSet1 = cmp_bitset_(set1);
    int bSet2 = cmp_bitset_(set2);
    if (bSet1 >= bSet2)
        return false;
    return (bSet2 & bSet1) == bSet1;
}
