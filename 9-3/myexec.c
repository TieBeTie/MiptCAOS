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

    int offset =  0x241;
    int N = 5432;

    unsigned char* executable_buff;
    executable_buff = (unsigned char*)mmap(
        0,
        N,
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_PRIVATE | MAP_ANON,
        -1,
        0
    );

    FILE* f = fopen("test", "r");
    for (int i = 0; i < N; ++i ) {
        unsigned char t;
        fread(&t, 1, 1, f);
        executable_buff[i] = t;
    }

    int(*fi)(void) = (int(*)(void))(executable_buff + offset);
    printf("%s\n", executable_buff);
    int result = fi();
    printf("%d\n", result);

    return 0;
}
