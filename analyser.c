#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "analyser.h"
#include "loops.h"

void input(char *ptr) {
    if (ptr < tape || ptr - tape >= 30000) {
        printf("Segmentation fault\nTried to store input beyond memory bounds\n");
        // printf("Check: %d\n", ptr - buffer);
        exit(-1);
    }
    scanf("%c", ptr);
}

void output(char *ptr) {
    if (ptr < tape || ptr - tape >= 30000) {
        printf("Segmentation fault\nTried to ouput contents of inaccessible memory location\n");
        // printf("Check: %d\n", ptr - buffer);
        exit(-1);
    }
    printf("%c", *ptr);
}

void inc(char *ptr) {
    if (ptr < tape || ptr - tape >= 30000) {
        printf("Segmentation fault\nTried to modify memory location out of bounds\n");
        // printf("Check: %d\n", ptr - buffer);
        exit(-1);
    }
    (*ptr)++;
}

void dec(char *ptr) {
    if (ptr < tape || ptr - tape >= 30000) {
        printf("Segmentation fault\nTried to modify memory location out of bounds\n");
        // printf("Check: %d\n", ptr - tape);
        exit(-1);
    }
    (*ptr)--;
    //printf("\n%d\n", *ptr);
}

char *left(char *ptr) {
    return --ptr;
}

char *right(char *ptr) {
    return ++ptr;
}

void analyse() {
    char *pc = buffer, *ptr = tape;
    bool inLoop = true;
    int bracketDegree = 0, bracketCount = 0;
    Head *stack = createStack();

    while (*pc != BUFFER_END) {
        // printf("%c", *pc);
        switch (*pc) {
        case IN:
            input(ptr);
            break;
        case OUT:
            output(ptr);
            break;
        case INC:
            inc(ptr);
            break;
        case DEC:
            dec(ptr);
            break;
        case LEFT:
            ptr = left(ptr);
            break;
        case RIGHT:
            ptr = right(ptr);
            break;
        case START_LOOP:
        // printf("\n%d\n", *ptr);
            if (*ptr != 0 && (stack -> back == NULL || stack -> back -> position != pc)) {
                BracketStack *bracket = (BracketStack*)malloc(sizeof(BracketStack));
                bracket -> position = pc;
                bracket -> next = NULL;
                if (stack -> front == NULL) {
                    bracket -> previous = NULL;
                    stack -> front = bracket;
                }
                else {
                    bracket -> previous = stack -> back;
                    stack -> back -> next = bracket;
                }
                stack -> size++;
                stack -> back = bracket;
            } else if (*ptr == 0)
                pc = gotoEndLoop(++pc);
            break;
        case END_LOOP:
            pc = stack -> back -> position;
            --pc;
            if (*ptr == 0) {
                BracketStack *bracket = stack -> back;
                stack -> size--;
                stack -> back = bracket -> previous;
                if (stack -> back != NULL)
                    stack -> back -> next = NULL;
                else
                    stack -> front = NULL;
                free(bracket);
            }
            break;
        }
        ++pc;
    }
    printf("\n");
}