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

int find_MRU(int frames[], int m, int time[], int current_time) {
    int mru_index = 0, max_time = -1;

    for (int i = 0; i < m; i++) {
        if (time[i] > max_time) {
            max_time = time[i];
            mru_index = i;
        }
    }

    return mru_index;
}

int main() {
    int reference[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2};
    int n = sizeof(reference) / sizeof(reference[0]);
    int frames[10], time[10], page_faults = 0, m;

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
                time[j] = i; // Update the time of use
                break;
            }
        }

        if (!found) {
            int pos = find_MRU(frames, m, time, i);
            frames[pos] = reference[i];
            time[pos] = i;
            page_faults++;
        }

        display(frames, m);
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}