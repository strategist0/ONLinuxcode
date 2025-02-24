#include <stdio.h>
#include <string.h>
int main() {
    int k = 2, m = 4, n = 6;
    int *p1 = &k, *p2 = &m, *p3 = &n;
    *p1 = *p3;
    *p3 = *p1;
    if (p1 == p3)
        p1 = p2;
    printf("p1 = %d p2 = %d p3 = %d\n", *p1, *p2, *p3);
    return 0;
    /*int m = 1, n = 2, *p = &m, *q = &n, *r;
    r = p;
    p = q;
    q = r;
    printf("%d, %d, %d, %d\n", m, n, *p, *q);
    return 0;*/
    /*int i, n[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (i = 0; i < 9; i++)
        n[i] = 9 - i;
    printf("%5d %5d", n[3], n[5]);
    return 0;*/
    /*int i, j = 1, a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (i = 0; i < 4; i++){
        a[i] += i;
        j += a[i] * i;
    }
    printf("%5d\n", j);
    return 0;*/
    /*int i, a[3][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (i = 0; i < 3; i++) {
        printf("%5d", a[i][4 - i]);
    }
    return 0;*/
    /*int i, j, a[3][4] = {{0, 1, 2}, {3, 4, 5, 6}, {7, 8}};
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%5d", a[2-i][j]);
        }
        printf("\n");
    }
    return 0;*/
    /*int i, j, a[][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (i = 0; i < 3; i++)
        for (j = i; j < 4; j++)
            a[i][j] += a[i][j - 1];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%5d", a[i][j]);
        }
        return 0;
    }*/
    /*char s[20];
    scanf("%s", s);
    printf("%s\n", strcat(s, " is a doctor."));
    return 0;*/
    /*char st[16] = "123456\0abcdef";
    printf("%d %d %s\n", strlen(st), sizeof(st), st);
    return 0;*/
    /*char i, s[][5] = {"ab", "1234", "wxyz"};
    for (i = 1; i < 2; i++)
        printf("%s\n", s[i]);
    return 0;*/
    /*int d[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, *p = d;
    printf("%5d %5d\n", *(p + 5), *p + 5);
    return 0;*/
    /*int d[][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int *p[3], j;
    for (j = 0; j < 3; j++)
        p[j] = d[j];
    printf("%5d %5d\n", *(*(p + 2) + 3), *(*(p + 1) + 1));
    return 0;*/
}