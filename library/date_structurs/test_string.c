#include "string_.h"
#include <assert.h>
#include <ctype.h>

void test_findNonSpace() {
    char str1[] = " Hello world!";
    char str2[] = "\t\t\t\n\r ";
    char str3[] = "";
    char str4[] = "Test";
    assert(*findNonSpace(str1) == 'H');
    assert(*findNonSpace(str2) == '\0');
    assert(*findNonSpace(str3) == '\0');
    assert(*findNonSpace(str4) == 'T');
}

void test_findSpace() {
    char str[] = "Hello World";
    char* result = findSpace(str);
    assert(*result == ' ');
    char str2[] = "This\thas\ta\ttab";
    char* result2 = findSpace(str2);
    assert(*result2 == '\t');
}

void test_findNonSpaceReverse() {
    char str1[] = " Hello, World! ";
    char str2[] = " Hello,\tWorld! \n";
    char str3[] = " ";
    char str4[] = " \t \n";
    char* res1 = findNonSpaceReverse(&str1[strlen_(str1) - 1], str1);
    assert(strcmp(res1, "d!") < 0);
    char* res2 = findNonSpaceReverse(&str2[strlen_(str2) - 1], str2);
    assert(strcmp(res2, "!") < 0);
    char* res3 = findNonSpaceReverse(&str3[strlen_(str3) - 1], str3);
    assert(res3 == str3);
    char* res4 = findNonSpaceReverse(&str4[strlen_(str4) - 1], str4);
    assert(res4 == str4);
}

void test_findSpaceReverse() {
    char str[] = "hello world";
    char *rbegin = &str[strlen_(str) - 1];
    char *rend = str - 1;
    assert(findSpaceReverse(rbegin, rend) == rbegin);
    *findSpaceReverse(rbegin, rend) = '\0';
    assert(strcmp(str, "hello") == 0);
}

void test_strcmp() {
    char str1[] = "Hello, world!";
    char str2[] = "Hello, world!";
    char str3[] = "Goodbye, world!";
    char str4[] = "He";
    char str5[] = "Hello";
    assert(strcmp(str1, str2) == 0);
    assert(strcmp(str1, str3) > 0);
    assert(strcmp(str1, str4) > 0);
    assert(strcmp(str4, str5) < 0);
}

void test_copy() {
    char source[] = "Hello, world!";
    char destination[50];
    char* end = copy(source, source + strlen_(source), destination);
    assert(strcmp(destination, source) == 0);
    assert(end == destination + strlen_(source));
}

void test_copyIf() {
    char src[] = "Hello, World!";
    char dest[20];
    char *result;
    result = copyIf(src, src + strlen_(src), dest, isalpha);
    assert(strcmp(result, "HelloWorld") < 0);
}

void test_copyIfReverse() {
    char source[] = "Hello, world!";
    char destination[20];
    char *result = copyIfReverse(&source[11], &source[0] - 1,
                                 destination, isalpha);
    assert(result > &*(destination + 5));
    assert(*(destination + 0) == 'd');
    assert(*(destination + 1) == 'l');
    assert(*(destination + 2) == 'r');
    assert(*(destination + 3) == 'o');
    assert(*(destination + 4) == 'w');
}

void test1(){
    test_findNonSpaceReverse();
    test_findNonSpace();
    test_findSpace();
    test_strcmp();
    test_copy();
    test_copyIf();
    test_copyIfReverse();
    test_findSpaceReverse();
}
