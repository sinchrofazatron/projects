#include <iostream>
#include <fstream>
#include <queue>

using namespace std;
// Структура дерева
struct tree
{
    int val;
    tree* left;
    tree* right;
};

// Функция создания узла дерева
tree* createnode(int a)
{
    tree* T = new tree;
    T->val = a;
    T->left = T->right = NULL;
    return T;
}

// Функция вставки узла
void push(tree* n, tree*& root)
{
    // Проверка на пустоту
    if (!root)
    {
        root = n;
        return;
    }

    // Формирование очереди
    queue<tree*> q;
    q.push(root);

    while (!q.empty())
    {
        // Получение элемента из начала очереди
        tree* current = q.front();

        // Удаление элемента из начала очереди
        q.pop();

        // Проверка на существование левого поддерева
        if (!current->left)
        {
            current->left = n;
            break;
        }

        // Проверка на существование правого поддерева
        else if (!current->right)
        {
            current->right = n;
            break;
        }

        // Рекурсивный вызов функции
        else
        {
            q.push(current->left);
            q.push(current->right);
        }
    }
}

//  Функция нахождения высоты дерева
int height(tree* root)
{
    if (root)
    {
        int lh = root->left ? height(root->left) : 0;
        int rh = root->right ? height(root->right) : 0;

        return 1 + min(lh, rh);
    }
    else
        return 0;
}

// Функция, выполняющая процедуру (модуль элементов дерева)
void Abs(tree* root)
{
    if (root == NULL)
        return;

    // Примение функции к значению узла 
    root->val = abs(root->val);

    // Рекурсивный вызов функции
    Abs(root->left);
    Abs(root->right);
}

// Функция сохранения значащих элементов в файл с учетом прямого обхода дерева
void output(tree* root, ofstream& fout)
{
    if (root == NULL)
        return;

    fout << root->val << " ";

    // Рекурсивный вызов функции
    output(root->left, fout);
    output(root->right, fout);
}

// Функция считывания данных из файла
void input(tree*& root)
{
    ifstream fin("input.txt");
    int a;

    if (fin)
    {
        while (!fin.eof())
        {
            fin >> a;

            // Проверка на существование корня дерева
            if (root)
                push(createnode(a), root);
            else
                root = createnode(a);
        }
    }
    else
        cout << "Error";
    fin.close();
}

void Delete(tree* root)
{
    if (root->left)   Delete(root->left);
    if (root->right)  Delete(root->right);
    delete root;
}

int main()
{
    ofstream fout("output.txt");
    tree* T = NULL;
    input(T);
    Abs(T);
    output(T, fout);
    Delete(T);
}

