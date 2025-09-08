#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main() {
    DIR *d;
    struct dirent *de;
    d = opendir(".");
    if (d == NULL) {
        printf("Cannot open directory\n");
        exit(1);
    }
    while ((de = readdir(d)) != NULL) {
        printf("%s\n", de->d_name);
    }
    closedir(d);
    return 0;
}
