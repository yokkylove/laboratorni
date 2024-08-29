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
//начиная с адреса beginSource до endSource.
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

//возвращает указатель на конец строки
char* getEndOfString(const char* str) {
    const char* end = str;
    while (*end != '\0') {
        end++;
    }
    return (char*) end;
}

char* strpbrk_(const char* str, const char* delim) {
    const char* ptr = str;

    while (*ptr != '\0') {
        const char* d = delim;
        while (*d != '\0') {
            if (*ptr == *d) {
                return (char*)ptr;
            }
            d++;
        }
        ptr++;
    }

    return NULL;
}

char* strtok_(char* str, const char* delim) {
    static char* savedToken = NULL;

    if (str != NULL) {
        savedToken = str;
    }

    if (savedToken == NULL) {
        return NULL;
    }

    char* tokenStart = savedToken;
    char* tokenEnd = strpbrk_(savedToken, delim);

    if (tokenEnd != NULL) {
        *tokenEnd = '\0';
        savedToken = tokenEnd + 1;
    } else {
        savedToken = NULL;
    }

    return tokenStart;
}

char* strcat_(char* dest, const char* src) {
    char* ptr = dest;

    while (*ptr != '\0') {
        ptr++;
    }

    while (*src != '\0') {
        *ptr = *src;
        ptr++;
        src++;
    }

    *ptr = '\0';

    return dest;
}

char *strncpy_(char *destination, const char *source, size_t num) {
    char *start = destination;

    while (num && (*destination++ = *source++)) {
        num--;
    }

    if (num) {
        while (--num) {
            *destination++ = '\0';
        }
    }

    return start;
}

char *strstr_(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;  // Пустая подстрока всегда найдена в любой строке
    }

    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;

        while (*h && *n && (*h == *n)) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char *)haystack;  // Найдено вхождение подстроки
        }

        haystack++;
    }

    return NULL;  // Подстрока не найдена
}

void strcpy_(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

char* strdup_(const char* str) {
    size_t len = strlen_(str); // определяем длину строки
    char* newStr = (char*)malloc(len + 1); // выделяем память для новой строки

    if (newStr == NULL) {
        return NULL; // возвращаем NULL, если не удалось выделить память
    }

    strcpy_(newStr, str); // копируем строку в новую память
    return newStr; // возвращаем указатель на новую строку
}

size_t strcspn_(const char* str1, const char* str2) {
    const char* ptr1 = str1;
    size_t len = 0;

    while (*ptr1) {
        const char* ptr2 = str2;
        while (*ptr2) {
            if (*ptr1 == *ptr2) {
                return len;
            }
            ++ptr2;
        }
        ++ptr1;
        ++len;
    }

    return len;
}

char *strrchr_(const char *str, int c) {
    char *last = NULL;
    while (*str != '\0') {
        if (*str == c) {
            last = (char *)str;
        }
        str++;
    }
    return last;
}

int strncmp_(const char *s1, const char *s2, size_t n) {
    while (n--) {
        if (*s1 != *s2) {
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
    }
    return 0;
}