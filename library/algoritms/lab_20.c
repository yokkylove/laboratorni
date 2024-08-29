#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "C:/Users/tanya/CLionProjects/GG/library/date_structurs/matrix.h"
#include <string.h>
#include <stdbool.h>
#include "C:/Users/tanya/CLionProjects/GG/library/date_structurs/vector.h"
#include "conio.h"

typedef struct {
    int row;
    int col;
    int **board;
    int **nextState;
    int boardSize;
    int *boardColSize;
} CellArgs;

typedef struct domain{
    size_t visits;
    char name[200];
} domain;

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

int **matrix_task_1;

void *increment_submatrix(void *arg) {
    int *query = (int *)arg;
    int row1 = query[0], col1 = query[1], row2 = query[2], col2 = query[3];

    for (int i = row1; i <= row2; i++) {
        for (int j = col1; j <= col2; j++) {
            matrix_task_1[i][j]++;
        }
    }

    pthread_exit(NULL);
}

void task_1(int n, int num_queries, int **queries) {

    matrix_task_1 = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix_task_1[i] = (int *)calloc(n, sizeof(int));
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
            assert(matrix_task_1[i][j] == matrix_t[i][j]);
        }
    }
}

void *processCell(void *arg) {
    CellArgs *cellArgs = (CellArgs *)arg;
    int row = cellArgs->row;
    int col = cellArgs->col;
    int **board = cellArgs->board;
    int **nextState = cellArgs->nextState;
    int boardSize = cellArgs->boardSize;
    int *boardColSize = cellArgs->boardColSize;

    int liveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int r = row + i, c = col + j;
            if (r >= 0 && r < boardSize && c >= 0 && c < boardColSize[r]) {
                liveNeighbors += board[r][c];
            }
        }
    }

    if (board[row][col] == 1) {
        if (liveNeighbors < 2 || liveNeighbors > 3) {
            nextState[row][col] = 0;
        } else {
            nextState[row][col] = 1;
        }
    } else {
        if (liveNeighbors == 3) {
            nextState[row][col] = 1;
        } else {
            nextState[row][col] = 0;
        }
    }

    free(cellArgs);
    pthread_exit(NULL);
}

void task_2(int **board, int boardSize, int *boardColSize) {
    int **nextState = (int **)malloc(boardSize * sizeof(int *));
    for (int i = 0; i < boardSize; i++) {
        nextState[i] = (int *)calloc(boardColSize[i], sizeof(int));
    }

    pthread_t threads[boardSize * boardColSize[0]];
    int threadIndex = 0;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            CellArgs *cellArgs = (CellArgs *)malloc(sizeof(CellArgs));
            cellArgs->row = i;
            cellArgs->col = j;
            cellArgs->board = board;
            cellArgs->nextState = nextState;
            cellArgs->boardSize = boardSize;
            cellArgs->boardColSize = boardColSize;

            pthread_create(&threads[threadIndex++], NULL, processCell, (void *)cellArgs);
        }
    }

    for (int i = 0; i < threadIndex; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < boardSize; i++) {
        free(board[i]);
        board[i] = nextState[i];
        nextState[i] = NULL;
    }
    free(nextState);
}

void test_for_task_2() {
    int countCol = 3;
    int boardSize = 4;
    int boardColSize[] = {3, 3, 3, 3};
    int **board = (int **)malloc(boardSize * sizeof(int *));
    for (int i = 0; i < boardSize; i++) {
        board[i] = (int *)malloc(boardColSize[i] * sizeof(int));
    }

    board[0][0] = 0; board[0][1] = 1; board[0][2] = 0;
    board[1][0] = 0; board[1][1] = 0; board[1][2] = 1;
    board[2][0] = 1; board[2][1] = 1; board[2][2] = 1;
    board[3][0] = 0; board[3][1] = 0; board[3][2] = 0;

    task_2(board, boardSize, boardColSize);

    int **board_t = (int **)malloc(boardSize * sizeof(int *));
    for (int i = 0; i < boardSize; i++) {
        board_t[i] = (int *)malloc(boardColSize[i] * sizeof(int));
    }

    board_t[0][0] = 0; board_t[0][1] = 0; board_t[0][2] = 0;
    board_t[1][0] = 1; board_t[1][1] = 0; board_t[1][2] = 1;
    board_t[2][0] = 0; board_t[2][1] = 1; board_t[2][2] = 1;
    board_t[3][0] = 0; board_t[3][1] = 1; board_t[3][2] = 0;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < countCol; ++j) {
            assert(board[i][j] == board_t[i][j]);
        }
    }
}

