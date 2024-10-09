#include <stdio.h>

void display(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int find_LRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int reference[] = {3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2};
    int n = sizeof(reference) / sizeof(reference[0]);
    int frames[10], time[10], page_faults = 0, m, counter = 0;

    printf("Enter number of frames: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < m; j++) {
            if (frames[j] == reference[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }
        }

        if (!found) {
            int pos = find_LRU(time, m);
            frames[pos] = reference[i];
            time[pos] = ++counter;
            page_faults++;
        }

        display(frames, m);
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}