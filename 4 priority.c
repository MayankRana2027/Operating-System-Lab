#include <stdio.h>

struct Process {
    int id, at, bt, pr, st, ct, tat, wt, done;
};

int main() {
    int n, time = 0, completed = 0, i, max;
    float total_wt = 0, total_tat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time, burst time and priority of process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].done = 0;
    }
    while (completed < n) {
        max = -1;
        for (i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (max == -1 || p[i].pr > p[max].pr) max = i;
            }
        }
        if (max == -1) {
            time++;
        } else {
            p[max].st = time;
            p[max].ct = p[max].st + p[max].bt;
            p[max].tat = p[max].ct - p[max].at;
            p[max].wt = p[max].tat - p[max].bt;
            p[max].done = 1;
            time = p[max].ct;
            completed++;
            total_wt += p[max].wt;
            total_tat += p[max].tat;
        }
    }
    printf("\n========== GANTT CHART ==========\n");
    for (i = 0; i < n; i++) {
        if (i > 0) printf(" | ");
        printf("%d -- P%d -- %d", p[i].st, p[i].id, p[i].ct);
    }
    printf("\n=================================\n");

    printf("\nProcess\tAT\tBT\tPR\tST\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr,
               p[i].st, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    return 0;
}
