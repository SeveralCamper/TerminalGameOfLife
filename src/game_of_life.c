#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int arrayInitInt(int **array, int arrayLines, int arrayColumns, int *exitFlag);
char arrayInitChar(char **array, int arrayLines, int arrayColumns, int *exitFlag);

int arrayFieldIntRand(int **array, int arrayLines, int arrayColumns);
char arrayFieldChar(int **arrayInt, char **arrayChar, int arrayLines, int arrayColumns);

int arrayOutputInt(int **array, int arrayLines, int arrayColumns);
char arrayOutputChar(char **array, int arrayLines, int arrayColumns);

void reDrawBorders(int **array, int arrayLines, int arrayColumns);
void initUniverse(int **arrayInt, char **arrayChar,  int arrayColumns, int arrayLines, int *exitFlag);
void logic(int **arrayInt, int **arrayTemp, int arrayColumns, int arrayLines, int *liveCellsScore);
void countAndCheckingLife(int **arrayInt, int **arrayTemp, int arrayColumns, int arrayLines);
void startGame(int **arrayInt, int **arrayTemp,
    char **arrayChar, int arrayColumns, int arrayLines, int *exitFlag);
void workWithFile(int **arrayInt, char name[],
    int arrayColumns, int arrayLines, int *exitFlag);
void tempArrToInt(int **arrayInt, int **arrayTemp,
    int arrayColumns, int arrayLines);
void zeroing(int **arrayInt, int arrayColumns, int arrayLines);
void waitFor(int secs);
void step();
void clear();

enum Conditions {
    DIEDCELLS = 0,
    BORNCELLS,
    LIVECELLS,
    TDBORDESRS,
    LRBORDERS
};

int main() {
    step();
    return 0;
}

int arrayInitInt(int **array, int arrayLines, int arrayColumns, int *exitFlag) {
    if (array == NULL) {
        printf("Недостаточно памяти для выделения индексного массива\n");
        *exitFlag = 0;
    }

    array[0] = (int *) malloc(sizeof(int) * arrayLines * arrayColumns);

    if (array[0] == NULL) {
        printf("Недостаточно памяти для выделения матрицы\n");
        free(array);
        *exitFlag = 0;
    }

    for (int i = 1; i < arrayLines; i++) {
        array[i] = array[i-1] + arrayColumns;
    }

    return 0;
}

char arrayInitChar(char **array, int arrayLines, int arrayColumns, int *exitFlag) {
    if (array == NULL) {
        printf("Недостаточно памяти для выделения индексного массива\n");
        *exitFlag = 0;
    }

    array[0] = (char *) malloc(sizeof(char) * arrayLines * arrayColumns);

    if (array[0] == NULL) {
        printf("Недостаточно памяти для выделения матрицы\n");
        free(array);
        *exitFlag = 0;
    }

    for (int i = 1; i < arrayLines; i++)
        array[i] = array[i-1] + arrayColumns;

    return 0;
}

int arrayFieldIntRand(int **array, int arrayLines, int arrayColumns) {
    for (int i = 0; i < arrayLines; i++) {
        for (int j = 0; j < arrayColumns; j++) {
            array[i][j] = DIEDCELLS;
            if (i + 1 != arrayLines) {
                array[i][0] = LRBORDERS;
            }
            array[i][arrayColumns-1] = LRBORDERS;
            array[0][j] = TDBORDESRS;
            array[arrayLines-1][j] = TDBORDESRS;
        }
    }

    for (int i = 1; i < arrayLines-1; i++) {
        for (int j = 1; j < arrayColumns-1; j +=2) {
            array[i][j] = rand() % 3;
        }
    }
    return 0;
}