int sortedNumsCompare(const void * first_num, const void * second_num){
    return (*(int*)first_num - *(int*)second_num);
}


void fillingNumFrameSorted(int *array, matrix m, size_t ind_row, size_t ind_col){ size_t
            arrayInd = 0;
    for (size_t mIndRow = ind_row - 1; mIndRow < ind_row + 2; mIndRow++){
        for(size_t mIndCol = ind_col - 1; mIndCol < ind_col + 2; mIndCol++){
            if (mIndRow != ind_row || mIndCol != ind_col){
                array[arrayInd++] = m.values[mIndRow][mIndCol];
            }
        }
    }
    qsort(array, 8, sizeof(int), sortedNumsCompare);
}

void task_3(matrix *m, size_t size){
    int frame[8];
    for (size_t indRow = 1; indRow < size - 1; indRow++){
        for(size_t indCol = 1; indCol < size - 1; indCol++){
            fillingNumFrameSorted(frame, *m, indRow, indCol);
            int median = (frame[3] + frame[4]) / 2;
            m->values[indRow][indCol] = median;
        }
    }
}

void test_for_task_3(){
    size_t size = 3;
    matrix got = createMatrixFromArray((int[]) {
            10, 20, 30,
            25, 35, 45,
            15, 25, 35
    }, 3, 3);
    task_3(&got, size);
    matrix expected = createMatrixFromArray( (int[]) {
            10, 20, 30,
            25, 25, 45,
            15, 25, 35
    }, 3, 3);
    assert(areTwoMatricesEqual(&got, &expected));
}

size_t searchDomainInResults(const domain results[], size_t size, char *s){ for
            (size_t ind = 0; ind < size; ind++){
        if (strcmp(results[ind].name, s) == 0){
            return ind;
        }
    }
    return size;
}

void handlerDotPrtNotNull(domain *array, size_t ind, char *dotPtr, domain
results[], size_t *sizeResult){
    strcpy(array[ind].name, dotPtr + 1);
    size_t pos = searchDomainInResults(results, *sizeResult,
                                       array[ind].name);
    if (pos == *sizeResult){
        results[*sizeResult] = array[ind];
        *sizeResult += 1;
    } else{
        results[pos].visits += array[ind].visits;
    }
}

bool searchNumFromArray(const size_t array[], size_t length, size_t num){ for
            (size_t ind = 0; ind < length; ind++){
        if (num == array[ind]){
            return true;
        }
    }
    return false;
}

void outputResultDomains(domain *results, size_t size){
    for (size_t ind = 0; ind < size; ind++){
        printf("%ld %s\n", results[ind].visits, results[ind].name); }
}

void task_4(domain array[], size_t size){
    size_t closeIndexes[size];
    size_t countClose = 0;
    domain results[200];
    size_t sizeResult = 0;
    for (size_t ind = 0; ind < size; ind++){
        results[sizeResult++] = array[ind];
    }
    while(countClose != size){
        for (size_t ind = 0; ind < size; ind++){
            if (!searchNumFromArray(closeIndexes, countClose, ind)){ char *dotPtr =
                        strchr(array[ind].name, '.');
                if (dotPtr != NULL){
                    handlerDotPrtNotNull(array, ind, dotPtr,
                                         results, &sizeResult);
                } else{
                    closeIndexes[countClose++] = ind;
                }
            }
        }
    }
    outputResultDomains(results, sizeResult);
}

void test_for_task_4(){
    size_t size = 4;
    domain array[4] = {{900, "google.mail.com"},
                       {50,"yahoo.com"},
                       {1, "intel.mail.com"},
                       {5, "wiki.org"}};
    task_4(array, size);
}

void fillingCalcMatrix(matrix m, matrix *calcMatrix, size_t rows, size_t cols){
    for (size_t indRow = 0; indRow < rows; indRow++){
        for (size_t indCol = 0; indCol < cols; indCol++){
            if (m.values[indRow][indCol] == 1){
                if (indRow != 0){
                    calcMatrix->values[indRow][indCol] =
                            calcMatrix->values[indRow - 1][indCol] + 1;
                }
                else{
                    calcMatrix->values[indRow][indCol] = 1;
                }
            } else {
                calcMatrix->values[indRow][indCol] = 0;
            }
        }
    }
}

