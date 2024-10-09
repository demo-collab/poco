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

int find_MFU(int frequency[], int n) {
    int max = frequency[0], index = 0;
    for (int i = 1; i < n; i++) {
        if (frequency[i] > max) {
            max = frequency[i];
            index = i;
        }
    }
    return index;
}

int main() {
    int reference[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2};
    int n = sizeof(reference) / sizeof(reference[0]);
    int frames[10], frequency[10], page_faults = 0, m, time = 0;

    printf("Enter number of frames: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        frames[i] = -1;
        frequency[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < m; j++) {
            if (frames[j] == reference[i]) {
                frequency[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int replace_index = find_MFU(frequency, m);
            frames[replace_index] = reference[i];
            frequency[replace_index] = 1;
            page_faults++;
        }

        display(frames, m);
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}