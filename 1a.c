#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Child process\n");
    } else {
        printf("Parent process\n");
    }
    return 0;
}
