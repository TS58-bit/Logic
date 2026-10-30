#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <queue>

#define REPEATS 5
#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

void freeGraph(int** g, int n) {
    for (int i = 0; i < n; i++) {
        free(g[i]);
    }
    free(g);
}

int** createGraph(int n) {
    int** g = (int**)malloc(n * sizeof(int*));

    if (g == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        g[i] = (int*)malloc(n * sizeof(int));

        if (g[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(g[j]);
            }

            free(g);
            return NULL;
        }
    }

    return g;
}

void printGraph(int** g, int n) {
    printf("    ");
    for (int j = 0; j < n; j++) {
        printf("%3d", j + 1);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%3d ", i + 1);

        for (int j = 0; j < n; j++) {
            printf("%3d", g[i][j]);
        }

        printf("\n");
    }
}

void randGraph(int** g, int n, int r) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        g[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            g[i][j] = (rand() % 100 < r) ? 1 : 0;
            g[j][i] = g[i][j];
        }
    }
    printGraph(g, n);
}

void initDistances(int* dist, int n, int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = -1;
    }

    dist[start] = 0;
}

void bfsGraph(int** g, int n, int start, int* dist) {
    std::queue<int> q;

    initDistances(dist, n, start);
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (g[v][i] == 1 && dist[i] == -1) {
                dist[i] = dist[v] + 1;
                q.push(i);
            }
        }
    }
}

Node** createGraphList(int** g, int n) {
    Node** gl = (Node**)malloc(n * sizeof(Node*));

    for (int i = 0; i < n; i++) {
        gl[i] = NULL;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (g[i][j] == 1) {

                Node* newNode = (Node*)malloc(sizeof(Node));

                newNode->vertex = j;
                newNode->next = NULL;
                if (gl[i] == NULL) {
                    gl[i] = newNode;
                }
                else {
                    Node* current = gl[i];

                    while (current->next != NULL) {
                        current = current->next;
                    }

                    current->next = newNode;
                }
            }
        }
    }

    return gl;
}

void printGraphList(Node** gl, int n) {
    printf("\nСписок смежности:\n");

    for (int i = 0; i < n; i++) {
        printf("%d: ", i + 1);

        Node* current = gl[i];

        while (current != NULL) {
            printf("%d ", current->vertex + 1);
            current = current->next;
        }

        printf("\n");
    }
}

void freeGraphList(Node** gl, int n) {
    for (int i = 0; i < n; i++) {

        Node* current = gl[i];

        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(gl);
}

void bfsList(Node** gl, int n, int start, int* dist) {
    std::queue<int> q;

    initDistances(dist, n, start);
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        Node* current = gl[v];

        while (current != NULL) {
            int neighbor = current->vertex;

            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[v] + 1;
                q.push(neighbor);
            }

            current = current->next;
        }
    }
}

void dfsGraphRecursive(int v, int** g, int n, int* dist) {
    for (int i = 0; i < n; i++) {
        if (g[v][i] == 1 &&
            (dist[i] == -1 || dist[i] > dist[v] + 1)) {

            dist[i] = dist[v] + 1;
            dfsGraphRecursive(i, g, n, dist);
        }
    }
}

void dfsGraph(int** g, int n, int start, int* dist) {
    initDistances(dist, n, start);
    dfsGraphRecursive(start, g, n, dist);
}

void dfsListRecursive(int v, Node** gl, int* dist) {
    Node* current = gl[v];

    while (current != NULL) {
        int neighbor = current->vertex;

        if (dist[neighbor] == -1 ||
            dist[neighbor] > dist[v] + 1) {

            dist[neighbor] = dist[v] + 1;
            dfsListRecursive(neighbor, gl, dist);
        }

        current = current->next;
    }
}

void dfsList(Node** gl, int n, int start, int* dist) {
    initDistances(dist, n, start);
    dfsListRecursive(start, gl, dist);
}

