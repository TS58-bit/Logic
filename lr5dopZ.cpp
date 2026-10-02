#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void freeGraph(int** g, int n) {
    if (g == NULL) return;
    for (int i = 0; i < n; i++) {
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

    for (i = 0; i < (*n); i++) {
        g[i] = (int*)malloc((*n) * sizeof(int));
        for (int j = 0; j < (*n); j++) {
            g[i][j] = 0;
        }
    }

    return g;
}

void printGraph(int** g, int n) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return;
    }

    printf("\nГраф (ориентированный, с возможными петлями):\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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

    // Заполняем все элементы независимо:
    // теперь граф ориентированный, и петли g[i][i] тоже могут быть 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = rand() % 2;
        }
    }

    printGraph(g, n);
}

int rcount(int** g, int n) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return 0;
    }

    int r = 0;

    // Для ориентированного графа считаем все единицы,
    // включая петли
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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

    for (int i = 0; i < n; i++) {
        int outdeg = 0; // полустепень исхода
        int indeg = 0;  // полустепень захода

        for (int j = 0; j < n; j++) {
            outdeg += g[i][j];
            indeg += g[j][i];
        }

        printf("Вершина %d: полустепень исхода = %d, полустепень захода = %d",
            i + 1, outdeg, indeg);

        if (outdeg == 0 && indeg == 0) {
            printf(" - изолированная");
        }

        if (n > 1 && outdeg >= n - 1) {
            printf(" - доминирующая");
        }

        if (n > 1 && outdeg == 1 && g[i][i] == 0) {
            printf(" - концевая");
        }

        printf("\n");
    }
}
void printIncidenceMatrix(int** g, int n) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return;
    }

    // Сначала считаем количество рёбер
    int edgeCount = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (g[i][j] == 1) edgeCount++;

    if (edgeCount == 0) {
        printf("Матрица инцидентности: рёбер нет.\n");
        return;
    }

    // Выделяем простой массив рёбер: храним пары (u, v)
    int* eu = (int*)malloc(edgeCount * sizeof(int));
    int* ev = (int*)malloc(edgeCount * sizeof(int));

    int idx = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (g[i][j] == 1) {
                eu[idx] = i;
                ev[idx] = j;
                idx++;
            }

    printf("\nМатрица инцидентности:\n");

    // Заголовки столбцов (номера рёбер)
    printf("     ");
    
    printf("\n");

    for (int i = 0; i < n; i++) {
        
        for (int k = 0; k < edgeCount; k++) {
            int u = eu[k];
            int v = ev[k];

            if (u == i && v == i) {
                // петля: стандартно ставят 2
                printf("%3d ", 2);
            }
            else if (u == i) {
                // исходящее ребро: -1
                printf("%3d ", -1);
            }
            else if (v == i) {
                // входящее ребро: +1
                printf("%3d ", 1);
            }
            else {
                printf("%3d ", 0);


}
        }
        printf("\n");
    }

    free(eu);
    free(ev);
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int m = 0;
    int** inc = NULL;
    int** g = NULL;
    int n = 0, r;
    int choice;

    while (1) {
        printf("\nвыберите действие и введите его номер:\n"
            " 1 - создать граф\n"
            " 2 - задать случайные связи вершин графа\n"
            " 3 - вывести граф\n"
            " 4 - определить размер графа (количество рёбер)\n"
            " 5 - определить типы вершин\n"
            " 6 - выход\n");

        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            if (g != NULL) {
                freeGraph(g, n);
            }
            g = createGraph(&n);
            break;

        case 2:
            randGraph(g, n);
            break;

        case 3:
            printGraph(g, n);
            printIncidenceMatrix(g, n);
            break;
        case 4:
            r = rcount(g, n);
            printf("Количество рёбер: %d\n", r);
            break;

        case 5:
            typevertex(g, n);
            break;

        case 6:
            freeGraph(g, n);
            return 0;

        default:
            printf("Нет такого действия\n");
            break;
        }
    }
}