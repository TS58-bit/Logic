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
			return root; /* исключение повторок */

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

		if (data > root->data) root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

/* --- вспомогательные функции для вертикального вывода --- */

int tree_height(struct Node* r)
{
	if (r == NULL) return 0;
	int lh = tree_height(r->left);
	int rh = tree_height(r->right);
	return 1 + (lh > rh ? lh : rh);
}

int tree_size(struct Node* r)
{
	if (r == NULL) return 0;
	return 1 + tree_size(r->left) + tree_size(r->right);
}

int max_digits(struct Node* r)
{
	if (r == NULL) return 0;
	char buf[32];
	int len = sprintf_s(buf, sizeof(buf), "%d", r->data);
	int l = max_digits(r->left);
	int rr = max_digits(r->right);
	int m = len;
	if (l > m) m = l;
	if (rr > m) m = rr;
	return m;
}

void fill_canvas(struct Node* r, char** canvas, int depth, int* col, int W)
{
	if (r == NULL) return;

	/* Дерево инвертированное: слева большие, справа меньшие.
	   Для вывода меньшие должны быть слева, поэтому идём в right первым. */
	fill_canvas(r->right, canvas, depth + 1, col, W);

	int x = *col;
	char buf[32];
	int len = sprintf_s(buf, sizeof(buf), "%d", r->data);
	for (int i = 0; i < len; i++)
		canvas[depth][x + i] = buf[i];
	*col += W;

	fill_canvas(r->left, canvas, depth + 1, col, W);
}

void print_vertical(struct Node* r)
{
	if (r == NULL) return;

	int h = tree_height(r);
	int n = tree_size(r);
	int md = max_digits(r);
	int W = md + 4;
	int cols = n * W + md + 4;

	char** canvas = (char**)malloc(h * sizeof(char*));
	if (canvas == NULL) { printf("Ошибка памяти\n"); exit(1); }
	for (int y = 0; y < h; y++)
	{
		canvas[y] = (char*)malloc(cols * sizeof(char));
		if (canvas[y] == NULL) { printf("Ошибка памяти\n"); exit(1); }
		for (int x = 0; x < cols - 1; x++)
			canvas[y][x] = ' ';
		canvas[y][cols - 1] = '\0';
	}

	int col = 0;
	fill_canvas(r, canvas, 0, &col, W);

	for (int y = 0; y < h; y++)
	{
		int last = cols - 1;
		while (last > 0 && canvas[y][last - 1] == ' ')
			last--;
		canvas[y][last] = '\0';
		printf("%s\n", canvas[y]);
	}

	for (int y = 0; y < h; y++)
		free(canvas[y]);
	free(canvas);
}

void print_tree(struct Node* r, int l)
{
	(void)l;
	print_vertical(r);
}

/* --- поиск и подсчёт с уровнями --- */

int Poisk(struct Node* r, int target, int level)
{
	if (r == NULL) return 0;
	if (r->data == target) return level;

	if (target > r->data)
		return Poisk(r->left, target, level + 1);
	else
		return Poisk(r->right, target, level + 1);
}

int Count(struct Node* r, int target, int level)
{
	if (r == NULL) return 0;

	int count = 0;
	if (r->data == target)
	{
		printf("  -> найдено на уровне %d\n", level);
		count = 1;
	}
	count += Count(r->left, target, level + 1);
	count += Count(r->right, target, level + 1);
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
	printf("\n");

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
		{
			printf("Введите число для поиска: ");
			scanf_s("%d", &D);
			int lvl = Poisk(root, D, 1);
			if (lvl)
				printf("Элемент %d найден в дереве на уровне %d.\n", D, lvl);
			else
				printf("Элемент %d не найден.\n", D);
			break;
		}
		case 2:
		{
			printf("Введите число для подсчёта вхождений: ");
			scanf_s("%d", &D);
			int n = Count(root, D, 1);
			if (n == 0)
				printf("Число %d не встречается в дереве.\n", D);
			else
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