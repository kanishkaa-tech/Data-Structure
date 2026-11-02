#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define WIDTH 30
#define HEIGHT 15
int x, y;
int foodX, foodY;
int score;
int gameOver;
int tailX[100], tailY[100];
int tailLength;
enum Direction
{
STOP = 0,
LEFT,
RIGHT,
UP,
DOWN
};
enum Direction dir;
void Setup()
{
x = WIDTH / 2;
y = HEIGHT / 2;
foodX = rand() % WIDTH;
foodY = rand() % HEIGHT;
score = 0;
gameOver = 0;
dir = STOP;
tailLength = 0;
}
void Draw()
{
int i, j, k;
system("cls");
for(i = 0; i < HEIGHT + 2; i++)
{
for(j = 0; j < WIDTH + 2; j++)
{
if(i == 0 || i == HEIGHT + 1 ||
j == 0 || j == WIDTH + 1)
{
printf("#");
}
else if(i == y + 1 && j == x + 1)
{
printf("O");
}
else if(i == foodY + 1 && j == foodX + 1)
{
printf("F");
}
else
{
int print = 0;
for(k = 0; k < tailLength; k++)
{
if(tailX[k] == j - 1 &&
tailY[k] == i - 1)
{
printf("o");
print = 1;
break;
}
}
if(!print)
printf(" ");
}
}
printf("\n");
}
printf("\nScore: %d", score);
printf("\nUse W A S D to move");
printf("\nPress X to exit");
}
void Input()
{
if(kbhit())
{
switch(getch())
{
case 'a':
dir = LEFT;
break;
case 'd':
dir = RIGHT;
break;
case 'w':
dir = UP;
break;
case 's':
dir = DOWN;
break;
case 'x':
gameOver = 1;
break;
}
}
}
void Logic()
{
int i;
int prevX = tailX[0];
int prevY = tailY[0];
int prev2X, prev2Y;
tailX[0] = x;
tailY[0] = y;
for(i = 1; i < tailLength; i++)
{
prev2X = tailX[i];
prev2Y = tailY[i];
tailX[i] = prevX;
tailY[i] = prevY;
prevX = prev2X;
prevY = prev2Y;
}
switch(dir)
{
case LEFT:
x--;
break;
case RIGHT:
x++;
break;
case UP:
y--;
break;
case DOWN:
y++;
break;
default:
break;
}
if(x < 0 || x >= WIDTH ||
y < 0 || y >= HEIGHT)
{
gameOver = 1;
}
for(i = 0; i < tailLength; i++)
{
if(tailX[i] == x && tailY[i] == y)
gameOver = 1;
}
if(x == foodX && y == foodY)
{
score += 10;
tailLength++;
foodX = rand() % WIDTH;
foodY = rand() % HEIGHT;
}
}
int main()
{
Setup();
while(!gameOver)
{
Draw();
Input();
Logic();
Sleep(150);
}
printf("\n\nGAME OVER!");
printf("\nFinal Score: %d", score);
getch();
return 0;
}
