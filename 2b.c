#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    execlp("ls", "ls", "-l", NULL);
    printf("execlp failed\n");
    return 0;
}