char arrayFieldChar(int **arrayInt, char **arrayChar, int arrayLines, int arrayColumns) {
    char liveCell = 'o';
    char bornCell = '*';
    char deadCell = ' ';
    char TDBorders = '-';
    char LRBorders = '|';
    for (int i = 0; i < arrayLines; i++) {
        for (int j = 0; j < arrayColumns; j++) {
            if (arrayInt[i][j] == DIEDCELLS) {
                arrayChar[i][j] = deadCell;
            } else if (arrayInt[i][j] == LIVECELLS) {
                arrayChar[i][j] = liveCell;
            } else if (arrayInt[i][j] == TDBORDESRS) {
                arrayChar[i][j] = TDBorders;
            } else if (arrayInt[i][j] == LRBORDERS) {
                arrayChar[i][j] = LRBorders;
            } else if (arrayInt[i][j] == BORNCELLS) {
                arrayChar[i][j] = bornCell;
            }
        }
    }
    return 0;
}

int arrayOutputInt(int **array, int arrayLines, int arrayColumns) {
    for (int i = 0; i < arrayLines; i++) {
        for (int j = 0; j < arrayColumns; j++)
            if (j + 1 == arrayColumns) {
                printf("%d", array[i][j]);
            } else {
                printf("%d ", array[i][j]);
            }
        printf("\n");
    }
    return 0;
}

char arrayOutputChar(char **array, int arrayLines, int arrayColumns) {
    for (int i = 0; i < arrayLines; i++) {
        for (int j = 0; j < arrayColumns; j++)
            if (j + 1 == arrayColumns) {
                printf("%c", array[i][j]);
            } else {
                printf("%c ", array[i][j]);
            }
        printf("\n");
    }
    return 0;
}

void step() {
    int arrayLines = 27;
    int arrayColumns = 82;
    int exitFlag = 1;
    int **flagArray = (int**) malloc(sizeof(int *) * arrayLines);
    int **tempArray = (int**) malloc(sizeof(int *) * arrayLines);
    char **arrayChar = (char**) malloc(sizeof(char *) * arrayLines);
    initUniverse(flagArray, arrayChar, arrayColumns, arrayLines, &exitFlag);
    arrayInitInt(tempArray, arrayLines, arrayColumns, &exitFlag);
    arrayFieldIntRand(tempArray, arrayLines, arrayColumns);
    int gameMode;
    char c;
    if ((scanf("%d%c", &gameMode, &c) == 2) && (c == '\n') && (gameMode > 0) && (gameMode < 7)) {
        switch (gameMode) {
        case 1: {
            char fileName[] = "./src/staticBlocksAndOscillators.txt";
            clear();
            printf("FIRST MODE\n");
            workWithFile(flagArray, fileName, arrayColumns, arrayLines, &exitFlag);
            tempArrToInt(flagArray, tempArray, arrayColumns, arrayLines);
            if (exitFlag != 0) {
                startGame(flagArray, tempArray, arrayChar, arrayColumns, arrayLines, &exitFlag);
            }
            break;
        }
        case 2: {
            char fileName[] = "./src/shotguns.txt";
            clear();
            printf("SECOND MODE\n");
            workWithFile(flagArray, fileName, arrayColumns, arrayLines, &exitFlag);
            tempArrToInt(flagArray, tempArray, arrayColumns, arrayLines);
            if (exitFlag != 0) {
                startGame(flagArray, tempArray, arrayChar, arrayColumns, arrayLines, &exitFlag);
            }
            break;
        }
        case 3: {
            char fileName[] = "./src/crativeFromJtony.txt";
            clear();
            printf("THIRD MODE\n");
            workWithFile(flagArray, fileName, arrayColumns, arrayLines, &exitFlag);
            tempArrToInt(flagArray, tempArray, arrayColumns, arrayLines);
            if (exitFlag != 0) {
                startGame(flagArray, tempArray, arrayChar, arrayColumns, arrayLines, &exitFlag);
            }
            break;
        }
        case 4: {
            char fileName[] = "./src/spaceships.txt";
            clear();
            printf("FORTH MODE\n");
            workWithFile(flagArray, fileName, arrayColumns, arrayLines, &exitFlag);
            tempArrToInt(flagArray, tempArray, arrayColumns, arrayLines);
            if (exitFlag != 0) {
                startGame(flagArray, tempArray, arrayChar, arrayColumns, arrayLines, &exitFlag);
            }
            break;
        }
        case 5: {
            char fileName[] = "./src/creativeFromWjeane.txt";
            clear();
            printf("FIFTH MODE:\n");
            workWithFile(flagArray, fileName, arrayColumns, arrayLines, &exitFlag);
            tempArrToInt(flagArray, tempArray, arrayColumns, arrayLines);
            if (exitFlag != 0) {
                startGame(flagArray, tempArray, arrayChar, arrayColumns, arrayLines, &exitFlag);
            }
            break;
        }
        case 6: {
            startGame(flagArray, tempArray, arrayChar, arrayColumns, arrayLines, &exitFlag);
            }
        }
    } else {
        printf("n/a");
    }
}

