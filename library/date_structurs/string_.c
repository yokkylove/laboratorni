#include "string_.h"

//возвращает количество символом в строке, не считая ноль-символ
size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}
