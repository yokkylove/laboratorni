#include <stdio.h>
#include <string.h>
#include <math.h>

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

int main1() {
    FILE *file = fopen("C:/Users/tanya/CLionProjects/GG/library/algoritms/19_1.txt", "r");
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
        fprintf(output_file, "\n");
    }

    fclose(file);
    fclose(output_file);

    copyFileContent("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_1.txt");

    return 0;
}

int main2() {
    FILE *input_file = fopen("C:/Users/tanya/CLionProjects/GG/library/algoritms/19_2.txt", "r");
    FILE *output_file = fopen("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", "w");
    double number;

    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    while (fscanf(input_file, "%lf", &number) == 1) {
        fprintf(output_file, "%.2f\n", number);
    }

    printf("Conversion completed successfully.\n");

    fclose(input_file);
    fclose(output_file);

    copyFileContent("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_2.txt");

    return 0;
}

int main3() {
    // Открываем файл для чтения и записи
    FILE *file = fopen("C:/Users/tanya/CLionProjects/GG/library/algoritms/19_3.txt", "r+");
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

int main() {
    // Открываем файл для чтения
    FILE *inputFile = fopen("C:/Users/tanya/CLionProjects/GG/library/algoritms/19_4.txt", "r");
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

    char word[100], sequence[20];

    printf("Enter a sequence of characters: ");
    scanf("%s", sequence);

    // Считываем каждое слово из входного файла
    while (fscanf(inputFile, "%s", word) != EOF) {
        // Проверяем содержит ли слово заданную последовательность символов
        if (strstr(word, sequence) != NULL) {
            // Записываем слово в выходной файл
            fprintf(outputFile, "%s\n", word);
        }
    }

    printf("Words containing a sequence of characters are saved\n");

    fclose(inputFile);
    fclose(outputFile);

    copyFileContent("C:/Users/tanya/CLionProjects/GG/library/algoritms/1.txt", "C:/Users/tanya/CLionProjects/GG/library/algoritms/19_4.txt");

    return 0;
}