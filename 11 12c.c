#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, head, temp, total = 0, disk_size;
    printf("Sample I/O for C-SCAN:\n\nInput:\n");
    printf("Enter number of disk requests : ");
    scanf("%d", &n);

    int req[n + 1];
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("\nEnter initial head position : ");
    scanf("%d", &head);

    printf("Enter total disk size : ");
    scanf("%d", &disk_size);

    req[n] = head;

    // Sorting
    for (i = 0; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (req[i] > req[j]) {
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }

    int pos;
    for (i = 0; i <= n; i++) {
        if (req[i] == head) {
            pos = i;
            break;
        }
    }

    // Move right
    for (i = pos; i < n; i++)
        total += abs(req[i + 1] - req[i]);

    // Jump to beginning (circular)
    total += (disk_size - 1 - req[n]) + (disk_size - 1);

    // Continue from start
    for (i = 0; i < pos; i++)
        total += abs(req[i + 1] - req[i]);

    printf("\nOutput:\nTotal seek movement : %d\n", total);
    return 0;
}
