#include <stdio.h>
#include <stdlib.h>
#include <conio.h>   // For getch() and kbhit() (Windows)
#include <windows.h> // For Sleep()

#define WIDTH 40
#define HEIGHT 20

int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailLength;
char direction;

void setup() {
    gameOver = 0;
    direction = ' ';
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
}

void draw() {
    system("cls"); // Clear screen

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            if (j == 0) printf("#");

            if (i == y && j == x)
                printf("O"); // Snake head
            else if (i == fruitY && j == fruitX)
                printf("F"); // Fruit
            else {
                int printTail = 0;
                for (int k = 0; k < tailLength; k++)
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        printTail = 1;
                    }

                if (!printTail) printf(" ");
            }

            if (j == WIDTH - 1) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': direction = 'U'; break;
            case 's': direction = 'D'; break;
            case 'a': direction = 'L'; break;
            case 'd': direction = 'R'; break;
            case 'x': gameOver = 1; break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case 'U': y--; break;
        case 'D': y++; break;
        case 'L': x--; break;
        case 'R': x++; break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;

    for (int i = 0; i < tailLength; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        tailLength++;
    }
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(80); // Speed control
    }

    printf("\nGAME OVER! Final Score = %d\n", score);
    return 0;
}
