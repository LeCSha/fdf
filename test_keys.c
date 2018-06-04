#include <stdio.h>
#include <curses.h>

// #inclde <conio.h>

int main()
{
int c;
// clrscr();
while ((c = getchar()) != '\n')
    printf("%d",c);
getch();
}