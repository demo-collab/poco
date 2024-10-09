#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int n, int item) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == item)
            return mid;
        if (arr[mid] < item)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <sorted_array> <item_to_search>\n", argv[0]);
        return 1;
    }

    int n = argc - 2;
    int arr[n];
    for (int i = 1; i < argc - 1; i++) {
        arr[i - 1] = atoi(argv[i]);
    }
    
    int item = atoi(argv[argc - 1]);
    int result = binarySearch(arr, n, item);

    if (result != -1) {
        printf("Item %d found at index %d\n", item, result);
    } else {
        printf("Item %d not found in the array\n", item);
    }

    return 0;
}