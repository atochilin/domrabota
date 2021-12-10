#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int i, int j, int* arr) {
    int f = arr[i];
    arr[i] = arr[j];
    arr[j] = f;
}

void sort(int first, int last, int* temp, int* array) {
    int center = (int)(first + ((last - first) / 2));
    int a, b;

    a = first;
    b = last;
    do {
        while (temp[a] <= temp[center] && a != center)
            a++;
        while (temp[b] >= temp[center] && b != center)
            b--;
        if (a != center) {
            if (b > center) {
                swap(a, b, temp);
                swap(a, b, array);
            }
            else {
                swap((center - 1), a, temp);
                swap(center, (center - 1), temp);
                swap((center - 1), a, array);
                swap(center, (center - 1), array);
                b = center -= 1;
            }
        }
        else {
            if (b != a) {
                swap((center + 1), b, temp);
                swap(center, (center + 1), temp);
                swap((center + 1), b, array);
                swap(center, (center + 1), array);
                a = center += 1;
            }
        }
    } while (a < b);
    if ((last - first) > 1) {
        sort(first, center, temp, array);
        sort(center, last, temp, array);
    }
}

void main() {
    FILE* file;
    char s;
    int N = 0, left, right;

    file = fopen("g.txt", "r");
    while ((s = getc(file)) != EOF)
        if (s == '\n')
            N++;
    --N;
    fclose(file);

    N *= 2;
    int* array;
    array = (int*)malloc(N * sizeof(int));
    int* temp;
    temp = (int*)malloc(N * sizeof(int));

    file = fopen("g.txt", "r");
    fscanf_s(file, "graph {");
    for (int i = 0; i < N; i += 2) {
        fscanf_s(file, "    %d -- %d;", &left, &right);
        array[i] = left;
        array[i + 1] = right;
    }
    fclose(file);
    sort(0, (N - 1), array, temp);
    int k = 0;
    for (int i = 0; i < N; i++) {
        int j = 1;
        while (array[i] == array[i + 1]) {
            ++i;
            ++j;
        }
        array[k] = array[i];
        temp[k] = j;
        ++k;
    }

    sort(0, (k - 1), temp, array);
    for (int h = 0; h < k; h++)
        for (int i = h + 1; i < k; i++) {
            while (temp[h] == temp[i])
                ++i;
            sort(h, (i - 1), array, temp);
            h = i;
        }
    for (int i = 0; i < k; i++)
        printf("Top %d count is %d\n", array[i], temp[i]);
}