void task_5(matrix m, size_t rows, size_t cols, size_t *result){
    matrix calcMatrix = getMemMatrix(rows, cols);
    fillingCalcMatrix(m, &calcMatrix, rows, cols);
    size_t calcResult = 0;
    for (size_t indCol = 0; indCol < cols; indCol++){
        for (size_t indRow = 0; indRow < rows; indRow++){
            for (size_t indK = indCol + 1; indK < cols + 1; indK++){
                int min = calcMatrix.values[indRow][indCol];
                for (size_t indFromColToK = indCol; indFromColToK < indK; indFromColToK++){
                    if (calcMatrix.values[indRow][indFromColToK] < min){
                        min = calcMatrix.values[indRow][indFromColToK];
                    }
                }
                calcResult += min;
            }
        }
    }
    *result = calcResult;
}

void test_for_task_5(){
    size_t rows1 = 3;
    size_t cols1 = 3;
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 1,
                    1, 1, 0,
                    1, 1, 0
            }, 3, 3
    );
    size_t result1 = 0;
    task_5(m1, rows1, cols1, &result1);
    assert(result1 == 13);
    size_t rows2 = 3;
    size_t cols2 = 4;
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    0, 1, 1, 0,
                    0, 1, 1, 1,
                    1, 1, 1, 0
            }, 3, 4
    );
    size_t result2 = 0;
    task_5(m2, rows2, cols2, &result2);
    assert(result2 == 24);
}

void task_6(const char *s, size_t length, char *result, size_t *resultLength){
    char buffer[10];
    size_t bufferLength = 0;
    size_t calcResultLength = 0;
    char num = '1';
    for (size_t ind = 0; ind < length; ind++) {
        buffer[bufferLength++] = num++;
        if (s[ind] == 'I') {
            while (bufferLength > 0)
                result[calcResultLength++] = buffer[--bufferLength];
        }
    }
    buffer[bufferLength++] = num;
    while (bufferLength > 0)
        result[calcResultLength++] = buffer[--bufferLength];
    result[calcResultLength] = '\0';
    *resultLength = calcResultLength;
}

void test_for_task_6(){
    char s1[10] = "IIIDIDDD";
    size_t length1 = 8;
    char got1[10];
    size_t resLength1;
    task_6(s1, length1, got1, &resLength1);
    char expected1[10] = "123549876";
    assert(strcmp(got1, expected1) == 0);

    char s2[5] = "DDD";
    size_t length2 = 3;
    char got2[5];
    size_t resLength2;
    task_6(s2, length2, got2, &resLength2);
    char expected2[10] = "4321";
    assert(strcmp(got2, expected2) == 0);
}

node *createNode(int k) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = k;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
node* insert(node *p, int k, bool isLeft) {
    node *newNode = createNode(k);
    if (isLeft)
        p->left = newNode;
    else
        p->right = newNode;
    return newNode;
}

int searchMaxInd(const int array[], int start, int end){
    if (start > end){
        return end + 1;
    } else{
        int maxNumInd = start;
        for (int ind = start + 1; ind <= end; ind++){
            if (array[ind] > array[maxNumInd]){
                maxNumInd = ind;
            }
        }
        return maxNumInd;
    }
}

void buildNodes(node *p, int array[], int start, int end, bool isLeft){ int
            maxNumInd = searchMaxInd(array, start, end);
    if (maxNumInd == end + 1){
        if (isLeft)
            p->left = NULL;
        else
            p->right = NULL;
        printf("null ");
        return;
    } else{
        printf("%d ", array[maxNumInd]);
        node *newNode = insert(p, array[maxNumInd], isLeft);
        buildNodes(newNode, array, start, maxNumInd - 1, true);
        buildNodes(newNode, array, maxNumInd + 1, end, false); }
}

void task_7(int array[], int lengthArray){
    if (lengthArray == 0){
        return;
    } else {
        int maxNumInd = searchMaxInd(array, 0, lengthArray - 1);
        node *newNode = createNode(array[maxNumInd]); printf("%d ", array[maxNumInd]);
        buildNodes(newNode, array, 0, maxNumInd - 1, true);
        buildNodes(newNode, array,maxNumInd + 1, lengthArray - 1, false);
        printf("\n");
    }
}

