#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <elf.h>

const int EXPR_SIZE = 12064;

int main(int argc, char** argv) {

    char* left = "#include<stdio.h>\n #include<math.h>\n int main() { printf(\"%d\",(";
    char* right = ")); }";
    char* buff = (char*)malloc(sizeof(char) * 32000);
    char expression[EXPR_SIZE];
    fgets(expression, sizeof(expression), stdin);
    if (
        strlen(expression) == 0 ||
        (strlen(expression) == 1 && expression[0] == '\n')
    ) {
        return 0;
    }
    strcpy(buff, left);
    strcat(buff, expression);
    strcat(buff, right);

    int code_file = open("source.c", O_WRONLY | O_CREAT, 0640);
    write(code_file, buff, strlen(buff));
    close(code_file);

    int pid = fork();

    if (pid == 0) {
        execlp("gcc", "gcc", "-o", "out", "source.c", NULL);
    } else {

        int status;
        wait(&status);
        if (fork() == 0) {
            execl("./out", "./out", NULL);
        } else {
            int status2;
            wait(&status2);
            unlink("source.c");
            unlink("out");
            free(buff);
        }
    }

    return 0;
}
