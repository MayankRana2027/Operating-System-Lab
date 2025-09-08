#include <stdio.h>

struct Process {
    int id, at, bt, st[50], ct, tat, wt, rt, visited;
};

int main() {
    int n, tq = 2, time = 0, completed = 0, i;
    float total_wt = 0, total_tat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].visited = 0;
    }

    int queue[100], front = 0, rear = 0;
    int gcCount = 0;
    struct { int st, id, ct; } gantt[200];

    queue[rear++] = 0;
    int mark[n];
    for (i = 0; i < n; i++) mark[i] = 0;
    mark[0] = 1;

    while (completed < n) {
        int idx = queue[front++];
        if (time < p[idx].at) time = p[idx].at;
        gantt[gcCount].st = time;
        gantt[gcCount].id = p[idx].id;
        if (p[idx].rt <= tq) {
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            completed++;
        } else {
            time += tq;
            p[idx].rt -= tq;
        }
        gantt[gcCount].ct = time;
        gcCount++;

        for (i = 0; i < n; i++) {
            if (!mark[i] && p[i].at <= time && p[i].rt > 0) {
                queue[rear++] = i;
                mark[i] = 1;
            }
        }
        if (p[idx].rt > 0) queue[rear++] = idx;
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
