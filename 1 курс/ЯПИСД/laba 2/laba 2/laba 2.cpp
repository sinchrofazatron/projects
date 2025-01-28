#include <iostream>
#include <fstream>
using namespace std;

// Прототипы функций для предварительного объявления
long long productMat(int* row, int columns);
void outputData(int** mat, int rows, int columns);
int inputData();

// Функция считывания размера матрицы и ее элементов
int inputData()
{
    ifstream in;
    in.open("input.txt"); // Открытие файла для считывания

    int rows; // Строки
    int columns; // Столбцы

    in >> rows >> columns; // Считывание количества строк и столбцов

    int** mat = new int* [rows]; // Создание двумерного динамического массива под матрицу
    for (int i = 0; i < rows; i++)
        mat[i] = new int[columns];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            in >> mat[i][j]; // Заполнение матрицы элементами из файла

    outputData(mat, rows, columns); // Функция вывода результатов построчного умножения матрицы в файл

    for (int i = 0; i < rows; i++) // Удаление двумерного динамического массива 
        delete[] mat[i];
    delete[] mat;
    in.close(); // Закрытие файла для чтения
    return 0;
}

// Функция, обрабатывающая массив (построчное умножение)
long long productMat(int* row, int columns)
{
    long long p = 1; // Переменная, куда записывается результат умножения (использован тип данных long long для хранения больших чисел)
    for (int j = 0; j < columns; j++)
        p *= row[j]; // Перемножение только тех элементов, чья строка является текущей на данный момент
    return p; // Возврат резултата произведения
}

void outputData(int** mat, int rows, int columns)
{
    ofstream out;
    out.open("output.txt"); // Открытие файла для записи

    long long res = 0; // Переменная для записи результата умножения. Выбран тип long long для хранения больших чисел

    for (int i = 0; i < rows; i++)
    {
        res = productMat(mat[i], columns); // Результатом умножения является результат работы функции productMat, в которую передается текущая строка и все ее элементы
        out << res << " "; // Вывод результата в файл
    }

    out.close(); // Закрытие файла для вывода
}

int main()
{
    inputData(); // Считывание данных из файла
}