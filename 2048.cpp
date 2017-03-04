/*******************************/
/*      2048                   */
/*      Author: Yu Lin         */
/*******************************/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <conio.h>

using namespace std;

//  utility struct
struct Loc {
    int x;
    int y;
    Loc(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

int grid[4][4];
int nextNum;
int nextLocIndex;
vector<Loc> emptyLocations;

int row = 4;
int col = 4;

// debug function
void debug() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%5d ", grid[i][j]);
        }
        printf("\n");
    }
}

int getScore() {
    int score = 0;
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            if (score < grid[r][c])
                score = grid[r][c];
        }
    }
    return score;
}

// print game UI
//   Score:  8
//    ----- ----- ----- -----
//   |    4|    2|     |     |
//    ----- ----- ----- -----
//   |    8|     |     |     |
//    ----- ----- ----- -----
//   |     |     |     |     |
//    ----- ----- ----- -----
//   |     |     |     |     |
//    ----- ----- ----- -----
//
void printUI() {
    printf("Score: %5d\n", getScore());
    for (int i = 0; i < row; ++i) {
        printf(" ----- ----- ----- ----- \n");
        printf("|");
        for (int j = 0; j < col; ++j) {
            if (grid[i][j] == 0) {
                printf("     |");
            }
            else {
                printf("%5d|", grid[i][j]);
            }
        }
        printf("\n");
    }
    printf(" ------ ----- ---- -----\n");
}

void pressKeyW() {
    for (int c = 0; c < col; ++c) {
        for (int r = 1; r < row; ++r) {
            int t = r - 1;
            if (grid[r][c] != 0) {
                while (t >= 0 && grid[t][c] == 0) t--;
                if (t + 1 != r) {
                    grid[t + 1][c] = grid[r][c];
                    grid[r][c] = 0;
                }
            }
        }
    }
    
    for (int c = 0; c < col; ++c) {
        for (int r = 1; r < row; ++r) {
            if (grid[r - 1][c] != 0 && grid[r - 1][c] == grid[r][c]) {
                grid[r - 1][c] *= 2;
                grid[r][c] = 0;
            }
            else if (grid[r - 1][c] == 0 && grid[r][c] != 0) {
                grid[r - 1][c] += grid[r][c];
                grid[r][c] = 0;
            }
        }
    }
}

void pressKeyS() {
    for (int c = 0; c < col; ++c) {
        for (int r = row - 2; r >= 0; --r) {
            int t = r + 1;
            if (grid[r][c] != 0) {
                while (t <= row - 1 && grid[t][c] == 0) t++;
                if (t - 1 != r) {
                    grid[t - 1][c] = grid[r][c];
                    grid[r][c] = 0;
                }
            }
        }
    }
    
    for (int c = 0; c < col; ++c) {
        for (int r = row - 2; r >= 0; --r) {
            if (grid[r + 1][c] != 0 && grid[r + 1][c] == grid[r][c]) {
                grid[r + 1][c] *= 2;
                grid[r][c] = 0;
            }
            else if (grid[r + 1][c] == 0 && grid[r][c] != 0) {
                grid[r + 1][c] += grid[r][c];
                grid[r][c] = 0;
            }
        }
    }
}

void pressKeyA() {
    for (int r = 0; r < row; ++r) {
        for (int c = 1; c < col; ++c) {
            int t = c - 1;
            if (grid[r][c] != 0) {
                while (t >= 0 && grid[r][t] == 0) t--;
                if (t + 1 != c) {
                    grid[r][t + 1] = grid[r][c];
                    grid[r][c] = 0;
                }
            }
        }
    }
    
    for (int r = 0; r < row; ++r) {
        for (int c = 1; c < col; ++c) {
            if (grid[r][c - 1] != 0 && grid[r][c - 1] == grid[r][c]) {
                grid[r][c - 1] *= 2;
                grid[r][c] = 0;
            }
            else if (grid[r][c - 1] == 0 && grid[r][c] != 0) {
                grid[r][c - 1] += grid[r][c];
                grid[r][c] = 0;
            }
        }
    }
}

void pressKeyD() {
    for (int r = 0; r < row; ++r) {
        for (int c = col - 2; c >= 0; --c) {
            int t = c + 1;
            if (grid[r][c] != 0) {
                while (t <= col - 1 && grid[r][t] == 0) t++;
                if (t - 1 != c) {
                    grid[r][t - 1] = grid[r][c];
                    grid[r][c] = 0;
                }
            }
        }
    }
    
    for (int r = 0; r < row; ++r) {
        for (int c = col - 2; c >= 0; --c) {
            if (grid[r][c + 1] != 0 && grid[r][c + 1] == grid[r][c]) {
                grid[r][c + 1] *= 2;
                grid[r][c] = 0;
            }
            else if (grid[r][c + 1] == 0 && grid[r][c] != 0) {
                grid[r][c + 1] += grid[r][c];
                grid[r][c] = 0;
            }
        }
    }
}

void showLose() {
    printf("You lose!\n");
    printf("please press [enter] to restart!\n");
}

void move(char c) {
    switch (c) {
        case 'a':
        case 'A':
            pressKeyA();
            break;
        case 'w':
        case 'W':
            pressKeyW();
            break;
        case 's':
        case 'S':
            pressKeyS();
            break;
        case 'd':
        case 'D':
            pressKeyD();
            break;
        default:
            return;
    }
}

//  collect empty locations
void getEmptyLocations() {
    emptyLocations.clear();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (grid[i][j] == 0) {
                emptyLocations.push_back(Loc(i, j));
            }
        }
    }
}

// put 2 or 4 in the grid in a random empty location
void putNumber() {
    if (emptyLocations.empty()) {
        return;
    }
    nextLocIndex = rand() % emptyLocations.size();
    int x = emptyLocations[nextLocIndex].x;
    int y = emptyLocations[nextLocIndex].y;
    if (rand() % 2 == 1) {
        grid[x][y] = 4;
    }
    else {
        grid[x][y] = 2;
    }
}

//  initialize the game
//  put two numbers in the grid
void init() {
    getEmptyLocations();
    putNumber();
    getEmptyLocations();
    putNumber();
}

void restart() {
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            grid[r][c] = 0;
        }
    }
    init();
}

bool isLose() {
    //  if there are empty locations
    if (!emptyLocations.empty()) {
        return false;
    }
    //  check rows
    for (int r = 0; r < row; ++r) {
        for (int c = 1; c < col; ++c) {
            if (grid[r][c - 1] == grid[r][c]) {
                return false;
            }
        }
    }
    //  check columns
    for (int c = 0; c < col; ++c) {
        for (int r = 1; r < row; ++r) {
            if (grid[r - 1][c] == grid[r][c]) {
                return false;
            }
        }
    }
    return true;
}

void loop() {
    char key;
    while (1) {
        system("cls");//  windows only
        //  linux should use
        //  system("clear");
        printUI();
        key = getch();
        if (key != 'a' && key != 's' && key != 'd' && key != 'w' &&
            key != 'A' && key != 'S' && key != 'D' && key != 'W')
            continue;
        move(key);
        getEmptyLocations();
        putNumber();
        if (isLose()) {
            showLose();
            char c = getchar();
            restart();
        }
    }
}

int main() {
    srand(time(0));
    init();
    loop();
    system("pause");
    return 0;
}











