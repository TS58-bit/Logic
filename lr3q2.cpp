#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node
{
    char inf[256];
    struct node* next;
};

struct node* head = NULL;
struct node* last = NULL;

void add()
{
    struct node* p;

    p = (struct node*)malloc(sizeof(struct node));

    if (p == NULL)
    {
        printf("Ошибка памяти\n");
        return;
    }

    printf("Введите название ");
    scanf_s("%s", p->inf, (unsigned)sizeof(p->inf));

    p->next = NULL;

    if (head == NULL)
    {
        head = p;
        last = p;
    }
    else
    {
        last->next = p;
        last = p;
    }
}

void del()
{
    struct node* p;

    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    p = head;
    head = head->next;

    free(p);

    if (head == NULL)
        last = NULL;
}

void review()
{
    struct node* p = head;
    int i = 1;

    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    while (p != NULL)
    {
        printf("%d. %s\n", i, p->inf);
        p = p->next;
        i++; 
    }
}

void find()
{
    char name[50];
    struct node* p = head;
    int i = 1;

    printf("Введите название элемента ");
    scanf_s("%s", name, (unsigned)sizeof(name));

    while (p != NULL)
    {
        if (strcmp(name, p->inf) == 0)
        {
            printf("Элемент есть в очереди %s под номером %d\n", p->inf, i);
            return;
        }
        i++;
        p = p->next;
    }

    printf("Элемент не найден\n");
}

void clear()
{
    struct node* p;

    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }

    last = NULL;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int choice;

    while (1) {
        printf("Выберете действие и введите его номер.\n 1 - добавить элемент в очередь\n 2 - вывести очередь\n 3 - найти элемент в очереди\n 4 - удалить элемент из очереди\n 5 - очистить очередь\n 6 - выход\n");
        scanf_s("%d", &choice);

        switch (choice)
        {
        case 1:
            add();
            break;

        case 2:
            review();
            break;

        case 3:
            find();
            break;

        case 4:
            del();
            break;

        case 5:
            clear();
            break;

        case 6:
            return 0;

        default:
            printf("Некорректный символ\n");
        }

    }
}