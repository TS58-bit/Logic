#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <queue>

#define MAX 300

int NUM[MAX];
int deg[MAX];
struct QNode
{
    int data;
    QNode* next;
};
struct ListQueue {
    QNode* head;
    QNode* tail;
};
void initQueue(ListQueue* q) {
    q->head = NULL;
    q->tail = NULL;
}
bool isEmpty(ListQueue* q) {
    return q->head == NULL;
}
void pushQueue(ListQueue* q, int x) {
    QNode* p = (QNode*)malloc(sizeof(QNode));
    p->data = x;
    p->next = NULL;

    if (q->tail != NULL)
        q->tail->next = p;
    else
        q->head = p;

    q->tail = p;
}
int popQueue(ListQueue* q) {
    if (isEmpty(q)) return -1;

    QNode* p = q->head;
    int x = p->data;
    q->head = p->next;

    if (q->head == NULL)
        q->tail = NULL;

    free(p);
    return x;
}
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
void printSP(int n, int M[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        printf("%d.", i + 1);
        for (int j = 0; j < deg[i]; j++) {
            printf(" %d", M[i][j] + 1); 
        }
        printf("\n");
    }
    
}
void generateGraf(int n, int G[MAX][MAX], int M[MAX][MAX], int r){
    for (int i = 0; i < n; i++) {
        deg[i] = 0;
        for (int j = 0; j < n; j++) {
            G[i][j] = 0;
            M[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            G[j][i] = G[i][j] = (rand() % 100 < r) ? 1 : 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (G[i][j] == 1) {
                M[i][deg[i]++] = j;
                M[j][deg[j]++] = i;
            }
        }
    }
}
void BFS(int G[MAX][MAX], int n, int i) {
    std::queue<int> Q;
    Q.push(i);
    NUM[i] = 1;
    while (!Q.empty()) {
        i = Q.front();
        Q.pop();
        printf("%d ", i + 1);
        for (int j = 0; j < n; j++) {
            if (G[i][j] == 1 && NUM[j] == 0) {
                Q.push(j);
                NUM[j] = 1;
            }
        }
    }
}
void POH(int n, int G[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        NUM[i] = 0;
    for (int i = 0; i < n; i++) {
        if (NUM[i] == 0)
            BFS(G, n, i);
    }
    
}
void BFS_SP(int M[MAX][MAX], int n, int i) {
    std::queue<int> Q;
    Q.push(i);
    NUM[i] = 1;
    while (!Q.empty()) {
        i = Q.front();
        Q.pop();
        printf("%d ", i + 1);
        for (int j = 0; j < deg[i]; j++) {
            int u = M[i][j];
            if (NUM[u]== 0) {
                Q.push(u);
                NUM[u] = 1;
            }
        }
    }
}
void POH_SP(int n, int M[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        NUM[i] = 0;
    for (int i = 0; i < n; i++) {
        if (NUM[i] == 0)
            BFS_SP(M, n, i);
    }

}
void BFS_QLIST(int G[MAX][MAX], int n, int i) {
    ListQueue Q;
    initQueue(&Q);
    pushQueue(&Q, i);
    NUM[i] = 1;
    while(!isEmpty(&Q)) {
        i = popQueue(&Q);
        printf("%d ", i + 1);
        for (int j = 0; j < n; j++) {
            if (G[i][j] == 1 && NUM[j] == 0) {
                pushQueue(&Q, j);
                NUM[j] = 1;
            }
        }
    }
}
void POH_QLIST(int n, int G[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        NUM[i] = 0;
    for (int i = 0; i < n; i++) {
        if (NUM[i] == 0)
            BFS_QLIST(G, n, i);
    }
}
int main(void) {
    srand((unsigned int)time(NULL));
    setlocale(LC_ALL, "Russian");
    int n = 4;
    int choice = 0;
    int r = 0;
    static int G[MAX][MAX];
    static int M[MAX][MAX];
    clock_t start, end;
    while (1) {
        printf("\nВыберите вариант работы:\n");
        printf("1 - Генерировать граф\n");
        printf("2 - Обход в ширину по матрице\n");
        printf("3 - Обход в ширину по спискам смежности\n");
        printf("4 - Обход в ширину по матрице с помощью очереди через список\n");
        printf("5 - Сравнение скорости\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 1: {
            printf("\nРазмер: ");
            scanf_s("%d", &n);
            if (n > MAX) {
                printf("Слишком большой размер, установлено %d\n", MAX);
                n = MAX;
            }
            printf("Вероятность ребра(1-100): ");
            scanf_s("%d", &r);
            generateGraf(n, G, M, r);
            printGraf(n, G);
            printSP(n, M);
            break;
        }
        case 2: {
            POH(n, G);
            break;
        }
        case 3: {
            POH_SP(n, M);
            break;
        }
        case 4: {
            POH_QLIST(n, G);
            break;
        }
        case 5: {
            int in[5];
            double ResQue[5];
            double ResList[5];
            int cnt = 0;
            for (int i = 100; i <= 300; i += 50) {
                printf("\nНа %d:\n", i);
                generateGraf(i, G, M, r);
                printf("Время на Queue:\n");
                start = clock();
                POH(i, G);
                end = clock();
                printf("\nВремя: %.3fs \n", ((double)(end - start) / CLOCKS_PER_SEC));
                ResQue[cnt] = (double)(end - start) / CLOCKS_PER_SEC;
                printf("Время на ListQueue:\n");
                start = clock();
                POH_QLIST(i, G);
                end = clock();
                printf("\nВремя: %.3fs \n", ((double)(end - start) / CLOCKS_PER_SEC));
                ResList[cnt] = (double)(end - start) / CLOCKS_PER_SEC;
                in[cnt] = i;
                cnt++;

            }
            for (int i = 0; i < cnt; i++) {
                printf("Замер номер %d на %d\n", i + 1, in[i]);
                printf("Queue %.3fs: \n", ResQue[i]);
                printf("ListQueue %.3fs: \n", ResList[i]);
            }
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
