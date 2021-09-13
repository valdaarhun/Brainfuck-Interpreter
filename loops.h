struct bracketStack {
    char *position;
    struct bracketStack *next, *previous;
};

struct stackHead {
    int size;
    struct bracketStack *front, *back;
};

typedef struct bracketStack BracketStack;
typedef struct stackHead Head;

Head *createStack();
char *gotoEndLoop(char*);