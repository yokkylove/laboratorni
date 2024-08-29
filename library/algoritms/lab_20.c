#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int **matrix;

void *increment_submatrix(void *arg) {
    int *query = (int *)arg;
    int row1 = query[0], col1 = query[1], row2 = query[2], col2 = query[3];

    for (int i = row1; i <= row2; i++) {
        for (int j = col1; j <= col2; j++) {
            matrix[i][j]++;
        }
    }

    pthread_exit(NULL);
}

void task_1(int n, int num_queries, int **queries) {

    matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)calloc(n, sizeof(int));
    }

    pthread_t threads[num_queries];
    for (int i = 0; i < num_queries; i++) {
        pthread_create(&threads[i], NULL, increment_submatrix, (void *)queries[i]);
    }

    for (int i = 0; i < num_queries; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < num_queries; i++) {
        free(queries[i]);
    }
    free(queries);
}

void test_for_task_1() {
    int n = 3;
    int num_queries = 2;
    int **queries;

    queries = (int **)malloc(num_queries * sizeof(int *));
    for (int i = 0; i < num_queries; i++) {
        queries[i] = (int *)malloc(4 * sizeof(int));
    }

    queries[0][0] = 1; queries[0][1] = 1; queries[0][2] = 2; queries[0][3] = 2;
    queries[1][0] = 0; queries[1][1] = 0; queries[1][2] = 1; queries[1][3] = 1;

    task_1(n, num_queries, queries);

    int **matrix_t;

    matrix_t = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix_t[i] = (int *)calloc(n, sizeof(int));
    }
    matrix_t[0][0] = 1; matrix_t[0][1] = 1; matrix_t[0][2] = 0;
    matrix_t[1][0] = 1; matrix_t[1][1] = 2; matrix_t[1][2] = 1;
    matrix_t[2][0] = 0; matrix_t[2][1] = 1; matrix_t[2][2] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(matrix[i][j] == matrix_t[i][j]);
        }
    }
}

int main() {
    test_for_task_1();
}