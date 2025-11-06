#include<stdio.h> // Using time counter
#include<stdbool.h>
#include<limits.h>

// Returns the index of the frame where LRU page is present
int getLRU(int f, int time[]) {
    int min = time[0];
    int lru = 0;
    for(int i = 1; i < f; i++) {
        if(min > time[i]) {
            min = time[i];
            lru = i;
        }
    }
    return lru;
}

void lru(int pages[], int p, int f) {
    int frames[f];
    int time[f]; // Stores last accessed time of each frame
    for(int i = 0; i < f; i++) {
        time[i] = 0;
        frames[i] = -1;
    }
    
    int pf = 0; // Counter for the page faults
    int t = 0; // Current time

    for(int i = 0; i < p; i++) {
        // Check for page hit (page is already present)
        bool hit = false;
        for(int j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                time[j] = ++t;
                hit = true;
                break;
            }
        }
        if(hit) continue;
        
        pf++;
        
        // Check for availablity of frames
        bool frameAvailable = false;
        for(int j = 0; j < f; j++) {
            if(frames[j] == -1) {
                frames[j] = pages[i];
                time[j] = ++t;
                frameAvailable = true;
                break;
            }
        }
        if(frameAvailable) continue;
        
        int lru = getLRU(f, time);
        frames[lru] = pages[i];
        time[lru] = ++t;
    }
    
    printf("Total page faults = %d\n", pf);
    printf("Total page hits = %d\n", p - pf);
    printf("Hit Ratio = %.2f\n", (double)(p - pf)/p);
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

    lru(pages, p, f);
}