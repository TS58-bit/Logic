#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shell(int* items, int count)
{

    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;

    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}
int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }
int main(void)
{
  /*/
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    clock_t start, end; 

    int i = 0, j = 0, r;
    int n;
    int elem_c;

    static int a[10000][10000];
    static int b[10000][10000];
    static int c[10000][10000];


    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int count = sizeof(sizes) / sizeof(sizes[0]);

   
    srand((unsigned)time(NULL));

    
    for (int s = 0; s < count; s++)
    {
        n = sizes[s];

        i = 0;
        j = 0;

        
        while (i < n)
        {
            j = 0;

            while (j < n)
            {
                a[i][j] = rand() % 100 + 1;
                j++;
            }

            i++;
        }

      
        i = 0;
        j = 0;

        while (i < n)
        {
            j = 0;

            while (j < n)
            {
                b[i][j] = rand() % 100 + 1;
                j++;
            }

            i++;
        }

      
        start = clock();

        
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                elem_c = 0;

                for (r = 0; r < n; r++)
                {
                    elem_c = elem_c + a[i][r] * b[r][j];
                    c[i][j] = elem_c;
                }
            }
        }

        end = clock();

        printf("Matric: %d x %d\n", n, n);
        printf("Time: %.6f sec\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    /*/
    int count = 7590;
    int* items = (int*)malloc(count * sizeof(int));
    int* temp = (int*)malloc(count * sizeof(int));
    double shell_time, qs_time, qsort_time;
    clock_t start, end;
    if (items == NULL || temp == NULL ) {
        printf("Memory allocation error\n");
    }
    printf("Random massiv");
    srand((unsigned)time(NULL));
    for (int i = 0; i < count;i++) {
        items[i] = rand() % 10000;
    }
    for (int i = 0; i < count; i++){
        temp[i] = items[i];
    }
    start = clock();
    shell(temp, count);
    end = clock();
    shell_time = (double)(end - start) / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    qs(temp, 0, count - 1);
    end = clock();
    qs_time = (double)(end - start) / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    qsort(temp, count, sizeof(int),compare);
    end = clock();
    qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nShell_Time %.6f sec", shell_time);
    printf("\nQs_Time %.6f sec", qs_time);
    printf("\nQsort_Time %.6f sec", qsort_time);
    printf("\nUpper Massiv");
    for (int i= 0; i < count;i++) {
        items[i] = i;
    }
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    shell(temp, count);
    end = clock();
    shell_time = (double)(end - start) / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    qs(temp, 0, count - 1);
    end = clock();
    qs_time = (double)(end - start) / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    qsort(temp, count, sizeof(int), compare);
    end = clock();
    qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nShell_Time %.6f sec", shell_time);
    printf("\nQs_Time %.6f sec", qs_time);
    printf("\nQsort_Time %.6f sec", qsort_time);
    printf("\nDown Massiv");
    for (int i = 0; i < count; i++) {
        items[i] = count - i;
    }
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    shell(temp, count);
    end = clock();
    shell_time = (double)(end - start) / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    qs(temp, 0, count - 1);
    end = clock();
    qs_time = (double)(end - start) / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    qsort(temp, count, sizeof(int), compare);
    end = clock();
    qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nShell_Time %.6f sec", shell_time);
    printf("\nQs_Time %.6f sec", qs_time);
    printf("\nQsort_Time %.6f sec", qsort_time);
    printf("\nUPandDowm Massiv");
    for (int i = 0; i < count / 2; i++) {
        items[i] = i;
    }
    for (int i = count / 2; i < count; i++) {
        items[i] = count - i;
    }
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    shell(temp, count);
    end = clock();
    shell_time = (double)(end - start) / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    qs(temp, 0, count - 1);
    end = clock();
    qs_time = (double)(end - start) / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    start = clock();
    qsort(temp, count, sizeof(int), compare);
    end = clock();
    qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nShell_Time %.6f sec", shell_time);
    printf("\nQs_Time %.6f sec", qs_time);
    printf("\nQsort_Time %.6f sec", qsort_time);
    return 0;
}