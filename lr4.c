#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};
struct Node* root;
struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL)
	{
		
		 if (root != NULL && root->data == data)
			return root;//Исключение повторок
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}
void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}
int Poisk(struct Node* r, int target)
{
	if (r == NULL)
		return 0; // не найдено

	if (r->data == target)
		return 1; // найдено

	// Учитываем инвертированность: слева больше, справа меньше
	if (target > r->data)
		return Poisk(r->left, target);
	else
		return Poisk(r->right, target);
}
int Count(struct Node* r, int target)
{
	if (r == NULL)
		return 0;

	int count = 0;
	if (r->data == target)
		count = 1;

	count += Count(r->left, target);
	count += Count(r->right, target);

	return count;
}
int main()
{
	setlocale(LC_ALL, "");
	int D, choice, start = 1;

	root = NULL;
	printf("0 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == 0)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
		{
			root = CreateTree(root, root, D);
		}
	}

	print_tree(root, 0);

	while (1)
	{
		printf("\nВыберите вариант работы с деревом\n");
		printf("1 - Поиск значения\n");
		printf("2 - Подсчёт вхождений\n");
		printf("3 - Выход\n");
		printf("Ваш выбор: ");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Введите число для поиска: ");
			scanf_s("%d", &D);
			if (Poisk(root, D))
				printf("Элемент %d найден в дереве.\n", D);
			else
				printf("Элемент %d не найден.\n", D);
			break;

		case 2:
		{
			printf("Введите число для подсчёта вхождений: ");
			scanf_s("%d", &D);
			int n = Count(root, D);
			printf("Число %d встречается %d раз(а).\n", D, n);
			break;
		}

		case 3:
			return 0;

		default:
			printf("Неверный выбор. Попробуйте снова.\n");
			break;
		}
	}

	return 0;
}
