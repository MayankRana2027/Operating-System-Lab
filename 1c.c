#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 < 0) exit(1);
    if (pid1 == 0) {
        printf("First Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(2);
        exit(0);
    } else {
        wait(NULL);
        pid2 = fork();
        if (pid2 < 0) exit(1);
        if (pid2 == 0) {
            printf("Second Child PID: %d, Parent PID: %d\n", getpid(), getppid());
            sleep(5);
            printf("Second Child after Parent termination, New Parent PID: %d\n", getppid());
            exit(0);
        } else {
            printf("Parent PID: %d, First Child PID: %d, Second Child PID: %d\n", getpid(), pid1, pid2);
            sleep(1);
            exit(0);
        }
    }
    return 0;
}
