#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

int board[9][9];

int main()
{
    resetBoard();
    printBoard();

    Display *display = XOpenDisplay(NULL);

    Window window = XCreateSimpleWindow(
        display, RootWindow(display,0), 0, 0,
        600, 600, 1, BlackPixel(display, 0),
        WhitePixel(display, 0));

    XMapWindow(display, window);

    XSelectInput(display, window, ButtonPressMask);

    XEvent event;
    while (1)
    {
        XNextEvent(display, &event);
        switch  (event.type) {
        case ButtonPress:
            printf("Clicked at %d,%d\n", event.xbutton.x, event.xbutton.y);
            break;
        }
    }
    return 0;
}

void printBoard(){
    for(int i = 0; i < 9; i++){
        if(i % 3 == 0) printf("---------------------------------------\n"); //Add ----- on first and every third row
        for(int j = 0; j < 9; j++){
            if(j % 3 == 0) printf("|"); //Add | on first and every third column
            printf(" %c |", board[i][j] == 0 ? ' ' : board[i][j] + '0'); //If element is 0 print blank space, if not convert integer to char and print it
        }
        printf("\n---------------------------------------\n"); // New row separator
    }
}

void resetBoard(){ //Reseting board so everything is 0
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            board[i][j] = 0;
        }
    }
}

