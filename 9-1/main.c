#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

const int BUFF_SIZE = 8000;

int main(int argc, char** argv) {
    char buff[BUFF_SIZE];
    fgets(buff, sizeof(buff), stdin);
    char expression[BUFF_SIZE];
    strcpy(expression, "print(");
    strcat(expression, buff);
    strcat(expression, ")");
    execlp("python3", "python3", "-c", expression, NULL);
    perror("");
    exit(1);
    return 0;
}
