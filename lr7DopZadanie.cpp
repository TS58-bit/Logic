#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void freeGraph(int** g, int n) {
    for (int i = 0; i < n; i++){
        free(g[i]);
    }
    free(g);    
}
int** createGraph(int* n) {
    int** g;
    int i;
    printf("Введите количество вершин графа ");
    do {
        scanf_s("%d", n);
        if ((*n) <= 0) {
            printf("введите положительное ненулевое число! ");
        }
    } while ((*n) <= 0);

    g = (int**)malloc((*n) * sizeof(int*));

    for (i = 0; i < (*n); i++){
        g[i] = (int*)malloc((*n) * sizeof(int));
    }

    return g;
}

void printGraph(int** g, int n){
    int i, j;

    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return;
    }

    printf("\nГраф: \n");

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("%d ", g[i][j]);
        }

        printf("\n");
    }
}

void randGraph(int** g, int n) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        g[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            g[i][j] = rand() % 2;
        }
    }
    printGraph(g, n);
}

int rcount(int** g, int n){
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return 0;
    }

    int r = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (g[i][j] == 1) {
                r++;
            }
        }
    }
    return r;
}

void typevertex(int** g, int n) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return;
    }
    int t1 = 0;
    int t2 = 0;
    for (int i = 0; i < n; i++) {
        t1 = 0;
        t2 = 0;
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 1) t1++;
            if (g[j][i] == 1) t2++;
        }
        if (t1 == n - 1 && t2 == n - 1) {
            printf("Вершина %d - доминирующая\n", i+1);
        }
        if (t1 == 1 && t2 == 1) {
            printf("Вершина %d - концевая\n", i+1);
        }

        if (t1 == 0 && t2 == 0) {
            printf("Вершина %d - изолированная\n", i+1);
        }
    }
}

int main(){
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int** g = NULL;
    int n, r;
    int choice;
    while (1) {
        printf("\nвыберите действие и введите его номер:\n 1 - создать граф\n 2 - задать случайные связи вершин графа\n 3 - вывести граф\n 4 - определить размер графа(количество рёбер)\n 5 - определить типы вершин\n");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1: g = createGraph(&n); break;
        case 2: randGraph(g, n); break;
        case 3: printGraph(g, n); break;
        case 4: r = rcount(g, n); printf("%d", r); break;
        case 5: typevertex(g, n); break;
        case 6: freeGraph(g, n); return 0;
        default: break;
        }
    }
}

