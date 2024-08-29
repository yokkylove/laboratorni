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

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

BagOfWords _bag;
BagOfWords _bag2;

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

//Выводит слова данной строки в обратном порядке по одному в строке экрана.
void getBagOfWords(BagOfWords *bag, char *s) {
    WordDescriptor word;
    bag->size = 0;
    while (getWord(s, &word)) {
        bag->words[bag->size] = word;
        bag->size++;
        s = word.end;
    }
}

//копирует символы из заданного диапазона строки в обратном порядке
//в другую строку. Начиная с указателя rbeginSource и до rendSource,
//символы копируются в строку, начиная с указателя beginDestination.
char *copyReverse(char *rbeginSource, const char *rendSource, char
*beginDestination) {
    while (rbeginSource != rendSource) {
        (*beginDestination++) = *rbeginSource--;
    }
    return beginDestination;
}

//разбивает входную строку s на слова, затем переворачивает
//каждое слово и объединяет их в одну строку.
void reverseWordsBag(char *s) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    *copy(s, getEndOfString(s), _stringBuffer) = '\0';
    getBagOfWords(&_bag, _stringBuffer);
    char *copyS = s;
    for (int i = 0; i < _bag.size; i++) {
        copyS = copyReverse(_bag.words[i].end - 1, _bag.words[i].begin -
                                                   1, copyS);
        *copyS++ = ' ';
    }
    if (copyS != s) {
        copyS--;
    }
    *copyS = '\0';
}

void test_reverseWordsBag1() {
    char s[MAX_STRING_SIZE] = "h e y";
    reverseWordsBag(s);
    ASSERT_STRING("h e y", s);
}

void test_reverseWordsBag2() {
    char s[MAX_STRING_SIZE] = "Artyom";
    reverseWordsBag(s);
    ASSERT_STRING("moytrA", s);
}

void test_reverseWordsBag3() {
    char s[MAX_STRING_SIZE] = "";
    reverseWordsBag(s);
    ASSERT_STRING("", s);
}

void test_reverseWordsBag(){
    test_reverseWordsBag1();
    test_reverseWordsBag2();
    test_reverseWordsBag3();
}

//проверяет, является ли заданное слово палиндромом.
bool isWordPalindrome(char *begin, char *end) {
    end--;
    while (end - begin > 0) {
        if (*begin != *end)
            return false;
        begin++;
        end--;
    }
    return true;
}

//подсчитывает количество палиндромов в строке, разделенной запятыми.
size_t howManyWordsPalindromes(char *s) {
    char *endS = getEndOfString(s);
    char *beginSearch = findNonSpace(s);
    int countPalindromes = 0;
    char *commaPos = find(beginSearch, endS, ',');
    bool lastComma = *commaPos == '\0' && endS - beginSearch != 0;
    while (*commaPos != '\0' || lastComma) {
        beginSearch = findNonSpace(beginSearch);
        countPalindromes += isWordPalindrome(beginSearch, commaPos);
        beginSearch = commaPos + 1;
        if (lastComma)
            break;
        commaPos = find(beginSearch, endS, ',');
        lastComma = *commaPos == '\0';
    }
    return countPalindromes;
}

void test_howManyWordsPalindromes_stringIsEmpty() {
    char s[] = "";
    assert(howManyWordsPalindromes(s) == 0);
}

void test_howManyWordsPalindromes_oneWOrdIsPalindrome() {
    char s[] = "heh";
    assert(howManyWordsPalindromes(s) == 1);
}

void test_howManyWordsPalindromes_twoWordsIsPalindrome() {
    char s[] = "heh,heyeh";
    assert(howManyWordsPalindromes(s) == 2);
}

void test_howManyWordsPalindromes_onePallAndOneNot() {
    char s[] = "heh,hi";
    assert(howManyWordsPalindromes(s) == 1);
}

void test_howManyWordsPalindromes_OneSymbol() {
    char s[] = "a";
    assert(howManyWordsPalindromes(s) == 1);
}

void test_howManyWordsPalindromes_task8() {
    test_howManyWordsPalindromes_stringIsEmpty();
    test_howManyWordsPalindromes_oneWOrdIsPalindrome();
    test_howManyWordsPalindromes_twoWordsIsPalindrome();
    test_howManyWordsPalindromes_onePallAndOneNot();
    test_howManyWordsPalindromes_OneSymbol();
}