void measureTime() {
    int sizes[] = { 100, 200, 300, 400, 500, 1000 };
    int sizeCount = sizeof(sizes) / sizeof(sizes[0]);

    printf("Сравнение времени работы алгоритмов\n");
    printf("Среднее время одного запуска, мс\n");

    for (int s = 0; s < sizeCount; s++) {
        int n = sizes[s];

        int** g = createGraph(n);

        if (g == NULL) {
            printf("Не удалось создать граф n=%d\n", n);
            continue;
        }

        for (int i = 0; i < n; i++) {
            g[i][i] = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                g[i][j] = (rand() % 100 < 50) ? 1 : 0;
                g[j][i] = g[i][j];
            }
        }

        Node** gl = createGraphList(g, n);

        if (gl == NULL) {
            printf("Не удалось создать список смежности\n");
            freeGraph(g, n);
            continue;
        }

        int* dist = (int*)malloc(n * sizeof(int));

        if (dist == NULL) {
            printf("Ошибка выделения памяти\n");
            freeGraphList(gl, n);
            freeGraph(g, n);
            continue;
        }

        clock_t begin, end;
        double bfsM, bfsL, dfsM, dfsL;

        begin = clock();
        for (int k = 0; k < REPEATS; k++) {
            bfsGraph(g, n, 0, dist);
        }
        end = clock();
        bfsM = (double)(end - begin) * 1000.0 / CLOCKS_PER_SEC / REPEATS;

        begin = clock();
        for (int k = 0; k < REPEATS; k++) {
            bfsList(gl, n, 0, dist);
        }
        end = clock();
        bfsL = (double)(end - begin) * 1000.0 / CLOCKS_PER_SEC / REPEATS;

        begin = clock();
        for (int k = 0; k < REPEATS; k++) {
            dfsGraph(g, n, 0, dist);
        }
        end = clock();
        dfsM = (double)(end - begin) * 1000.0 / CLOCKS_PER_SEC / REPEATS;

        begin = clock();
        for (int k = 0; k < REPEATS; k++) {
            dfsList(gl, n, 0, dist);
        }
        end = clock();
        dfsL = (double)(end - begin) * 1000.0 / CLOCKS_PER_SEC / REPEATS;

        printf("%5d В ширину: матрица %f список %f. В глубину: матрица %f список %f\n", n, bfsM, bfsL, dfsM, dfsL);

        free(dist);
        freeGraphList(gl, n);
        freeGraph(g, n);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(NULL));

    int** g = NULL;
    Node** gl = NULL;

    int n = 0;
    int choice = 0;
    int start;
    bool graphReady = false;

    while (1) {
        printf(
            "\nВыберите действие и введите его номер:\n"
            "1 - создать граф\n"
            "2 - задать случайные связи вершин графа\n"
            "3 - вывести матрицу смежности\n"
            "4 - вывести список смежности\n"
            "5 - найти расстояния BFS по матрице\n"
            "6 - найти расстояния BFS по списку\n"
            "7 - найти расстояния DFS по матрице\n"
            "8 - найти расстояния DFS по списку\n"
            "9 - выполнить все алгоритмы\n"
            "10 - измерить время работы алгоритмов\n"
            "11 - выход\n"
            "Ваш выбор: "
        );

        if (scanf_s("%d", &choice) != 1) {
            printf("Ошибка ввода\n");
            break;
        }

        switch (choice) {
        case 1: {
            int newN;

            printf("Введите количество вершин графа ");

            if (scanf_s("%d", &newN) != 1) {
                printf("Ошибка ввода\n");
                if (g != NULL) {
                    freeGraph(g, n);
                }
                return 1;
            }

            if (newN < 1 || newN > MAX_VERTICES) {
                printf("Введите число от 1 до %d\n", MAX_VERTICES);
                break;
            }

            int** newGraph = createGraph(newN);

            if (newGraph == NULL) {
                printf("Ошибка выделения памяти\n");
                break;
            }

            if (g != NULL) {
                freeGraph(g, n);
            }

            g = newGraph;
            n = newN;
            graphReady = false;
            break;
        }

        case 2: {
            if (g == NULL) {
                printf("Граф ещё не создан\n");
                break;
            }
            int r;
            printf("Введите вероятность появления ребра\n");
            scanf_s("%d", &r);
            randGraph(g, n, r);
            graphReady = true;
            break;
        }

        case 3: {
            if (g == NULL || !graphReady) {
                printf("Граф ещё не создан или не заполнен\n");
                break;
            }

            printGraph(g, n);
            break;
        }

        case 4: {
            if (g == NULL || !graphReady) {
                printf("Граф ещё не создан или не заполнен\n");
                break;
            }

            gl = createGraphList(g, n);

            if (gl == NULL) {
                printf("Ошибка создания списка смежности\n");
                break;
            }

            printGraphList(gl, n);
            freeGraphList(gl, n);
            gl = NULL;

            break;
        }

        case 5: {
            if (g == NULL || !graphReady) {
                printf("Граф ещё не создан или не заполнен\n");
                break;
            }

            printf("Введите исходную вершину ");

            if (scanf_s("%d", &start) != 1) {
                printf("Ошибка ввода\n");
                freeGraph(g, n);
                return 1;
            }

            if (start < 1 || start > n) {
                printf("Неверный номер вершины\n");
                break;
            }

            start--;

            int* dist = (int*)malloc(n * sizeof(int));

            if (dist == NULL) {
                printf("Ошибка выделения памяти\n");
                break;
            }

            bfsGraph(g, n, start, dist);

            printf("\nОбход в ширину матрицы смежности\n");
            for (int i = 0; i < n; i++) {
                if (dist[i] == -1) {
                    printf("До вершины %d: недостижима\n", i + 1);
                }
                else {
                    printf("До вершины %d: %d\n", i + 1, dist[i]);
                }
            }

            free(dist);
            break;
        }

        case 6: {
            if (g == NULL || !graphReady) {
                printf("Граф ещё не создан или не заполнен\n");
                break;
            }

            printf("Введите исходную вершину ");

            if (scanf_s("%d", &start) != 1) {
                printf("Ошибка ввода\n");
                freeGraph(g, n);
                return 1;
            }

            if (start < 1 || start > n) {
                printf("Неверный номер вершины\n");
                break;
            }

            start--;

            gl = createGraphList(g, n);

            if (gl == NULL) {
                printf("Ошибка создания списка смежности\n");
                break;
            }

            int* dist = (int*)malloc(n * sizeof(int));

            if (dist == NULL) {
                printf("Ошибка выделения памяти\n");
                freeGraphList(gl, n);
                gl = NULL;
                break;
            }

            bfsList(gl, n, start, dist);

            printf("\nОбход в ширину списка смежности\n");
            for (int i = 0; i < n; i++) {
                if (dist[i] == -1) {
                    printf("До вершины %d: недостижима\n", i + 1);
                }
                else {
                    printf("До вершины %d: %d\n", i + 1, dist[i]);
                }
            }

            free(dist);
            freeGraphList(gl, n);
            gl = NULL;

            break;
        }

        case 7: {
            if (g == NULL || !graphReady) {
                printf("Граф ещё не создан или не заполнен\n");
                break;
            }

            printf("Введите исходную вершину ");

            if (scanf_s("%d", &start) != 1) {
                printf("Ошибка ввода\n");
                freeGraph(g, n);
                return 1;
            }

            if (start < 1 || start > n) {
                printf("Неверный номер вершины\n");
                break;
            }

            start--;

            int* dist = (int*)malloc(n * sizeof(int));

            if (dist == NULL) {
                printf("Ошибка выделения памяти\n");
                break;
            }

            dfsGraph(g, n, start, dist);

            printf("\nОбход в глубину матрицы смежности\n");
            for (int i = 0; i < n; i++) {
                if (dist[i] == -1) {
                    printf("До вершины %d: недостижима\n", i + 1);
                }
                else {
                    printf("До вершины %d: %d\n", i + 1, dist[i]);
                }
            }

            free(dist);
            break;
        }

        case 8: {
            if (g == NULL || !graphReady) {
                printf("Граф ещё не создан или не заполнен\n");
                break;
            }

            printf("Введите исходную вершину ");

            if (scanf_s("%d", &start) != 1) {
                printf("Ошибка ввода\n");
                freeGraph(g, n);
                return 1;
            }

            if (start < 1 || start > n) {
                printf("Неверный номер вершины\n");
                break;
            }

            start--;

            gl = createGraphList(g, n);

            if (gl == NULL) {
                printf("Ошибка создания списка смежности\n");
                break;
            }

            int* dist = (int*)malloc(n * sizeof(int));

            if (dist == NULL) {
                printf("Ошибка выделения памяти\n");
                freeGraphList(gl, n);
                gl = NULL;
                break;
            }

            dfsList(gl, n, start, dist);

            printf("\nОбход в глубину списка смежности\n");
            for (int i = 0; i < n; i++) {
                if (dist[i] == -1) {
                    printf("До вершины %d: недостижима\n", i + 1);
                }
                else {
                    printf("До вершины %d: %d\n", i + 1, dist[i]);
                }
            }

            free(dist);
            freeGraphList(gl, n);
            gl = NULL;

            break;
        }

        case 9: {
            if (g == NULL || !graphReady) {
                printf("Сначала создайте граф и задайте связи\n");
                break;
            }

            printf("Введите исходную вершину ");

            if (scanf_s("%d", &start) != 1) {
                printf("Ошибка ввода\n");
                freeGraph(g, n);
                return 1;
            }

            if (start < 1 || start > n) {
                printf("Неверный номер вершины\n");
                break;
            }

            start--;

            gl = createGraphList(g, n);

            if (gl == NULL) {
                printf("Ошибка создания списка смежности\n");
                break;
            }

            int* distBfsM = (int*)malloc(n * sizeof(int));
            int* distBfsL = (int*)malloc(n * sizeof(int));
            int* distDfsM = (int*)malloc(n * sizeof(int));
            int* distDfsL = (int*)malloc(n * sizeof(int));

            if (distBfsM == NULL || distBfsL == NULL || distDfsM == NULL || distDfsL == NULL) {
                printf("Ошибка выделения памяти\n");
                if (distBfsM) free(distBfsM);
                if (distBfsL) free(distBfsL);
                if (distDfsM) free(distDfsM);
                if (distDfsL) free(distDfsL);
                freeGraphList(gl, n);
                gl = NULL;
                break;
            }

            bfsGraph(g, n, start, distBfsM);
            printf("\nОбход в ширину матрицы смежности\n");
            for (int i = 0; i < n; i++) {
                if (distBfsM[i] == -1) {
                    printf("До вершины %d: недостижима\n", i + 1);
                }
                else {
                    printf("До вершины %d: %d\n", i + 1, distBfsM[i]);
                }
            }

            bfsList(gl, n, start, distBfsL);
            printf("\nОбход в ширину списка смежности\n");
            for (int i = 0; i < n; i++) {
                if (distBfsL[i] == -1) {
                    printf("До вершины %d: недостижима\n", i + 1);
                }
                else {
                    printf("До вершины %d: %d\n", i + 1, distBfsL[i]);
                }
            }

            dfsGraph(g, n, start, distDfsM);
            printf("\nОбход в глубину матрицы смежности\n");
            for (int i = 0; i < n; i++) {
                if (distDfsM[i] == -1) {
                    printf("До вершины %d: недостижима\n", i + 1);
                }
                else {
                    printf("До вершины %d: %d\n", i + 1, distDfsM[i]);
                }
            }

            dfsList(gl, n, start, distDfsL);
            printf("\nОбход в глубину списка смежности\n");
            for (int i = 0; i < n; i++) {
                if (distDfsL[i] == -1) {
                    printf("До вершины %d: недостижима\n", i + 1);
                }
                else {
                    printf("До вершины %d: %d\n", i + 1, distDfsL[i]);
                }
            }

            free(distBfsM);
            free(distBfsL);
            free(distDfsM);
            free(distDfsL);
            freeGraphList(gl, n);
            gl = NULL;

            break;
        }

        case 10: {
            measureTime();
            break;
        }

        case 11: {
            if (gl != NULL) {
                freeGraphList(gl, n);
            }

            if (g != NULL) {
                freeGraph(g, n);
            }

            return 0;
        }

        default:
            break;
        }
    }
}