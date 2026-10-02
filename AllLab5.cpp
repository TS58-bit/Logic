#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// ============================================================
// Вариант 1: Неориентированный простой граф (из lr5.cpp)
// ============================================================
namespace UndirectedSimple {

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
        }
        return g;
    }

    void printGraph(int** g, int n) {
        int i, j;
        if (g == NULL) {
            printf("Граф ещё не был создан\n");
            return;
        }
        printf("\nГраф: \n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
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
            for (int j = i + 1; j < n; j++) {
                g[i][j] = rand() % 2;
                g[j][i] = g[i][j];
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
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
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
        int t = 0;
        for (int i = 0; i < n; i++) {
            t = 0;
            for (int j = 0; j < n; j++) {
                t += g[i][j];
            }
            if (t == n - 1) {
                printf("Вершина %d - доминирующая\n", i + 1);
            }
            if (t == 1) {
                printf("Вершина %d - концевая\n", i + 1);
            }
            if (t == 0) {
                printf("Вершина %d - изолированная\n", i + 1);
            }
        }
    }

    void run() {
        int** g = NULL;
        int n = 0, r;
        int choice;
        while (1) {
            printf("\n[Неориентированный простой граф]\n");
            printf("выберите действие и введите его номер:\n"
                " 1 - создать граф\n"
                " 2 - задать случайные связи вершин графа\n"
                " 3 - вывести граф\n"
                " 4 - определить размер графа (количество рёбер)\n"
                " 5 - определить типы вершин\n"
                " 6 - выход в главное меню\n");
            scanf_s("%d", &choice);
            switch (choice) {
            case 1:
                if (g != NULL) freeGraph(g, n);
                g = createGraph(&n);
                break;
            case 2: randGraph(g, n); break;
            case 3: printGraph(g, n); break;
            case 4: r = rcount(g, n); printf("%d\n", r); break;
            case 5: typevertex(g, n); break;
            case 6: if (g != NULL) freeGraph(g, n); return;
            default: break;
            }
        }
    }
}

// ============================================================
// Вариант 2: Неориентированный с матрицей инцидентности (lr5q2.cpp)
// ============================================================
namespace UndirectedIncidence {

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
        }
        return g;
    }

    void printGraph(int** g, int n) {
        int i, j;
        if (g == NULL) {
            printf("Граф ещё не был создан\n");
            return;
        }
        printf("\nГраф: \n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
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
            for (int j = i + 1; j < n; j++) {
                g[i][j] = rand() % 2;
                g[j][i] = g[i][j];
            }
        }
        printGraph(g, n);
    }

    int rcount(int** g, int n) {
        if (g == NULL) return 0;
        int r = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
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
        int t = 0;
        for (int i = 0; i < n; i++) {
            t = 0;
            for (int j = 0; j < n; j++) {
                t += g[i][j];
            }
            if (t == n - 1) {
                printf("Вершина %d - доминирующая\n", i + 1);
            }
            if (t == 1) {
                printf("Вершина %d - концевая\n", i + 1);
            }
            if (t == 0) {
                printf("Вершина %d - изолированная\n", i + 1);
            }
        }
    }

    int** createInc(int** g, int n, int* m) {
        if (g == NULL) {
            printf("Граф ещё не был создан\n");
            *m = 0;
            return NULL;
        }
        *m = rcount(g, n);
        int** inc = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++) {
            inc[i] = (int*)calloc(*m, sizeof(int));
        }
        int edgeIndex = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (g[i][j] == 1) {
                    inc[i][edgeIndex] = 1;
                    inc[j][edgeIndex] = 1;
                    edgeIndex++;
                }
            }
        }
        return inc;
    }

    void printInc(int** inc, int n, int m) {
        if (inc == NULL || m == 0) {
            printf("Матрица инцидентности пуста\n");
            return;
        }
        printf("Матрица инцидентности:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", inc[i][j]);
            }
            printf("\n");
        }
    }

    void typevertexInc(int** inc, int n, int m) {
        if (inc == NULL) {
            printf("Матрица инцидентности ещё не была создана\n");
            return;
        }
        for (int i = 0; i < n; i++) {
            int t = 0;
            for (int j = 0; j < m; j++) {
                t += inc[i][j];
            }
            if (t == 0) {
                printf("Вершина %d - изолированная\n", i + 1);
            }
            if (t == 1) {
                printf("Вершина %d - концевая\n", i + 1);
            }
            if (t == n - 1 && n > 1) {
                printf("Вершина %d - доминирующая\n", i + 1);
            }
        }
    }

    void run() {
        int** g = NULL;
        int** inc = NULL;
        int n = 0;
        int m = 0;
        int r;
        int choice;
        while (1) {
            printf("\n[Неориентированный граф с матрицей инцидентности]\n");
            printf("выберите действие и введите его номер:\n"
                " 1 - создать граф\n"
                " 2 - задать случайные связи вершин графа\n"
                " 3 - вывести граф и матрицу инцидентности\n"
                " 4 - определить размер графа (количество рёбер)\n"
                " 5 - определить типы вершин\n"
                " 6 - выход в главное меню\n");
            scanf_s("%d", &choice);
            switch (choice) {
            case 1:
                if (g != NULL) freeGraph(g, n);
                if (inc != NULL) freeGraph(inc, n);
                g = createGraph(&n);
                inc = NULL;
                break;
            case 2:
                randGraph(g, n);
                if (inc != NULL) freeGraph(inc, n);
                inc = NULL;
                break;
            case 3:
                if (inc != NULL) freeGraph(inc, n);
                inc = createInc(g, n, &m);
                printGraph(g, n);
                printInc(inc, n, m);
                break;
            case 4:
                r = rcount(g, n);
                printf("%d\n", r);
                break;
            case 5: typevertex(g, n); break;
            case 6:
                if (g != NULL) freeGraph(g, n);
                if (inc != NULL) freeGraph(inc, n);
                return;
            default: break;
            }
        }
    }
}

