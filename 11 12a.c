#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, total = 0;
    printf("--- FCFS Disk Scheduling ---\n");
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int request[n];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nHead Movement Sequence: %d", head);
    for (int i = 0; i < n; i++) {
        total += abs(request[i] - head);
        head = request[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement: %d\n", total);
    printf("Average Seek Time: %.2f\n", (float)total / n);
    return 0;
}
