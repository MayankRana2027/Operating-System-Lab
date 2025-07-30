#include<stdio.h>
#include<unistd.h>
int main() {
    fork();
    fork();
    printf("Process with PID = %d\n", getpid());
}
