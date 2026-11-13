#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <queue>
#include <string.h> 
#define MAX 3000

int DIST[MAX];

void printGraf(int n, int G[MAX][MAX]) {
    printf("    ");
    for (int j = 0; j < n; j++) {
        printf("%3d", j + 1);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%3d ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%3d", G[i][j]);
        }
        printf("\n");
    }
}

void generateGraf(int n, int G[MAX][MAX], int r, int l, int weighted) {
    if (weighted == 0) {
        if (l == 0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    G[i][j] = 0;
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    G[j][i] = G[i][j] = (rand() % 100 < r) ? 1 : 0;
                }
            }
        }
        if (l == 1) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    G[i][j] = 0;
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    if (i != j && rand() % 2 == 0) {
                        G[i][j] = (rand() % 100 < r) ? 1 : 0;
                    }
            }
        }
    }
    else {
        if (l == 0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    G[i][j] = 0;
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    G[j][i] = G[i][j] = rand() % r + 1;
                }
            }
        }
        if (l == 1) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    G[i][j] = 0;
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    if (i != j && rand() % 2 == 0) {
                        G[i][j] = rand() % r + 1;
                    }
            }
        }
    }
}
void BFS(int G[MAX][MAX], int n, int i) {
    std::queue<int> Q;
    Q.push(i);
    DIST[i] = 0;
    while (!Q.empty()) {
        i = Q.front();
        Q.pop();
        printf("%d ", i + 1);
        for (int j = 0; j < n; j++) {
            if (G[i][j] > 0 && DIST[j] == -1) {
                Q.push(j);
                DIST[j] = DIST[i] + G[i][j];
            }

        }
    }
}
void POH(int n, int G[MAX][MAX]) {
    int ecc[MAX];
    int v = 0;
    int diametr = -1;
    int radius = MAX;
    for (int v = 0; v < n; v++) {
        int extmax = 0;
        printf("От %d\n", v + 1);
        for (int i = 0; i < n; i++) {
            DIST[i] = -1;

        }
        BFS(G, n, v);


        for (int i = 0; i < n; i++) {
            if (DIST[i] == -1 || DIST[i] == 0) {
                printf(" inf");
                continue;
            }
            printf(" %d", DIST[i]);
            if (extmax == 0 || extmax < DIST[i]) {
                extmax = DIST[i];

            }
        }
        ecc[v] = extmax;
        printf("\nЭксцентриситет: %d\n", extmax);
        printf("\n");
        if (extmax > diametr)
            diametr = extmax;
        if (extmax < radius || extmax != 0) {
            radius = extmax;
        }

    }
    printf("Диаметр: %d", diametr);
    printf("\nРадиус: %d", radius);
    printf("\nПериферийные вершины: ");
    for (int i = 0; i < n; i++) {
        if (ecc[i] == diametr)
            printf(" %d", i + 1);
    }
    printf("\nЦентральные вершины: ");
    for (int i = 0; i < n; i++) {
        if (ecc[i] == radius)
            printf(" %d", i + 1);
    }
}


int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));
    setlocale(LC_ALL, "Russian");
    int n = 4;
    int choice = 0;
    int l = 0;
    int r = 0;
    static int G[MAX][MAX];
    clock_t start, end;
    if (argc > 1) {
        int weighted = 1;
        l = 0;
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-weighted") == 0 && i + 1 < argc) {
                weighted = atoi(argv[++i]);
            }
            else if (strcmp(argv[i], "-directed") == 0 && i + 1 < argc) {
                l = atoi(argv[++i]);
            }
            else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
                n = atoi(argv[++i]);
            }
            else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
                r = atoi(argv[++i]);
            }
        }
        if (n > MAX) n = MAX;
        if (n < 1)   n = 1;
        if (weighted) {
            if (r < 1) r = 10;
        }
        printf("Параметры: n=%d, weighted=%d, directed=%d, r=%d\n\n",
            n, weighted, l, r);
        generateGraf(n, G, r, l, weighted);
        printGraf(n, G);
        printf("\n");
        POH(n, G);
        return 0;
    }
    while (1) {
        printf("\nВыберите вариант работы:\n");
        printf("1 - Генерировать граф неориентированный\n");
        printf("2 - Поиск расстояний (BFSD) по матрице и метрик\n");
        printf("3 - Генерация ориентированого графа\n");
        printf("4 - Генерировать граф неориентированный невзвешенный\n");
        printf("5 - Генерировать граф ориентированный невзвешенный\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 1: {
            l = 0;
            printf("\nРазмер: ");
            scanf_s("%d", &n);
            if (n > MAX) {
                printf("Слишком большой размер, установлено %d\n", MAX);
                n = MAX;
            }
            printf("Веc ребра(0-100): ");
            scanf_s("%d", &r);
            generateGraf(n, G, r, l, 1);
            printGraf(n, G);
            break;
        }
        case 2: {
            POH(n, G);
            break;
        }
        case 3: {
            l = 1;
            printf("\nРазмер: ");
            scanf_s("%d", &n);
            if (n > MAX) {
                printf("Слишком большой размер, установлено %d\n", MAX);
                n = MAX;
            }
            printf("Веc ребра(0-100): ");
            scanf_s("%d", &r);
            if (r < 1) r = 1;
            generateGraf(n, G, r, l, 1);
            printGraf(n, G);
            break;
        }
        case 4: {
            l = 0;
            printf("\nРазмер: ");
            scanf_s("%d", &n);
            if (n > MAX) {
                printf("Слишком большой размер, установлено %d\n", MAX);
                n = MAX;
            }
            printf("Шанс ребра(0-100): ");
            scanf_s("%d", &r);
            generateGraf(n, G, r, l, 0);
            printGraf(n, G);
            break;
        }
        case 5: {
            l = 1;
            printf("\nРазмер: ");
            scanf_s("%d", &n);
            if (n > MAX) {
                printf("Слишком большой размер, установлено %d\n", MAX);
                n = MAX;
            }
            printf("Шанс ребра(0-100): ");
            scanf_s("%d", &r);
            generateGraf(n, G, r, l, 0);
            printGraf(n, G);
            break;
        }

        case 0: {
            return 0;
        }
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
            break;
        }
    }
    return 0;
}
