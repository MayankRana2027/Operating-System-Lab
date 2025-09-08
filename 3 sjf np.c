#include <stdio.h>

struct Process {
    int id, at, bt, st, ct, tat, wt, done;
};

int main() {
    int n, time = 0, completed = 0, i, min;
    float total_wt = 0, total_tat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done = 0;
    }
    while (completed < n) {
        min = -1;
        for (i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (min == -1 || p[i].bt < p[min].bt) min = i;
            }
        }
        if (min == -1) {
            time++;
        } else {
            p[min].st = time;
            p[min].ct = p[min].st + p[min].bt;
            p[min].tat = p[min].ct - p[min].at;
            p[min].wt = p[min].tat - p[min].bt;
            p[min].done = 1;
            time = p[min].ct;
            completed++;
            total_wt += p[min].wt;
            total_tat += p[min].tat;
        }
    }
    printf("\n========== GANTT CHART ==========\n");
    for (i = 0; i < n; i++) {
        if (i > 0) printf(" | ");
        printf("%d -- P%d -- %d", p[i].st, p[i].id, p[i].ct);
    }
    printf("\n=================================\n");
    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].st, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    return 0;
}
