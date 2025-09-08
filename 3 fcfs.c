#include <stdio.h>

typedef struct {
    int id;        // Process ID
    int at, bt;    // Arrival Time, Burst Time
    int st, ct;    // Start Time, Completion Time
    int tat, wt;   // Turnaround Time, Waiting Time
} Process;

void stable_sort_by_arrival(Process a[], int n) {
    // Sort processes by arrival time (stable)
    for (int i = 1; i < n; i++) {
        Process key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j].at > key.at) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[50];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Process P%d (AT BT): ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Sort by arrival time
    stable_sort_by_arrival(p, n);

    double total_wt = 0, total_tat = 0;
    int time = 0;

    // Calculate timings
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;  // If CPU is idle
        p[i].st = time;
        p[i].ct = p[i].st + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time = p[i].ct;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        
    }

    // Print Gantt Chart
    printf("\n========== GANTT CHART ==========\n");
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" | ");
        printf("%d -- P%d -- %d", p[i].st, p[i].id, p[i].ct);
    }
    printf("\n=================================\n");

    // Print table
    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].st, p[i].ct, p[i].tat, p[i].wt);
    }

    // Print averages
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
