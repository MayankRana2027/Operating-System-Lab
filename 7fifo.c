#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

void fifo(int pages[], int p, int f) {
    int frames[f];
    for(int i = 0; i < f; i++) frames[i] = -1;

    int cnt = 0;
    int first = 0;
    for(int i = 0; i < p; i++) {
        // Check for page hit (page is already present)
        bool hit = false;
        for(int j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                hit = true;
                break;
            }
        }
        if(hit) continue;

        cnt++;
        frames[first] = pages[i];
        first = (first + 1) % f;
    }

    printf("Total page faults = %d\n", cnt);
    printf("Total page hits = %d\n", p - cnt);
    printf("Hit Ratio = %.2f\n", (double)(p - cnt)/p);
}

int main() {
    // Taking inputs
    int p;
    printf("Enter the number of pages: ");
    scanf("%d", &p);
    int pages[p];
    printf("Enter the sequence of the pages: "); // Page reference string
    for(int i = 0; i < p; i++) scanf("%d", & pages[i]);
    int f;
    printf("Enter the number of frames: ");
    scanf("%d", &f);

    fifo(pages, p, f);
}