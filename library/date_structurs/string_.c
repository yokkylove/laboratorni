#include "string_.h"
#include <ctype.h>
#include <memory.h>

//возвращает количество символом в строке, не считая ноль-символ
size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}


// возвращает указатель
//на первый элемент с кодом ch, расположенным на ленте памяти между
//адресами begin и end не включая end.
char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

//возвращает указатель на первый
//символ, отличный от пробельных, расположенный на ленте памяти,
// начиная с begin и заканчивая ноль-символом.
char* findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin)) {
        begin++;
    }
    return begin;
}

//возвращает указатель на первый пробельный символ, расположенный
//на ленте памяти начиная с адреса begin или на первый ноль-символ.
char* findSpace(char *begin) {
    while (*begin != '\0' && (*begin != ' ' && *begin != '\t' && *begin != '\r' && *begin != '\n')) {
        begin++;
    }
    return begin;
}

//возвращает указатель на первый справа символ, отличный от пробельных,
//расположенный на ленте памяти, начиная с rbegin и заканчивая rend.
char* findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && (*rbegin == ' ' || *rbegin == '\t' || *rbegin == '\r' || *rbegin == '\n')) {
        rbegin--;
    }
    return rbegin + 1;
}

//возвращает указатель на первый пробельный символ справа, расположенный
//на ленте памяти, начиная с rbegin и заканчивая rend.
char* findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && !isspace(*rbegin)) {
        rbegin--;
    }
    return rbegin;
}

//Функция возвращает отрицательное значение, если lhs располагается до rhs
//в лексикографическом порядке, значение 0, если lhs и rhs
//равны, иначе – положительное значение.
int strcmp(const char *lhs, const char *rhs) {
    while (*lhs != '\0' && *rhs != '\0' && *lhs == *rhs) {
        lhs++;
        rhs++;
    }
    return (*lhs > *rhs) - (*lhs < *rhs);
}

//записывает по адресу beginDestination фрагмент памяти,
//начиная с адреса beginSource до endSource50.
//Возвращает указатель на следующий свободный фрагмент памяти в destination.
char* copy(const char *beginSource, const char *endSource, char
*beginDestination) {
    size_t size = endSource - beginSource;
    memcpy(beginDestination, beginSource, size);
    *(beginDestination + size) = '\0';
    return beginDestination + size;
}

//записывает по адресу beginDestination элементы из фрагмента
//памяти начиная с beginSource заканчивая endSource,
//удовлетворяющие функции-предикату f.
//Функция возвращает указатель на следующий свободный для
//записи фрагмент в памяти.
char* copyIf(char *beginSource, const char *endSource, char
*beginDestination, int (*f)(int)) {
    while (beginSource != endSource) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
    *beginDestination = '\0';
    return beginDestination;
}

//записывает по адресу beginDestination элементы из фрагмента
//памяти начиная с rbeginSource заканчивая rendSource, удовлетворяющие функции-предикату f.
//Функция возвращает значение beginDestination по окончанию работы функции.
char* copyIfReverse(char *rbeginSource, const char *rendSource, char
*beginDestination, int (*f)(int)) {
    char *rbeginDest = beginDestination;
    while (rbeginSource >= rendSource) {
        if (f(*rbeginSource)) {
            *rbeginDest = *rbeginSource;
            rbeginDest++;
        }
        rbeginSource--;
    }
    *rbeginDest = '\0';
    return rbeginDest;
}