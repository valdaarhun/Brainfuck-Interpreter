#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "analyser.h"

static bool checkChar(char c) {
    switch (c) {
    case OUT:
    case IN:
    case INC:
    case DEC:
    case LEFT:
    case RIGHT:
    case START_LOOP:
    case END_LOOP:
        return true;
    default:
        return false;
    }
}

static void readFile(FILE *f) {
    int index = 0;
    char c;
    while((c = fgetc(f)) != EOF) {
        if (checkChar(c))
            buffer[index++] = c;
    }
    buffer[index] = BUFFER_END;
}

static int findLength(FILE *f){
    char c;
    int progLength = 0;
    while ((c = fgetc(f)) != EOF) {
        if (checkChar(c))
            progLength++;
    }
    return progLength;
}

// TODO: error handling
int main(int argc, char *argv[]) {
    if (argc == 1 || argc > 3) {
        printf("USAGE:\n./bfpret [filename | -c cmd]\n");
        return -1;
    } else if (argc == 2) {
        if (!strcmp(argv[1], "-c")) {
            printf("No program found\n");
            return -1;
        }
        if (argv[1][0] == '-') {
            printf("Invalid flag\n");
            return -1;
        }
        FILE *f = fopen(argv[1], "r");
        if (f == NULL) {
            printf("Error in opening/reading file. Check if file exists.\n");
            return -1;
        }
        int progLength = findLength(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char *)malloc(sizeof(char) * (progLength + 1));
        readFile(f);
        fclose(f);
    } else if (argc == 3) {
        if (strcmp(argv[1], "-c")) {
            printf("Unknown flag \"%s\"\n", argv[1]);
            return -1;
        }
        char *program = argv[2];
        int length = 0;
        for(int i = 0 ; program[i] != '\0' ; i++) {
            if (checkChar(program[i]))
                length++;
        }
        buffer = (char*)malloc(sizeof(char) * (length + 1));
        int pc = 0;
        for(int i = 0 ; program[i] != '\0' ; i++) {
            if (checkChar(program[i]))
                buffer[pc++] = program[i];
        }
        buffer[pc] = '\0';
    }
    
    // printf("%s\n\n", buffer);
    analyse();

    free(buffer);
}
