#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#include "string_.h"
#include <ctype.h>
#include <stdio.h>

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

int main(){
    test_removeNonLetters();

    return 0;
}