void initUniverse(int **arrayInt, char **arrayChar,  int arrayColumns, int arrayLines, int *exitFlag) {
    clear();
    printf("CHOUSE YOUR MODE FROM 1 TO 6\n");
    arrayInitInt(arrayInt, arrayLines, arrayColumns, exitFlag);
    arrayFieldIntRand(arrayInt, arrayLines, arrayColumns);
    arrayInitChar(arrayChar, arrayLines, arrayColumns, exitFlag);
    arrayFieldChar(arrayInt, arrayChar, arrayLines, arrayColumns);
    arrayOutputChar(arrayChar, arrayLines, arrayColumns);

    printf("1 MODE: Static blocks and oscillators mode\n");
    printf("2 MODE: Shotguns - configurations generating gliders or other configurations\n");
    printf("3 MODE: Creative from jtony\n");
    printf("4 MODE: Spaceships are another kind of oscillator that moves infinitely in one direction\n");
    printf("5 MODE: Creative from wjeane\n");
    printf("6 MODE: Random\n");
}

void workWithFile(int **arrayInt, char name[],  int arrayColumns, int arrayLines, int *exitFlag) {
    FILE *fp;
    char fileSymbol;

    zeroing(arrayInt, arrayColumns, arrayLines);

    if ((fp = fopen(name, "r")) == NULL) {
        printf("Не удалось открыть файл");
        *exitFlag = 0;
    } else {
        for (int i = 0; i < arrayLines; i++) {
            for (int j = 0; j < arrayColumns; j++) {
                fileSymbol = fgetc(fp);
                if (fileSymbol == '\n') {
                    fileSymbol = fgetc(fp);
                    break;
                }
                if (fileSymbol == '0') {
                    arrayInt[i][j] = 0;
                } else if (fileSymbol == '1') {
                    arrayInt[i][j] = 1;
                } else if (fileSymbol == EOF) {
                    fclose(fp);
                    }
            }
        }
    }
}

void logic(int **arrayInt, int **arrayTemp, int arrayColumns, int arrayLines, int *liveCellsScore) {
    for (int i = 0; i < arrayLines; i++) {
        for (int j = 0; j < arrayColumns; j++) {
            arrayInt[i][0] = arrayInt[i][arrayColumns-2];
            arrayInt[i][arrayColumns-1] = arrayInt[i][1];
            arrayInt[0][j] = arrayInt[arrayLines-2][j];
            arrayInt[arrayLines-1][j] = arrayInt[1][j];
            arrayInt[0][0] = DIEDCELLS;
            arrayInt[arrayLines-1][arrayColumns-1] = DIEDCELLS;
            arrayInt[0][arrayColumns-1] = DIEDCELLS;
            arrayInt[arrayLines-1][0] = DIEDCELLS;
        }
    }
    countAndCheckingLife(arrayInt, arrayTemp, arrayColumns, arrayLines);

    for (int i = 1; i < arrayLines - 1; i++) {
        for (int j = 1; j < arrayColumns - 1; j++) {
            arrayInt[i][j] = arrayTemp[i][j];
            if (arrayInt[i][j] == BORNCELLS || arrayInt[i][j] == LIVECELLS) {
                *liveCellsScore += 1;
            }
        }

    reDrawBorders(arrayInt, arrayLines, arrayColumns);
    }
}

