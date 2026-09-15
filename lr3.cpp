#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node
{
    char inf[256];
    int priority;
    struct node* next;
};

struct node* head = NULL;


struct node* get_struct()
{
    struct node* p;

    p = (struct node*)malloc(sizeof(struct node));

    if (p == NULL)
    {
        printf("Ошибка памяти\n");
    }

    printf("Введите название ");
    scanf_s("%s", p->inf, (unsigned)sizeof(p->inf));

    printf("Введите приоритет ");
    scanf_s("%d", &p->priority);

    p->next = NULL;

    return p;
}


void add()
{
    struct node* p;
    struct node* q;

    p = get_struct();

    if (head == NULL)
    {
        head = p;
        return;
    }

    if (p->priority > head->priority)
    {
        p->next = head;
        head = p;
        return;
    }

    q = head;

    while (q->next != NULL &&
        q->next->priority >= p->priority)
    {
        q = q->next;
    }

    p->next = q->next;
    q->next = p;
}

void review()
{
    struct node* p = head;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    printf("Список\n");

    while (p != NULL)
    {
        printf("Название: %s, приоритет: %d\n", p->inf, p->priority);

        p = p->next;
    }
}

void find()
{
    char name[256];
    struct node* p = head;

    printf("Введите элемент, который нужно найти ");
    scanf_s("%s", name, (unsigned)sizeof(name));

    while (p != NULL)
    {
        if (strcmp(name, p->inf) == 0)
        {
            printf("Элемент \" %s \", приоритет = % d\n", p->inf, p->priority);
            return;
        }

        p = p->next;
    }

    printf("Элемент не найден\n");
}

void del()
{
    char name[256];
    struct node* p = head;
    struct node* prev = NULL;

    printf("Введите название элемента, который нужно удалить ");
    scanf_s("%s", name, (unsigned)sizeof(name));

    if (head != NULL && strcmp(name, head->inf) == 0)
    {
        head = head->next;
        free(p);

        printf("Элемент удалён\n");
        return;
    }

    while (p != NULL)
    {
        if (strcmp(name, p->inf) == 0)
        {
            prev->next = p->next;
            free(p);

            printf("Элемент удалён\n");
            return;
        }

        prev = p;
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
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int choice;

    while (1){
        printf("Выберете действие и введите его номер.\n 1 - добавить элемент в список\n 2 - вывести список\n 3 - найти элемент в списке\n 4 - удалить элемент из списка\n 5 - очистить список\n 6 - выход\n");
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
