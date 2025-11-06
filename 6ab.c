#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    struct msg_buffer message;
    key_t key;
    int msgid;
    pid_t pid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1) {
        printf("msgget failed\n");
        return 1;
    }

    pid = fork();

    if (pid == 0) {  // Child process
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from Child!");
        msgsnd(msgid, &message, sizeof(message), 0);
    } else {          // Parent process
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("Parent received: %s\n", message.msg_text);
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
