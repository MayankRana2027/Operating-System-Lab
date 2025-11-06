#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

void bestFit(int process[], int p, int block[], int b) {
    int allocated[p];
    for(int i = 0; i < p; i++) 
        allocated[i] = -1;
        
    int space[b];
    for(int i = 0; i < b; i++)
        space[i] = block[i];
    
    for(int i = 0; i < p; i++) {
        int best = INT_MAX;
        int bestIdx = -1;
        for(int j = 0; j < b; j++) {
            if(space[j] >= process[i] && best > space[j]) {
                best = space[j];
                bestIdx = j;
            }
        }

        if(bestIdx != -1) {
            allocated[i] = bestIdx + 1;
            space[bestIdx] -= process[i];
        }
    }
    
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < p; i++) {
        if(allocated[i] != -1)
            printf("%d\t\t%d\t\t%d\n", i + 1, process[i], allocated[i]);
        else
            printf("%d\t\t%d\tno free block allocated\n", i + 1, process[i]);
    }
    printf("\n");
}

int main() {
    int p;
    printf("Enter the number of process: ");
    scanf("%d", &p);
    int process[p];
    printf("Enter the size of each process: ");
    for(int i = 0; i < p; i++) {
        scanf("%d", &process[i]);
    }

    int b;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &b);
    int block[b];
    printf("Enter the size of each memory block: ");
    for(int i = 0; i < b; i++) {
        scanf("%d", &block[i]);
    }

    bestFit(process, p, block, b);
}