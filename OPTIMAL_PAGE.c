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

int find_optimal(int frames[], int m, int reference[], int ref_index, int n) {
    int farthest = ref_index, pos = -1;

    for (int i = 0; i < m; i++) {
        int j;
        for (j = ref_index; j < n; j++) {
            if (frames[i] == reference[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }

        if (j == n) {
            return i; // This frame is not referenced again
        }
    }

    return (pos == -1) ? 0 : pos; // If all frames are referenced, replace the farthest one
}

int main() {
    int reference[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2};
    int n = sizeof(reference) / sizeof(reference[0]);
    int frames[10], page_faults = 0, m;

    printf("Enter number of frames: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < m; j++) {
            if (frames[j] == reference[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = find_optimal(frames, m, reference, i + 1, n);
            frames[pos] = reference[i];
            page_faults++;
        }

        display(frames, m);
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}