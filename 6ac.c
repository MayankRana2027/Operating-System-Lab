#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str;
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        str = (char*) shmat(shmid, NULL, 0);
        strcpy(str, "Hello from Child!");
        shmdt(str);
    } else {          // Parent process
        sleep(1); // ensure child writes first
        str = (char*) shmat(shmid, NULL, 0);
        printf("Parent received: %s\n", str);
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
