#include <stdlib.h>

#ifndef GG_STRING__H
#define GG_STRING__H
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

//возвращает количество символом в строке, не считая ноль-символ
size_t strlen_(const char *begin);

// возвращает указатель
//на первый элемент с кодом ch, расположенным на ленте памяти между
//адресами begin и end не включая end.
char* find(char *begin, char *end, int ch);

//возвращает указатель на первый
//символ, отличный от пробельных, расположенный на ленте памяти,
// начиная с begin и заканчивая ноль-символом.
char* findNonSpace(char *begin);

//возвращает указатель на первый пробельный символ, расположенный
//на ленте памяти начиная с адреса begin или на первый ноль-символ.
char* findSpace(char *begin);

//возвращает указатель на первый справа символ, отличный от пробельных,
//расположенный на ленте памяти, начиная с rbegin и заканчивая rend.
char* findNonSpaceReverse(char *rbegin, const char *rend);

//возвращает указатель на первый пробельный символ справа, расположенный
//на ленте памяти, начиная с rbegin и заканчивая rend.
char* findSpaceReverse(char *rbegin, const char *rend);

//Функция возвращает отрицательное значение, если lhs располагается до rhs
//в лексикографическом порядке, значение 0, если lhs и rhs
//равны, иначе – положительное значение.
int strcmp(const char *lhs, const char *rhs);

//записывает по адресу beginDestination фрагмент памяти,
//начиная с адреса beginSource до endSource.
//Возвращает указатель на следующий свободный фрагмент памяти в destination.
char* copy(const char *beginSource, const char *endSource, char
*beginDestination);

//записывает по адресу beginDestination элементы из фрагмента
//памяти начиная с beginSource заканчивая endSource,
//удовлетворяющие функции-предикату f.
//Функция возвращает указатель на следующий свободный для
//записи фрагмент в памяти.
char* copyIf(char *beginSource, const char *endSource, char
*beginDestination, int (*f)(int));

//записывает по адресу beginDestination элементы из фрагмента
//памяти начиная с rbeginSource заканчивая rendSource, удовлетворяющие функции-предикату f.
//Функция возвращает значение beginDestination по окончанию работы функции.
char* copyIfReverse(char *rbeginSource, const char *rendSource, char
*beginDestination, int (*f)(int));

//возвращает указатель на конец строки
char* getEndOfString(const char* str);

//ищет в строке str первое вхождение любого символа из строки delim.
char* strpbrk_(const char* str, const char* delim);

char* strtok_(char* str, const char* delim);

char* strcat_(char* dest, const char* src);

#endif