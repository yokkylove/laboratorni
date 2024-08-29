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

int main() {
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