//объединяет две строки s1 и s2, разбивая их на слова
//с помощью функции strtok_ и объединяя слова
//в результирующую строку result.
void mergeStrings(char* s1, char* s2, char* result) {
    char* word1 = strtok_(s1, " ");
    char* word2 = strtok_(s2, " ");

    while (word1 != NULL || word2 != NULL) {
        if (word1 != NULL) {
            strcat_(result, word1);
            strcat_(result, " ");
            word1 = strtok_(NULL, " ");
        }
        if (word2 != NULL) {
            strcat_(result, word2);
            strcat_(result, " ");
            word2 = strtok_(NULL, " ");
        }
    }
}

void test_mergeString1() {
    char s1[] = "Hello how are you";
    char s2[] = "I am fine thank you";
    char result[100] = "";
    mergeStrings(s1, s2, result);
    ASSERT_STRING("Hello I am fine thank you", result);
}

void test_mergeString2() {
    char s1[] = "Thank you my friend";
    char s2[] = "Hello how are you";
    char result[100] = "";
    mergeStrings(s1, s2, result);
    ASSERT_STRING("Thank Hello how are you", result);
}

void test_mergeString(){
    test_mergeString1();
    test_mergeString2();
}

//Преобразовывает строку, изменяя порядок следования слов в строке на обратный.
void reverseWords(char *str) {
    int i = 0;
    _bag.size = 0;
    WordDescriptor word;

    //Считываем первое слово в строке
    while (*str && _bag.size < 1) {
        if (*str != ' ' && *(str+1) == ' ' || *(str+1) == '\0') {
            word.begin = str - i;
            word.end = str + 1;
            _bag.words[_bag.size] = word;
            _bag.size++;
            i = -1;
        }
        str++;
        i++;
    }

    //Считываем оставшиеся слова в строке
    while (*str) {
        if (*str != ' ' && *(str+1) == ' ' || *(str+1) == '\0') {
            word.begin = str - i + 1;
            word.end = str + 1;
            _bag.words[_bag.size] = word;
            _bag.size++;
            i = -1;
        }
        str++;
        i++;
    }

    // Перезаписываем слова в обратном порядке
    char *reversedStr = malloc(strlen_(str) + 1); // выделяем память для хранения перезаписанных слов
    char *p = reversedStr;

    for (int j = _bag.size - 1; j >= 0; j--) {
        for (char *p = _bag.words[j].begin; p < _bag.words[j].end; p++) {
            *reversedStr = *p;
            reversedStr++;
        }
        *reversedStr = ' ';
        reversedStr++;
    }
    *reversedStr = '\0';

    strcpy_(str, p); // копируем измененную строку обратно в исходную

    free(p); // освобождаем выделенную память
}

void test_reverseWords1 () {
    char p[MAX_STRING_SIZE] = "Hello world! This is a test.";
    reverseWords(p);
    ASSERT_STRING(p, ".test a is This !world Hello");

    char c[MAX_STRING_SIZE] = ".test a is This !world Hello";
    reverseWords(c);
    ASSERT_STRING(c, "Hello world! This is a test.");
}

void printWordBeforeFirstWordWithA(char *s) {
    char *word = NULL;
    char *token = strtok_(s, " ");

    while (token != NULL) {
        int foundA = 0;
        for (int i = 0; token[i] != '\0'; i++) {
            if (tolower(token[i]) == 'a') {
                foundA = 1;
                break;
            }
        }

        if (foundA) {
            if (word != NULL) {
                printf("%s\n", word);
                return;
            }
        } else {
            word = token;
        }

        token = strtok_(NULL, " ");
    }
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w) {
    if (s == NULL || strlen_(s) == 0) {
        return EMPTY_STRING;
    }

    char *wordBegin = NULL;
    char *wordEnd = NULL;
    char *token = strtok_(s, " ");

    while (token != NULL) {
        int foundA = 0;
        for (int i = 0; token[i] != '\0'; i++) {
            if (tolower(token[i]) == 'a') {
                foundA = 1;
                break;
            }
        }

        if (foundA) {
            if (wordBegin != NULL) {
                w->begin = wordBegin;
                w->end = wordEnd;
                return WORD_FOUND;
            } else {
                return FIRST_WORD_WITH_A;
            }
        } else {
            wordBegin = token;
            wordEnd = token + strlen_(token);
        }

        token = strtok_(NULL, " ");
    }

    return NOT_FOUND_A_WORD_WITH_A;
}

