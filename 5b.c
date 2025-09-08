#include <stdio.h>

int main() {
    int p, r;
    printf("Enter number of processes : ");
    scanf("%d", &p);
    printf("Enter number of resources : ");
    scanf("%d", &r);

    int max[p][r], alloc[p][r], need[p][r], avail[r], total[r];

    printf("Enter maximum requirement :\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter allocated matrix :\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Resource Vector : ");
    for (int i = 0; i < r; i++)
        scanf("%d", &total[i]);

    for (int j = 0; j < r; j++) {
        int sum = 0;
        for (int i = 0; i < p; i++) sum += alloc[i][j];
        avail[j] = total[j] - sum;
    }

    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int finish[p];
    for (int i = 0; i < p; i++) finish[i] = 0;

    int count = 0;
    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < r; j++)
                    if (need[i][j] > avail[j]) break;
                if (j == r) {
                    for (int k = 0; k < r; k++) avail[k] += alloc[i][k];
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    int deadlock = 0;
    for (int i = 0; i < p; i++) {
        if (!finish[i]) {
            deadlock = 1;
            break;
        }
    }

    if (deadlock)
        printf("Deadlock detected\n");
    else
        printf("No deadlock\n");

    return 0;
}
