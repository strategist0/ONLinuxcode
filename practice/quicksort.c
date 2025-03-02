void quicksort(int arr[], int left, int right) {
    if (left >= right)
        return;

    int pivot = arr[left];
    int i = left, j = right;

    while (i < j) {
        while (i < j && arr[j] >= pivot)
            j--;
        if (i < j)
            arr[i++] = arr[j];

        while (i < j && arr[i] <= pivot)
            i++;
        if (i < j)
            arr[j--] = arr[i];
    }

    arr[i] = pivot;

    quicksort(arr, left, i - 1);
    quicksort(arr, i + 1, right);
}