void test_getWordBeforeFirstWordWithA(){
    WordDescriptor word;
    char s1[] = "";
    assert(getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING);

    char s2[] = "ABC";
    assert(getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A);

    char s3[] = "BC A";
    assert(getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND);

    char s4[] = "B Q WE YR OW  IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

void wordDescriptorToString(WordDescriptor word, char *destination) {
    int length = word.end - word.begin;
    strncpy_(destination, word.begin, length);
    destination[length] = '\0';
}

BagOfWords createBagOfWordsFromString(char *s) {
    BagOfWords bag;
    bag.size = 0;

    char *wordBegin = s;
    for (; *s; ++s) {
        if (isspace(*s)) {
            if (s > wordBegin) {
                bag.words[bag.size].begin = wordBegin;
                bag.words[bag.size].end = s;
                ++bag.size;
            }
            wordBegin = s + 1;
        }
    }

    if (s > wordBegin) {
        bag.words[bag.size].begin = wordBegin;
        bag.words[bag.size].end = s;
        ++bag.size;
    }

    return bag;
}

int isWordInBagOfWords(WordDescriptor word, BagOfWords bag) {
    for (size_t i = 0; i < bag.size; ++i) {
        if (strncmp_(word.begin, bag.words[i].begin, word.end - word.begin) == 0) {
            return 1;
        }
    }
    return 0;
}

WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2) {
    BagOfWords bag = createBagOfWordsFromString(s2);
    WordDescriptor lastWord = {NULL, NULL};

    BagOfWords wordsInS1 = createBagOfWordsFromString(s1);
    for (size_t i = 0; i < wordsInS1.size; ++i) {
        if (isWordInBagOfWords(wordsInS1.words[i], bag)) {
            lastWord = wordsInS1.words[i];
        }
    }

    return lastWord;
}

void test_lastWordInFirstStringInSecondString(){
    char s1_1[] = "Hi ha he";
    char s2_1[] = "Hi he";
    WordDescriptor word1 = lastWordInFirstStringInSecondString(s1_1, s2_1);
    char str1[MAX_WORD_SIZE];
    wordDescriptorToString(word1, str1);
    ASSERT_STRING(str1, "he");

    char s1_2[] = "Hi ha he";
    char s2_2[] = "Hi ha";
    WordDescriptor word2 = lastWordInFirstStringInSecondString(s1_2, s2_2);
    char str2[MAX_WORD_SIZE];
    wordDescriptorToString(word2, str2);
    ASSERT_STRING(str2, "ha");
}

bool hasDuplicateWords(char* sentence) {
    char* words[100]; // массив для хранения слов
    int wordCount = 0;

    // Инициализируем массив слов
    char* word = strtok_(sentence, " ");
    while (word != NULL) {
        words[wordCount] = word;
        wordCount++;
        word = strtok_(NULL, " ");
    }

    // Проверяем наличие одинаковых слов
    for (int i = 0; i < wordCount; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                return true; // Найдено одинаковое слово
            }
        }
    }

    return false; // Одинаковых слов не найдено
}

void test_checkWordInString(){
    char str1[] = "my friend Hello my";
    assert(hasDuplicateWords(str1) == true);

    char str2[] = "my friend Hello";
    assert(hasDuplicateWords(str1) == false);
}

int compareWords(char *word1, char *word2) {
    int count1[26] = {0};
    int count2[26] = {0};

    int len1 = strlen_(word1);
    int len2 = strlen_(word2);

    if (len1 != len2) {
        return 0;
    }

    for (int i = 0; i < len1; i++) {
        count1[tolower(word1[i]) - 'a']++;
        count2[tolower(word2[i]) - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (count1[i] != count2[i]) {
            return 0;
        }
    }

    return 1;
}

void parseString(char *str, BagOfWords *bag) {
    char *token = strtok_(str, " ");
    while (token != NULL) {
        bag->words[bag->size].begin = token;
        bag->words[bag->size].end = token + strlen_(token);
        bag->size++;
        token = strtok_(NULL, " ");
    }
}

int findPairWithSameLetters(BagOfWords *bag) {
    for (int i = 0; i < bag->size - 1; i++) {
        for (int j = i + 1; j < bag->size; j++) {
            if (compareWords(bag->words[i].begin, bag->words[j].begin)) {
                char result1[MAX_WORD_SIZE], result2[MAX_WORD_SIZE];
                wordDescriptorToString(bag->words[i], result1);
                wordDescriptorToString(bag->words[j], result2);
                return 1;
            }
        }
    }

    return 0;
}

void test_findPairWithSameLetters() {
    BagOfWords bag1;
    bag1.size = 0;
    parseString("hello world olleh dlrow", &bag1);
    assert(findPairWithSameLetters(&bag1) == 1);

    BagOfWords bag2;
    bag2.size = 0;
    parseString("hey hi ha", &bag2);
    assert(findPairWithSameLetters(&bag2) == 0);
}

int main() {
    test_findPairWithSameLetters();

    return 0;
}