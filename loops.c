#include <stdlib.h>

#include "loops.h"
#include "analyser.h"

Head *createStack() {
    Head *stack = (Head*)malloc(sizeof(Head));
    stack -> size = 0;
    stack -> front = NULL;
    stack -> back = NULL;
    return stack;
}

char *gotoEndLoop(char *pc) {
    int bracketWeight = 0;
    while (*pc != BUFFER_END) {
        // printf("\n%c\n", *pc);
        if (*pc == END_LOOP && bracketWeight == 0)
            break;
        else if (*pc == START_LOOP)
            bracketWeight++;
        else if (*pc == END_LOOP && bracketWeight != 0)
            bracketWeight--;
        ++pc;
    }
    return pc;
}