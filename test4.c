#include <stdio.h>

int minimumSum(int n, int k) {
    int num[51];
    int res = 0;
    for (int i = 0; i < 51; i++) {
        num[i] = i;
    }
    for (int i = 1; i < k / 2; i++) {
        num[k - i] = 0;
    }
    if (n < 51) {
        for (int i = 0, j = 0; j < n; i++) {
            if (num[i] != 0) {
                res += num[i];
                j++;
            }
        }
    } else {
        for (int i = 0, j = 0; j < 51; i++) {
            if (num[i] != 0) {
                res += num[i];
                j++;
            }
        }
        for (int i = 51, j = 51; j <= n; i++) {
            if (num[i] != 0) {
                res += num[i];
                j++;
            }
        }
    }
    return res;
}

int main() {
    int n = 5, k = 4, res;
    res = minimumSum(n, k);
    printf("%d\n", res);
    return 0;
}