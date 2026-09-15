#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h> // добавлено для strstr/strcmp
#include <windows.h>


struct student
{
    char famil[20];
    char name[20], facult[20];
    int Nomzach;
};

// было stud[3], стало динамическим
struct student* stud = NULL;
int studCount = 0;


void createStructArray()
{
    int n;
    printf("Введите количество студентов: ");
    if (scanf_s("%d", &n) != 1 || n <= 0) {
        printf("Некорректный размер\n");
        studCount = 0;
        return;
    }

    if (stud != NULL) {
        free(stud);
        stud = NULL;
    }

    stud = (struct student*)malloc(n * sizeof(struct student));
    if (stud == NULL) {
        printf("Ошибка выделения памяти\n");
        studCount = 0;
        return;
    }

    studCount = n;
    printf("Массив структур на %d студентов создан\n", studCount);
}


void turnmass(int* d, int s)
{
    if (d == NULL || s <= 0) {
        printf("Массив не создан\n");
        return;
    }
    int temp, i = 0;
    while (i < s / 2)
    {
        temp = d[i];
        d[i] = d[s - 1 - i];
        d[s - 1 - i] = temp;
        i++;
    }
    i = 0;
    while (i < s) printf(" %d", d[i++]);
}

int* createmass(int* size) {
    printf("Введите размер массива");
    scanf_s("%d", size);
    if (*size <= 0) {
        printf("Введён единичный, нулевой или отрицательный размер\n");
        *size = 0;
        return NULL;
    }
    int* d = (int*)malloc((*size) * sizeof(int));
    if (d == NULL) {
        printf("Ошибка\n");
        *size = 0;
        return NULL;
    }
    printf("массив создан, заполните его по команде 2\n");
    return d;
}

void diffmaxmin(int* d, int s)
{
    if (d == NULL || s <= 0) {
        printf("Массив не создан\n");
        return;
    }
    int max = d[0], min = d[0];
    for (int i = 1; i < s; i++) {
        if (max < d[i]) max = d[i];
        if (min > d[i]) min = d[i];
    }
    int diff = max - min;
    printf("разница между максимальным %d и минимальным %d элементами массива = %d\n", max, min, diff);
}

void randmass(int* d, int s) {
    if (d == NULL || s <= 0) {
        printf("Массив не создан\n");
        return;
    }
    int max, min;
    printf("введите максимальное возможное значение элемента\n");
    scanf_s("%d", &max);
    printf("введите минимальное возможное значение элемента\n");
    scanf_s("%d", &min);
    for (int i = 0; i < s; i++) {
        d[i] = min + rand() % (max - min + 1);
    }
    printf("созданный массив\n");
    for (int i = 0; i < s; i++) {
        printf("%4d ", d[i]);
    }
    printf("\n");
}

void freeMatrix(int** m, int rows) {
    if (m != NULL) {
        for (int i = 0; i < rows; i++) {
            if (m[i] != NULL) free(m[i]);
        }
        free(m);
    }
}
int** createMatrix(int* rows, int* cols) {
    printf("Введите количество строк");
    if (scanf_s("%d", rows) != 1 || *rows <= 0) { *rows = 0; return NULL; }
    printf("Введите количество столбцов");
    if (scanf_s("%d", cols) != 1 || *cols <= 0) { *rows = 0; *cols = 0; return NULL; }

    int** m = (int**)malloc((*rows) * sizeof(int*));
    if (m == NULL) return NULL;

    for (int i = 0; i < *rows; i++) {
        m[i] = (int*)malloc((*cols) * sizeof(int));
    }
    printf("Двумерный массив создан, заполните его по команде 2\n");
    return m;
}

void randMatrix(int** m, int rows, int cols) {
    if (m == NULL || rows <= 0 || cols <= 0) {
        printf("Двумерный массив не создан\n");
        return;
    }
    int min, max;
    printf("Введите минимальное значение");
    scanf_s("%d", &min);
    printf("Введите максимальное значение");
    scanf_s("%d", &max);

    if (min > max) { int t = min; min = max; max = t; }

    printf("Созданный двумерный массив\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m[i][j] = min + rand() % (max - min + 1);
            printf("%4d ", m[i][j]);
        }
        printf("\n");
    }
}


void sumrows(int** m, int cols, int l) {
    if (m == NULL) {
        printf("Двумерный массив не создан\n");
        return;
    }
    int sum = 0;
    for (int j = 0; j < cols; j++) {
        sum += m[l - 1][j];
    }
    printf("Сумма всех элементов %d строки = %d\n", cols, sum);
}

void sumcols(int** m, int rows, int l) {
    if (m == NULL) {
        printf("Двумерный массив не создан\n");
        return;
    }
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += m[i][l - 1];
    }
    printf("Сумма всех элементов %d столбца = %d\n", rows, sum);
}


void printstrukt() {
    if (stud == NULL || studCount <= 0) {
        printf("Массив структур не создан\n");
        return;
    }

    for (int i = 0; i < studCount; i++)
    {
        printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n",
            stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
    }
}

