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

void print_version()
{
    printf("scaffold - Tiny Crass-Platform Build System\n");
    printf("Version: 1.0.0\n");
    printf("Author: mohammad mehdi sharife\n");
    printf("License: GPLv3\n");
    printf("GitHub: https://github.com/mohammadmehdisharife/scaffold\n");
    exit(0);
}

void print_help()
{
    printf("Usage: scaffold <target> [options]\n");
    printf("       scaffold --help\n");
    printf("       scaffold --version\n\n");
    printf("Options:\n");
    printf("  <target>    Target to execute from scaffold file\n");
    printf("  --help      Show this help message\n");
    printf("  --version   Show version information\n\n");
    printf("Examples:\n");
    printf("  scaffold build\n");
    printf("  scaffold clean\n");
    printf("  scaffold --version\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        print_error("Usage: scaffold <target>");
    }

    if (strcmp(argv[1], "--version") == 0) {
        print_version();
        exit(0);
    }

    if (strcmp(argv[1], "--help") == 0) {
        print_help();
        exit(0);
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
