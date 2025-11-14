#include <stdio.h>
#include <string.h>

struct File {
    char name[20];
    int nBlocks;
    int blocks[20];
};

int main() {
    struct File f[10];
    int n;

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter file %d name: ", i + 1);
        scanf("%s", f[i].name);
        printf("Enter number of blocks in file %d: ", i + 1);
        scanf("%d", &f[i].nBlocks);
        printf("Enter block numbers for file %s: ", f[i].name);
        for (int j = 0; j < f[i].nBlocks; j++)
            scanf("%d", &f[i].blocks[j]);
    }

    printf("\n%-10s%-15s%-20s\n", "File Name", "No. of blocks", "Blocks occupied");
    for (int i = 0; i < n; i++) {
        printf("%-10s%-15d", f[i].name, f[i].nBlocks);
        for (int j = 0; j < f[i].nBlocks; j++)
            printf("%d ", f[i].blocks[j]);
        printf("\n");
    }

    return 0;
}