void scanstruct() {
    if (stud == NULL || studCount <= 0) {
        printf("Массив структур не создан. Сначала задайте размер.\n");
        return;
    }

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    for (int i = 0; i < studCount; i++)
    {
        printf("Введите фамилию студента\n");
        scanf_s("%20s", stud[i].famil, (unsigned)_countof(stud[i].famil));
    }
    for (int i = 0; i < studCount; i++)
    {
        printf("Введите имя студента %s\n", stud[i].famil);
        scanf_s("%20s", stud[i].name, (unsigned)_countof(stud[i].name));
    }
    for (int i = 0; i < studCount; i++)
    {
        printf("Введите название факультета студента %s %s\n", stud[i].famil, stud[i].name);
        scanf_s("%20s", stud[i].facult, (unsigned)_countof(stud[i].facult));
    }
    for (int i = 0; i < studCount; i++)
    {
        printf("Введите номер зачётной книжки студента %s %s\n", stud[i].famil, stud[i].name);
        scanf_s("%d", &stud[i].Nomzach);
    }
}


void findstruct() {
    if (stud == NULL || studCount <= 0) {
        printf("Массив структур не создан\n");
        return;
    }

    char f[21], n[21];
    int found = 0;

    printf("Введите часть фамилии (для пропуска введите *):\n");
    scanf_s("%20s", f, (unsigned)_countof(f));
    printf("Введите часть имени (для пропуска введите *):\n");
    scanf_s("%20s", n, (unsigned)_countof(n));

    int useF = strcmp(f, "*") != 0;
    int useN = strcmp(n, "*") != 0;

    if (!useF && !useN) {
        printf("Не заданы параметры поиска\n");
        return;
    }

    for (int i = 0; i < studCount; i++) {
        int matchF = useF && (strstr(stud[i].famil, f) != NULL);
        int matchN = useN && (strstr(stud[i].name, n) != NULL);

        // Минимальное совпадение: достаточно совпадения хотя бы одного поля.
        // Если нужно искать строго по обоим полям, замените на:
        // if ((useF ? matchF : 1) && (useN ? matchN : 1))
        if (matchF || matchN) {
            printf("Найден: Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n",
                stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
            found = 1;
        }
    }

    if (!found) {
        printf("Студент по заданным параметрам не найден\n");
    }
}


int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
    int* d = NULL;
    int size = 0;
    int** m = NULL;
    int rows = 0, cols = 0, l;
    int choice;
    int type1, type2, type3, type4;

    while (1) {
        printf("1 - Вычислить разницу между минимальным и максимальным элементами массива\n");
        printf("2 - инициализация массива случайными числами\n");
        printf("3 - создание массива произвольного размера (вводится с клавиатуры\n");
        printf("4 - вычисление суммы значений в строке/строке двумерного массива\n");
        printf("5 - поиск среди структур student структуру с заданными параметрами (фамилией, именем)\n");
        printf("6 - обратить массив\n");
        printf("7 - ввод структуры или вывод на экран\n");
        printf("8 - выход\n");
        printf("9 - задать количество студентов\n");

        printf("Введите цифру задачи, которую вы выбрали\n");
        scanf_s("%d", &choice);

        switch (choice)
        {
        case 1: diffmaxmin(d, size); break;

        case 2:
            printf("1 - Одномерный, 2 - Двумерный");
            scanf_s("%d", &type1);
            if (type1 == 1) randmass(d, size);
            else if (type1 == 2) randMatrix(m, rows, cols);
            else printf("Неправильное значение\n");
            break;

        case 3:
            printf("1 - Одномерный массив, 2 - Двумерный массив");
            scanf_s("%d", &type2);
            if (type2 == 1) {
                if (d != NULL) { free(d); d = NULL; }
                d = createmass(&size);
            }
            else if (type2 == 2) {
                if (m != NULL) { freeMatrix(m, rows); m = NULL; }
                m = createMatrix(&rows, &cols);
            }
            else {
                printf("Неправильное значение\n");
            }
            break;

        case 4:
            printf("1 - в строке, 2 - в столбце ");
            scanf_s("%d", &type3);
            printf("введите номер столбца/строки");
            scanf_s("%d", &l);
            if (type3 == 1) sumrows(m, cols, l);
            else if (type3 == 2) sumcols(m, rows, l);
            else printf("Неправильное значение\n");
            break;

        case 5: findstruct(); break;

        case 6: turnmass(d, size); break;

        case 7:
            printf("1 - ввести структуру, 2 - вывести структуру, 3 - задать размер массива структур");
            scanf_s("%d", &type4);
            if (type4 == 1) {
                if (stud == NULL || studCount <= 0) createStructArray();
                if (stud != NULL) scanstruct();
            }
            else if (type4 == 2) {
                printstrukt();
            }
            else if (type4 == 3) {
                createStructArray();
            }
            else {
                printf("Неправильное значение\n");
            }
            break;

        case 9:
            createStructArray();
            break;

        case 8:
            if (d != NULL) { free(d); d = NULL; }
            if (stud != NULL) { free(stud); stud = NULL; }
            return 0;

        default:
            break;
        }
    }

    getchar();
}