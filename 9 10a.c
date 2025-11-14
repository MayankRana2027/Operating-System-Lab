#include <stdio.h>
#include <string.h>

struct File {
    char name[20];
    int start, length;
};

int main() {
    struct File f[10];
    int n;

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter file %d name: ", i + 1);
        scanf("%s", f[i].name);
        printf("Enter starting block of file %d: ", i + 1);
        scanf("%d", &f[i].start);
        printf("Enter number of blocks in file %d: ", i + 1);
        scanf("%d", &f[i].length);
    }

    printf("\n%-10s%-15s%-15s%-20s\n", "File Name", "Start block", "No. of blocks", "Blocks occupied");
    for (int i = 0; i < n; i++) {
        printf("%-10s%-15d%-15d", f[i].name, f[i].start, f[i].length);
        for (int j = 0; j < f[i].length; j++) {
            printf("%d ", f[i].start + j);
        }
        printf("\n");
    }

    return 0;
}
