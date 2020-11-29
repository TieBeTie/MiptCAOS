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

const int BUFF_SIZE = 12064;

int main(int argc, char** argv) {

    char* buff = "#include<stdio.h>\n int main() { printf(\"%d\", 2 + 2 + 5); }";
    char expression[BUFF_SIZE];

    void *executable_buff;
    executable_buff = mmap(
        0,
        64000,
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_SHARED | MAP_ANON,
        -1,
        0
    );

    int code_file = open("source.c", O_WRONLY | O_CREAT, 0640);
    write(code_file, buff, strlen(buff));
    close(code_file);

    int pid = fork();

    if (pid == 0) {
        execlp("gcc", "gcc", "-o", "out", "source.c", NULL);
    } else {

        int status;
        wait(&status);
        freopen("out", "r");
        fgets(executable_buff, 64000, stdin);
        printf("%s\n", (char*)executable_buff);
        //int i = ((int (*) (void))executable_buff)();
    }


    return 0;
}