// ============================================================
// Вариант 3: Ориентированный с петлями и матрицей инцидентности
// ============================================================
namespace DirectedIncidence {

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
            int outdeg = 0;
            int indeg = 0;
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
        int edgeCount = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (g[i][j] == 1) edgeCount++;

        if (edgeCount == 0) {
            printf("Матрица инцидентности: рёбер нет.\n");
            return;
        }

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
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < edgeCount; k++) {
                int u = eu[k];
                int v = ev[k];
                if (u == i && v == i) {
                    printf("%3d ", 2);
                }
                else if (u == i) {
                    printf("%3d ", -1);
                }
                else if (v == i) {
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

    void run() {
        int** g = NULL;
        int n = 0, r;
        int choice;
        while (1) {
            printf("\n[Ориентированный граф с петлями и матрицей инцидентности]\n");
            printf("выберите действие и введите его номер:\n"
                " 1 - создать граф\n"
                " 2 - задать случайные связи вершин графа\n"
                " 3 - вывести граф и матрицу инцидентности\n"
                " 4 - определить размер графа (количество рёбер)\n"
                " 5 - определить типы вершин\n"
                " 6 - выход в главное меню\n");
            scanf_s("%d", &choice);
            switch (choice) {
            case 1:
                if (g != NULL) freeGraph(g, n);
                g = createGraph(&n);
                break;
            case 2: randGraph(g, n); break;
            case 3:
                printGraph(g, n);
                printIncidenceMatrix(g, n);
                break;
            case 4:
                r = rcount(g, n);
                printf("Количество рёбер: %d\n", r);
                break;
            case 5: typevertex(g, n); break;
            case 6: if (g != NULL) freeGraph(g, n); return;
            default: printf("Нет такого действия\n"); break;
            }
        }
    }
}

// ============================================================
// Главное меню
// ============================================================
int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int mode;
    while (1) {
        printf("\n=== Главное меню ===\n");
        printf("Выберите вариант графа:\n");
        printf(" 1 - Неориентированный простой граф\n");
        printf(" 2 - Неориентированный граф с матрицей инцидентности\n");
        printf(" 3 - Ориентированный граф с петлями и матрицей инцидентности\n");
        printf(" 0 - Выход из программы\n");
        scanf_s("%d", &mode);
        switch (mode) {
        case 1: UndirectedSimple::run(); break;
        case 2: UndirectedIncidence::run(); break;
        case 3: DirectedIncidence::run(); break;
        case 0: return 0;
        default: printf("Нет такого варианта\n"); break;
        }
    }
}