void test_for_task_7(){
    int array1[6] = {3, 2, 1, 6, 0, 5};
    int lengthArray1 = 6;
    task_7(array1, lengthArray1);

    int array2[3] = {3, 2, 1};
    int lengthArray2 = 3;
    task_7(array2, lengthArray2);
}

void task_8(const char *s, size_t length, const size_t indexes[], char *newS){
    for (size_t ind = 0; ind < length; ind++){
        newS[ind] = s[indexes[ind]];
    }
    newS[length] = '\0';
}

void test_for_task_8(){
    char s1[4] = "abc";
    size_t lengthS1 = 3;
    size_t indexes1[3] = {0, 1, 2};
    char got1[4];
    task_8(s1, lengthS1, indexes1, got1);
    char expected1[4] = "abc";
    assert(strcmp(got1, expected1) == 0);

    char s2[5] = "abap";
    size_t lengthS2 = 4;
    size_t indexes2[4] = {0, 3, 2, 1};
    char got2[5];
    task_8(s2, lengthS2, indexes2, got2);
    char expected2[5] = "apab";
    assert(strcmp(got2, expected2) == 0);
}

FILE* openFile(char *fileName, char *action){
    FILE *file = fopen(fileName, action);
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        exit(1);
    }
    return file;
}

void fillingFile(int numsArray[], size_t lengthArray, char *fileName){
    FILE *file = openFile(fileName, "w");
    for (size_t ind = 0; ind < lengthArray; ind++){
        fprintf(file, "%d ", numsArray[ind]);
    }
    fclose(file);
}

void readingNumsFilteringAndWriting(vector *v, char *rFileName, int
controlNum, char *wFileName){
    FILE *rFile = openFile(rFileName, "r");
    FILE *wFile = openFile(wFileName, "w");
    int num;
    while (fscanf(rFile, "%d", &num) == 1){
        if (num < controlNum){
            pushBack(v, num);
            fprintf(wFile, "%d ", num);
        }
    }
    fclose(rFile);
    fclose(wFile);
}

void task_9(int numsArray[], size_t lengthArray, int controlNum, char *firstFileName, char *secondFileName, vector *v){
    fillingFile(numsArray, lengthArray,firstFileName);
    readingNumsFilteringAndWriting(v, firstFileName, controlNum, secondFileName);
    shrinkToFit(v);
}

void test_for_task_9(){
    int numsArray[5] = {2, 4, 1, 3, 5};
    size_t lengthArray = 5;
    int controlNum = 3;
    char *firstFileName = "C:/Users/User/Desktop/lab_20_9_1.txt";
    char *secondFileName = "C:/Users/User/Desktop/lab_20_9_2.txt";
    vector v = createVector(10);

    task_9(numsArray, lengthArray, controlNum, firstFileName, secondFileName, &v);

    size_t expectedLength = 2;
    int expectedArrayNums[2] = {2, 1};
    assert(expectedLength == v.size);
    for (size_t ind = 0; ind < expectedLength; ind++){
        assert(v.data[ind] == expectedArrayNums[ind]); }
}

void fillingFileWithText(char *fileName, char *text){
    FILE *file = openFile(fileName, "w");
    fprintf(file, "%s", text);
    fclose(file);
}

void task_10(char *fileName, size_t countOutputLines, char *text){
    fillingFileWithText(fileName, text);
    FILE *file = openFile(fileName, "r");
    char line[127];
    size_t count = 0;
    while (fgets(line, 127, file) != NULL) {
        printf("%s", line);
        count++;
        if (count == countOutputLines){
            printf("Please, press Ctrl + C\n");
            while (getch() != 3);
        }
    }
}

void test_for_task_10(){
    char *fileName = "../tenthTask.txt";
    size_t countOutputLines = 3;
    char text[200] = "123\n456\n789\n0";
    task_10(fileName, countOutputLines, text);
}

void tests_all() {
    test_for_task_1();
    test_for_task_2();
    test_for_task_3();
    test_for_task_4();
    test_for_task_5();
    test_for_task_6();
    test_for_task_7();
    test_for_task_8();
    test_for_task_9();
    test_for_task_10();
}

int main(){
    tests_all();
}