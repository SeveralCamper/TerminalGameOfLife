#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

int arrayInitInt(int **array, int arrayLines, int arrayColumns, int *exitFlag);
char arrayInitChar(char **array, int arrayLines, int arrayColumns, int *exitFlag);

int arrayFieldInt(int **array, int arrayLines, int arrayColumns);
char arrayFieldChar(int **arrayInt, char **arrayChar, int arrayLines, int arrayColumns);

int arrayOutputInt(int **array, int arrayLines, int arrayColumns);
char arrayOutputChar(char **array, int arrayLines, int arrayColumns);

void initUniverse(int **arrayInt, char **arrayChar,  int arrayColumns, int arrayLines, int *exitFlag);
void logic(int **arrayInt, int **arrayTemp, int arrayColumns, int arrayLines, int *liveCellsScore);
void waitFor (unsigned int secs);
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

int arrayFieldInt(int **array, int arrayLines, int arrayColumns) {
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
            } else if (arrayInt[i][j] == BORNCELLS){
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
    int liveCellsScore = 0;
    int liveCellsFlag = 1;
    int arrayLines = 27;
    int arrayColumns = 82;
    int exitFlag = 1;
    int **flagArray = (int**) malloc(sizeof(int *) * arrayLines);
    int **tempArray = (int**) malloc(sizeof(int *) * arrayLines);
    char **arrayChar = (char**) malloc(sizeof(char *) * arrayLines);
    initUniverse(flagArray, arrayChar, arrayColumns, arrayLines, &exitFlag);
    arrayInitInt(tempArray, arrayLines, arrayColumns, &exitFlag);
    arrayFieldInt(tempArray, arrayLines, arrayColumns);
    //arrayOutputInt(tempArray, arrayLines, arrayColumns);
    int gameMode;
    char c;
    if ((scanf("%d%c", &gameMode, &c) == 2) && (c == '\n') && (gameMode > 0) && (gameMode < 7)) {
        switch (gameMode) {
        case 1: {
            printf("First mode\n");
            break;
        }
        case 2: {
            printf("Second mode\n");
            break;
        }
        case 3: {
            printf("Third mode\n");
            break;
        }
        case 4: {
            printf( "Forth mode\n" );
            break;
        }
        case 5: {
            printf( "Fifth mode:\n" );
            break;
        }
        case 6: {
            printf( "RANDOM MODE:\n" );
            while (liveCellsFlag == 1) {
                if(exitFlag != 0) {
                    waitFor (1);
                    clear();
                    liveCellsScore = 0;
                    logic(flagArray, tempArray, arrayColumns, arrayLines, &liveCellsScore);
                    printf( "RANDOM MODE:\n" );
                    arrayFieldChar(flagArray, arrayChar, arrayLines, arrayColumns);
                    //arrayOutputInt(flagArray, arrayLines, arrayColumns);
                    arrayOutputChar(arrayChar, arrayLines, arrayColumns);
                    //arrayOutputInt(tempArray, arrayLines, arrayColumns);
                    printf("Живые клетки: %d\n", liveCellsScore);

                    if (liveCellsScore == 0) {
                        liveCellsFlag = 0;
                        printf("Game is over!");
                        free(flagArray[0]);
                        free(flagArray);

                        free(arrayChar[0]);
                        free(arrayChar);

                        free(tempArray[0]);
                        free(tempArray);
                        }
                    }         
                }
            }
        }
    }
}

void initUniverse(int **arrayInt, char **arrayChar,  int arrayColumns, int arrayLines, int *exitFlag) {
    clear();
    printf("CHOUSE YOUR MODE FROM 1 TO 6\n");
    arrayInitInt(arrayInt, arrayLines, arrayColumns, exitFlag);
    arrayFieldInt(arrayInt, arrayLines, arrayColumns);
    arrayInitChar(arrayChar, arrayLines, arrayColumns, exitFlag);
    arrayFieldChar(arrayInt, arrayChar, arrayLines, arrayColumns);
    //arrayOutputInt(arrayInt, arrayLines, arrayColumns);
    arrayOutputChar(arrayChar, arrayLines, arrayColumns);
}

void logic(int **arrayInt, int **arrayTemp, int arrayColumns, int arrayLines, int *liveCellsScore) {
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

            //printf("%d::%d Count = ", i, j);
            //printf("%d\n", count);

            if ((arrayInt[i][j] == LIVECELLS || arrayInt[i][j] == BORNCELLS) && 
            (count == 2 || count == 3)) {
                arrayTemp[i][j] = LIVECELLS;
            } else if ((arrayInt[i][j] == LIVECELLS || arrayInt[i][j] == BORNCELLS) &&
            (count < 2 || count > 3)) {
                arrayTemp[i][j] = DIEDCELLS;
            } else if ((arrayTemp[i][j] == DIEDCELLS) && (count == 3)) {
                arrayTemp[i][j] = BORNCELLS;
            } else if((arrayTemp[i][j] == DIEDCELLS) && (count != 3)) {
                arrayTemp[i][j] = DIEDCELLS;
            }
        }
    }

    for (int i = 1; i < arrayLines - 1; i++) {
        for(int j = 1; j < arrayColumns - 1; j++) {
            arrayInt[i][j] = arrayTemp[i][j];
            if (arrayInt[i][j] == BORNCELLS || arrayInt[i][j] == LIVECELLS) {
                *liveCellsScore += 1;
            }
        }
    }
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   
    while (time(0) < retTime);               
}

void clear() {
    printf("\33c\e[3J");
}
