#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#include "string_.h"
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

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

//сравнивает два слова
bool areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    char *ptr1 = w1.begin;
    char *ptr2 = w2.begin;
    while (ptr1 <= w1.end && ptr2 <= w2.end) {
        if (*ptr1 != *ptr2) {
            return false; // Символы не совпадают, слова различаются
        }
        ptr1++;
        ptr2++;
    }
    // Проверяем, что оба указателя указывают на конец слов
    if (ptr1 > w1.end && ptr2 > w2.end) {
        return true; // Слова совпадают
    } else {
        return false; // Длины слов различаются
    }
}

char *strcpy(char *dest, const char *src) {
    char *start = dest; // сохраняем указатель на начало целевой строки

    while (*src != '\0') { // пока не достигнут конец исходной строки
        *dest = *src; // копируем символ из src в dest
        dest++; // увеличиваем указатель на целевую строку
        src++;  // увеличиваем указатель на исходную строку
    }

    *dest = '\0'; // добавляем завершающий нулевой символ к целевой строке

    return start; // возвращаем указатель на начало целевой строки
}

//Заменяет все вхождения слова 𝑤1 на слово 𝑤2.
void replace(char *source, char *w1, char *w2) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};

    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        strcpy(_stringBuffer, source);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    while (*readPtr != '\0') {
        WordDescriptor currentWord = {readPtr, readPtr};
        while (*readPtr != ' ' && *readPtr != '\0') {
            readPtr++;
            currentWord.end = readPtr;
        }

        if (areWordsEqual(currentWord, word1)) {
            for (char *ptr = word2.begin; ptr <= word2.end; ptr++) {
                *recPtr = *ptr;
                recPtr++;
            }
        } else {
            for (char *ptr = currentWord.begin; ptr <= currentWord.end; ptr++) {
                *recPtr = *ptr;
                recPtr++;
            }
        }

        if (*readPtr == ' ') {
            *recPtr = ' ';
            recPtr++;
        }

        if (*readPtr != '\0') {
            readPtr++;
        }
    }

    *recPtr = '\0'; // Добавляем завершающий нулевой символ
}

void test_replace_stringsAreEmpty() {
    char s[MAX_STRING_SIZE] = "";
    char *word1 = "";
    char *word2 = "";
    replace(s, word1, word2);
    ASSERT_STRING("", s);
}

void test_replace_stringIsEmpty() {
    char s[MAX_STRING_SIZE] = "";
    char *word1 = "hey";
    char *word2 = "yeh";
    replace(s, word1, word2);
    ASSERT_STRING("", s);
}

void test_replace_firstWordLessThenSecond() {
    char s[MAX_STRING_SIZE] = "aaa bbb ccc aaa";
    char *word1 = "aaa";
    char *word2 = "hey";
    replace(s, word1, word2);
    ASSERT_STRING("hey bbb ccc hey", s);
}

void test_replace_firstWordIsGreaterThenSecond() {
    char s[MAX_STRING_SIZE] = "hello world hello";
    char *word1 = "hello";
    char *word2 = "hey";
    replace(s, word1, word2);
    ASSERT_STRING("hey world hey", s);
}

void test_replace_firstWordIsNotInString() {
    char s[MAX_STRING_SIZE] = "hello world hello";
    char *word1 = "aaa";
    char *word2 = "hey";
    replace(s, word1, word2);
    ASSERT_STRING("hello world hello", s);
}

void test_replace_task5() {
    test_replace_stringsAreEmpty();
    test_replace_stringIsEmpty();
    test_replace_firstWordLessThenSecond();
    test_replace_firstWordIsGreaterThenSecond();
    test_replace_firstWordIsNotInString();
}

//Определяет, упорядочены ли лексикографически слова данного предложе ния.
bool areWordsOrdered(char *string) {
    WordDescriptor word1;
    WordDescriptor word2;
    if (getWord(string, &word1)) {
        word2 = word1;
        while (getWord(string, &word1)) {
            if (areWordsEqual(word1, word2) < 0)
                return false;
            word2 = word1;
            string = word1.end;
        }
        return true;
    } else {
        return true;
    }
}

void test_areWordsOrdered_stringIsEmpty() {
    char s[] = "";
    assert(areWordsOrdered(s) == true);
}

void test_areWordsOrdered_oneWordInString() {
    char s[] = "dream";
    assert(areWordsOrdered(s) == true);
}

void test_areWordsOrdered_NotorderedString() {
    char s[] = "pass op";
    assert(areWordsOrdered(s) == true);
}

void test_areWordsOrdered_TwoWordsEqual() {
    char s[] = "pass pass";
    assert(areWordsOrdered(s) == true);
}

void test_areWordsOrdered_orderedString() {
    char s[] = "a ab baaa ca cd";
    assert(areWordsOrdered(s) == true);
}

void test_areWordsOrdered_task6() {
    test_areWordsOrdered_stringIsEmpty();
    test_areWordsOrdered_oneWordInString();
    test_areWordsOrdered_NotorderedString();
    test_areWordsOrdered_TwoWordsEqual();
    test_areWordsOrdered_orderedString();
}

int main(){
    test_removeNonLetters();
    test_removeExtraSpaces();
    test_digitToStartLetterToEndt();
    test_replacesNumbersWithSpaces_task4();
    test_replace_task5();
    test_areWordsOrdered_task6();

    return 0;
}