void countAndCheckingLife(int **arrayInt, int **arrayTemp, int arrayColumns, int arrayLines) {
    for (int i = 1; i < arrayLines - 1; i++) {
        for (int j = 1; j < arrayColumns - 1; j++) {
            int count = 0;
            for (int k = i - 1; k < i + 2; k++) {
                for (int l = j - 1; l < j + 2; l++) {
                    if (arrayInt[k][l] == LIVECELLS || arrayInt[k][l] == BORNCELLS) {
                        count += 1;
                    }
                }
            }
            if (arrayInt[i][j] == LIVECELLS || arrayInt[i][j] == BORNCELLS) {
                count -= 1;
            }
            if ((arrayInt[i][j] == LIVECELLS || arrayInt[i][j] == BORNCELLS) &&
            (count == 2 || count == 3)) {
                arrayTemp[i][j] = LIVECELLS;
            } else if ((arrayInt[i][j] == LIVECELLS || arrayInt[i][j] == BORNCELLS) &&
            (count < 2 || count > 3)) {
                arrayTemp[i][j] = DIEDCELLS;
            } else if ((arrayTemp[i][j] == DIEDCELLS) && (count == 3)) {
                arrayTemp[i][j] = BORNCELLS;
            } else if ((arrayTemp[i][j] == DIEDCELLS) && (count != 3)) {
                arrayTemp[i][j] = DIEDCELLS;
            }
        }
    }
}

void zeroing(int **arrayInt, int arrayColumns, int arrayLines) {
    for (int i = 0; i < arrayLines; i++) {
        for (int j = 0; j < arrayColumns; j ++) {
            arrayInt[i][j] = 0;
        }
    }
}

void tempArrToInt(int **arrayInt, int **arrayTemp, int arrayColumns, int arrayLines) {
    for (int i = 0; i < arrayLines; i++) {
        for (int j = 0; j < arrayColumns; j ++) {
            arrayTemp[i][j] = arrayInt[i][j];
        }
    }
}

void reDrawBorders(int **array, int arrayLines, int arrayColumns) {
    for (int i = 0; i < arrayLines; i++) {
        for (int j = 0; j < arrayColumns; j++) {
            if (i + 1 != arrayLines) {
                array[i][0] = LRBORDERS;
            }
            array[i][arrayColumns-1] = LRBORDERS;
            array[0][j] = TDBORDESRS;
            array[arrayLines-1][j] = TDBORDESRS;
        }
    }
}



void startGame(int **arrayInt, int **arrayTemp, char **arrayChar,
    int arrayColumns, int arrayLines, int *exitFlag) {
    int liveCellsScore = 0;
    int liveCellsFlag = 1;
    int iteration = 0;
    while (liveCellsFlag == 1) {
        if (exitFlag != 0) {
            iteration += 1;
            waitFor(1);
            clear();
            liveCellsScore = 0;
            logic(arrayInt, arrayTemp, arrayColumns, arrayLines, &liveCellsScore);
            arrayFieldChar(arrayInt, arrayChar, arrayLines, arrayColumns);
            arrayOutputChar(arrayChar, arrayLines, arrayColumns);
            printf("ЖИВЫЕ КЛЕТКИ: %d    ПОКОЛЕНИЕ: %d\n", liveCellsScore, iteration);

            if (liveCellsScore == 0) {
                liveCellsFlag = 0;
                printf("Game is over!");
                free(arrayInt[0]);
                free(arrayInt);

                free(arrayChar[0]);
                free(arrayChar);

                free(arrayTemp[0]);
                free(arrayTemp);
                }
            }
        }
}

void waitFor(int secs) {
    int retTime = time(0) + secs;
    while (time(0) < retTime) {
    }
}

void clear() {
    printf("\33c\e[3J");
}
