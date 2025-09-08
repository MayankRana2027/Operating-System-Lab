#include <stdio.h>

struct Process {
    int id, at, bt, st, ct, tat, wt, rt, done;
};

int main() {
    int n, time = 0, completed = 0, i, min, firstExec;
    float total_wt = 0, total_tat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].done = 0;
    }

    int prev = -1, gcCount = 0;
    struct { int st, id, ct; } gantt[100];

    while (completed < n) {
        min = -1;
        for (i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (min == -1 || p[i].rt < p[min].rt) min = i;
            }
        }
        if (min == -1) {
            time++;
        } else {
            if (prev != min) {
                gantt[gcCount].st = time;
                gantt[gcCount].id = p[min].id;
                prev = min;
            }
            p[min].rt--;
            time++;
            if (p[min].rt == 0) {
                p[min].ct = time;
                p[min].tat = p[min].ct - p[min].at;
                p[min].wt = p[min].tat - p[min].bt;
                total_wt += p[min].wt;
                total_tat += p[min].tat;
                p[min].done = 1;
                completed++;
            }
            gantt[gcCount].ct = time;
            if (gantt[gcCount].ct == time && (completed == n || prev != min)) gcCount++;
        }
    }

    printf("\n========== GANTT CHART ==========\n");
    for (i = 0; i < gcCount; i++) {
        if (i > 0) printf(" | ");
        printf("%d -- P%d -- %d", gantt[i].st, gantt[i].id, gantt[i].ct);
    }
    printf("\n=================================\n");

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    return 0;
}
