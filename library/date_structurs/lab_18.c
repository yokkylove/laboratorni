#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#include "string_.h"
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;


void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName, int line) {
    if (strcmp(expected, got)) { fprintf(stderr, " File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, " Expected : \"%s \"\n", expected); fprintf(stderr, "Got:\"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

void test_removeNonLetters1() {
    char s[] = "Hey1234";
    removeNonLetters(s);
    ASSERT_STRING("Hey1234", s);
}

void test_removeNonLetters2() {
    char s[] = "Hey 1234";
    removeNonLetters(s);
    ASSERT_STRING("Hey1234", s);
}

void test_removeNonLetters3() {
    char s[] = "Hey1234 ";
    removeNonLetters(s);
    ASSERT_STRING("Hey1234", s);
}

void test_removeNonLetters4() {
    char s[] = " Hey1234 ";
    removeNonLetters(s);
    ASSERT_STRING("Hey1234", s);
}

void test_removeNonLetters() {
    test_removeNonLetters1();
    test_removeNonLetters2();
    test_removeNonLetters3();
    test_removeNonLetters4();
}

//сокращает количество пробелов между словами данного предложения до одного
void removeExtraSpaces(char *s) { char *begin = s;
    char *destination = begin; char last = *begin;
    while (*begin != '\0') {
        if (*begin != last || last != ' ')
            *destination++ = *begin;
        last = *begin++;
    }
    if (last == ' ') destination--;
    *destination = '\0';
}

void test_removeExtraSpaces1() {
    char s[] = "Smolyakov Artyom";
    removeExtraSpaces(s);
    ASSERT_STRING("Smolyakov Artyom", s);
}

void test_removeExtraSpaces2() {
    char s[] = "Smolyakov Artyom ";
    removeExtraSpaces(s);
    ASSERT_STRING("Smolyakov Artyom", s);
}

void test_removeExtraSpaces3() {
    char s[] = " Smolyakov Artyom";
    removeExtraSpaces(s);
    ASSERT_STRING("Smolyakov Artyom", s);
}

void test_removeExtraSpaces4() {
    char s[] = "Smolyakov Artyom ";
    removeExtraSpaces(s);
    ASSERT_STRING("Smolyakov Artyom", s);
}

void test_removeExtraSpaces() {
    test_removeExtraSpaces1();
    test_removeExtraSpaces2();
    test_removeExtraSpaces3();
    test_removeExtraSpaces4();
}

//вернёт значение 0, если слово не было считано, в противном
//случае будет возвращено значение 1 и в переменную word типа WordDescriptor
//будут записаны позиции начала слова, и первого символа после конца слова
int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

void digitToStart(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

//извлекает отдельные слова с помощью функции getWord, преобразует
//первую букву слова в заглавную, если она является цифрой,
//и продолжает поиск следующего слова до конца строки
void digitToStartLetterToEndt(char *s) {
    char *beginSearch = s;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {
        digitToStart(word);
        beginSearch = word.end;
    }
}

void test_digitToStartLetterToEndt1() {
    char s[] = "Hey1234";
    digitToStartLetterToEndt(s);
    ASSERT_STRING("4321Hey", s);
}

void test_digitToStartLetterToEndt2() {
    char s[] = "He1y1234";
    digitToStartLetterToEndt(s);
    ASSERT_STRING("43211Hey", s);
}

void test_digitToStartLetterToEndt3() {
    char s[MAX_STRING_SIZE] = "He1y1234 5d ";
    digitToStartLetterToEndt(s);
    ASSERT_STRING("43211Hey", s);
}

void test_digitToStartLetterToEndt4() {
    char s[] = "Hey1y234 f0r12";
    digitToStartLetterToEndt(s);
    ASSERT_STRING("4321Heyy", s);
}

void test_digitToStartLetterToEndt() {
    test_digitToStartLetterToEndt1();
    test_digitToStartLetterToEndt2();
    test_digitToStartLetterToEndt3();
    test_digitToStartLetterToEndt4();
}

//вернёт значение 0, если слово не было считано,
//в противном случае будет возвращено значение 1
bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    if (rbegin == NULL || rend == NULL || word == NULL || rbegin >= rend) {
        return false;
    }
    // Начинаем с конца строки и идем назад, пока не достигнем начала слова
    while (rend > rbegin && !isalpha(*rend)) {
        rend--;
    }
    if (rend <= rbegin) {
        return false; // Не удалось найти слово
    }
    word->end = rend;
    // Ищем начало слова
    while (rend > rbegin && isalpha(*rend)) {
        rend--;
    }
    word->begin = rend + 1;
    return true;
}

//преобразовывает строку, заменяя каждую цифру соответствующим ей числом пробелов
void replacesNumbersWithSpaces(char *s) {
    int num_alphabet = 48;
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endSource = getEndOfString(s);
    char *stringBufferStart = _stringBuffer;
    char *endOfStringBuffer = copy(s, endSource, stringBufferStart);
    *endOfStringBuffer = '\0';
    while (*stringBufferStart != '\0') {
        if (isalpha(*stringBufferStart)) {
            *s++ = *stringBufferStart;
        }
        else if (isdigit(*stringBufferStart)) {
            while (*stringBufferStart - num_alphabet > 0) {
                *s++ = ' ';
                (*stringBufferStart)--;
            }
        }
        ++stringBufferStart;
    }
}

void test_replacesNumbersWithSpaces_stringIsEmpty() {
    char s[MAX_STRING_SIZE] = "";
    replacesNumbersWithSpaces(s);
    ASSERT_STRING("", s);
}

void test_replacesNumbersWithSpaces_onlyLetters() {
    char s[MAX_STRING_SIZE] = "Hey";
    replacesNumbersWithSpaces(s);
    ASSERT_STRING("Hey", s);
}

void test_replacesNumbersWithSpaces_onlydigits() {
    char s[MAX_STRING_SIZE] = "897654";
    replacesNumbersWithSpaces(s);
    ASSERT_STRING("                                       ", s);
}

void test_replacesNumbersWithSpaces_lettersAndDigits() {
    char s[MAX_STRING_SIZE] = "H3e0y1";
    replacesNumbersWithSpaces(s);
    ASSERT_STRING("H   ey ", s);
}

void test_replacesNumbersWithSpaces_task4() {
    test_replacesNumbersWithSpaces_stringIsEmpty();
    test_replacesNumbersWithSpaces_onlyLetters();
    test_replacesNumbersWithSpaces_onlydigits();
    test_replacesNumbersWithSpaces_lettersAndDigits();
}

int main(){
    test_removeNonLetters();
    test_removeExtraSpaces();
    test_digitToStartLetterToEndt();
    test_replacesNumbersWithSpaces_task4();

    return 0;
}