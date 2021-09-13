#define IN ','
#define OUT '.'
#define START_LOOP '['
#define END_LOOP ']'
#define LEFT '<'
#define RIGHT '>'
#define INC '+'
#define DEC '-'

#define BUFFER_END '\0'

char *buffer;
char tape[30000];

void analyse();
void input(char*);
void output(char*);
void inc(char*);
void dec(char*);
char *left(char*);
char *right(char*);