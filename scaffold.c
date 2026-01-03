#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN 1
#define OUT 0

void print_error(char *msg)
{
    printf("\e[0;31mERROR: %s\e[0m\n", msg);
    exit(1);
}

void execute_command(char *command)
{
    system(command);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        print_error("Usage: scaffold <target>");
    }

    char *target = argv[1];
    FILE *file = fopen("scaffold", "r");
    if (file == NULL) {
        print_error("scaffold file not found");
    }

    char line[256];
    int state = OUT;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        
        if (strlen(line) == 0) continue;

        if (state == OUT) {
            if (strstr(line, target) && strstr(line, ":")) {
                state = IN;
                printf("Found target: %s\n", target);
            }
        } else {
            if (line[0] == '\t' || line[0] == ' ') {
                execute_command(line);
            } else {
                state = OUT;
            }
        }
    }
    
    fclose(file);
    return 0;
}
