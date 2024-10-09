#include <stdio.h>
#include <limits.h>

void display(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int findLFU(int frequency[], int last_used[], int n) {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < n; i++) {
        if (frequency[i] < min || (frequency[i] == min && last_used[i] < last_used[index])) {
            min = frequency[i];
            index = i;
        }
    }
    return index;
}

int main() {
    int reference[] = {3, 4, 5, 4, 3, 4, 7, 2, 4, 5, 6, 7, 2, 4, 6};
    int n = sizeof(reference) / sizeof(reference[0]);
    int frames[10], frequency[10], last_used[10], page_faults = 0, m, time = 0;

    printf("Enter number of frames: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        frames[i] = -1;
        frequency[i] = 0;
        last_used[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < m; j++) {
            if (frames[j] == reference[i]) {
                frequency[j]++;
                last_used[j] = ++time;
                found = 1;
                break;
            }
        }

        if (!found) {
            int replace_index = findLFU(frequency, last_used, m);
            frames[replace_index] = reference[i];
            frequency[replace_index] = 1;
            last_used[replace_index] = ++time;
            page_faults++;
        }

        display(frames, m);
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}