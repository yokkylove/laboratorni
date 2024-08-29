#include <stdio.h>
#include <string.h>

#define MAX_FILE_SIZE 1024

void copyFileContent(const char* sourceFile, const char* destinationFile) {
    FILE *source, *destination;
    char ch;

    // Открываем исходный файл для чтения
    source = fopen(sourceFile, "r");
    if (source == NULL) {
        printf("The source file could not be opened for reading\n");
        return;
    }

    // Открываем файл назначения для записи
    destination = fopen(destinationFile, "w");
    if (destination == NULL) {
        printf("The destination file could not be opened for writing\n");
        fclose(source);
        return;
    }

    // Копируем содержимое из исходного файла в файл назначения
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }

    // Закрываем файлы
    fclose(source);
    fclose(destination);

    printf("The contents of the %s file have been successfully copied to the %s file\n", sourceFile, destinationFile);
}


void ASSERT_TXT(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        printf("Error\n");
        return;
    }

    char buffer1[MAX_FILE_SIZE];
    char buffer2[MAX_FILE_SIZE];

    while (fgets(buffer1, MAX_FILE_SIZE, f1) != NULL && fgets(buffer2, MAX_FILE_SIZE, f2) != NULL) {
        if (strcmp(buffer1, buffer2) != 0) {
            printf("Error: files is not similar\n");
            fclose(f1);
            fclose(f2);
            return;
        }
    }
    printf("All is good");
}

int task_19_1(const char *str1) {
    FILE *file = fopen(str1, "r");
    if (file == NULL) {
        printf("File opening error\n");
        return 1;
    }

    FILE *output_file = fopen("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", "w");
    if (output_file == NULL) {
        printf("File creation error\n");
        return 1;
    }

    int n;
    while (fscanf(file, "%d", &n) == 1) {
        int matrix[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fscanf(file, "%d", &matrix[i][j]);
            }
        }
        fprintf(output_file, "%d ", n);
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                fprintf(output_file, "%d ", matrix[i][j]);
            }
        }
    }

    fclose(file);
    fclose(output_file);

    copyFileContent("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", str1);

    return 0;
}

void test_for_task_19_1() {
    const char *str1 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_1.txt";
    const char *str2 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_1_test.txt";
    int ans = task_19_1(str1);

    if (ans == 0) {
        ASSERT_TXT(str1, str2);
    }
}

int task_19_2(const char *str) {
    FILE *input_file = fopen(str, "r");
    FILE *output_file = fopen("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", "w");
    double number;

    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    while (fscanf(input_file, "%lf", &number) == 1) {
        fprintf(output_file, "%.2f ", number);
    }

    printf("Conversion completed successfully.\n");

    fclose(input_file);
    fclose(output_file);

    copyFileContent("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", str);

    return 0;
}

void test_for_task_19_2() {
    const char *str1 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_2.txt";
    const char *str2 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_2_test.txt";
    int ans = task_19_2(str1);

    if (ans == 0) {
        ASSERT_TXT(str1, str2);
    }
}

int task_19_3(const char *str) {
    // Открываем файл для чтения и записи
    FILE *file = fopen(str, "r+");
    char operation;
    int operand1, operand2, result;

    if (file == NULL) {
        printf("File opening error\n");
        return 1;
    }

    // Считываем операнды и операцию из файла
    fscanf(file, "%d %c %d", &operand1, &operation, &operand2);

    // Вычисляем результат
    if (operation == '+') {
        result = operand1 + operand2;
    } else if (operation == '-') {
        result = operand1 - operand2;
    } else if (operation == '*') {
        result = operand1 * operand2;
    } else if (operation == '/') {
        result = operand1 / operand2;
    } else {
        printf("Unsupported operation\n");
        fclose(file);
        return 1;
    }

    // Дописываем результат в конец файла
    fprintf(file, "\nResult: %d\n", result);

    fclose(file);

    printf("The result of the calculation is added to the file\n");

    return 0;
}

void test_for_task_19_3() {
    const char *str1 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_3.txt";
    const char *str2 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_3_test.txt";
    int ans = task_19_3(str1);

    if (ans == 0) {
        ASSERT_TXT(str1, str2);
    }
}

int task_19_4(const char *str, char sequence[20]) {
    // Открываем файл для чтения
    FILE *inputFile = fopen(str, "r");
    if (inputFile == NULL) {
        printf("File opening error\n");
        return 1;
    }
    // Открываем файл для записи
    FILE *outputFile = fopen("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", "w");
    if (outputFile == NULL) {
        printf("File opening error\n");
        fclose(inputFile);
        return 1;
    }

    char word[100];

    // Считываем каждое слово из входного файла
    while (fscanf(inputFile, "%s", word) != EOF) {
        // Проверяем содержит ли слово заданную последовательность символов
        if (strstr(word, sequence) != NULL) {
            // Записываем слово в выходной файл
            fprintf(outputFile, "%s", word);
        }
    }

    printf("Words containing a sequence of characters are saved\n");

    fclose(inputFile);
    fclose(outputFile);

    copyFileContent("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", str);

    return 0;
}

void test_for_task_19_4() {
    const char *str1 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_4.txt";
    const char *str2 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_4_test.txt";
    int ans = task_19_4(str1, "hi");

    if (ans == 0) {
        ASSERT_TXT(str1, str2);
    }
}

int task_19_5(const char *str) {
    // Открываем файл для чтения
    FILE *inputFile = fopen(str, "r");
    if (inputFile == NULL) {
        printf("File opening error\n");
        return 1;
    }

    // Открываем файл для записи
    FILE *outputFile = fopen("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", "w");
    if (outputFile == NULL) {
        printf("File opening error\n");
        fclose(inputFile);
        return 1;
    }

    char line[1000], longest_word[100];
    int maxLen = 0;

    // Считываем каждую строку из входного файла
    while (fgets(line, sizeof(line), inputFile)) {
        char *token = strtok(line, " ");
        while (token != NULL) {
            if (strlen(token) > maxLen) {
                maxLen = strlen(token);
                strcpy(longest_word, token);
            }
            token = strtok(NULL, " ");
        }

        // Записываем самое длинное слово в выходной файл
        fprintf(outputFile, "%s", longest_word);

        // Сбрасываем значения для следующей строки
        maxLen = 0;
        longest_word[0] = '\0';
    }

    printf("The longest words from each line are saved\n");

    fclose(inputFile);
    fclose(outputFile);

    copyFileContent("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", str);

    return 0;
}

void test_for_task_19_5() {
    const char *str1 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_5.txt";
    const char *str2 = "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_5_test.txt";
    int ans = task_19_5(str1);

    if (ans == 0) {
        ASSERT_TXT(str1, str2);
    }
}

int main() {
    test_for_task_19_5();
    return 0;
}