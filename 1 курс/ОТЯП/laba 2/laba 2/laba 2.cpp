#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <cstring>
using namespace std;

// Прототипы функций для предварительного объявления
void LexAnalysis(vector<char*>& v);
vector<char*> TextProcessing(char* line);
void OutputData(vector <char*> vec);
void InputData();

// Грамматика для палиндрома
// S -> aSa|бSб|...|яSя|a|б|...|я|aa|бб|...|яя

// Состояния
enum Symbols { Char, Middle, Other, End };
enum States { First, Left, Right, Error, Last };

// Матрица переходов
//        First L     R     Error
// 
//Char    L     L     R     Error
//Middle  Last  R     Error Error
//Other   Error Error Error Error
//End     Last  Last  Last  Last

// Таблица переходов
const States table[4][4] =
{
    {Left, Left, Right, Error},
    {Last,  Right, Error, Error},
    {Error, Error, Error, Error},
    {Last, Last, Last, Last}
};

// Таблица лексического автомата
void CreateTable(States(*table)[4]) {

    table[Char][First] = Left;
    table[Char][Left] = Left;
    table[Char][Right] = Right;
    table[Char][Error] = Error;

    table[Middle][First] = Last;
    table[Middle][Left] = Right;
    table[Middle][Right] = Error;
    table[Middle][Error] = Error;

    table[Other][First] = Error;
    table[Other][Left] = Error;
    table[Other][Right] = Error;
    table[Other][Error] = Error;

    table[End][First] = First;
    table[End][Left] = Last;
    table[End][Right] = Error;
    table[End][Error] = Error;
}

// Функция проверки на соответствие букве русского алфавита
bool IsChar(char c) { return ((c <= 'я' && c >= 'А') || c == 'ё' || c == 'Ё'); }

// Функция проверки на соответствие символу разрыва и конца строки
bool IsEnd(char c) { return (c == ' ' || c == '\n' || c == '\t' || c == '\0'); }

// Функция проверки текущего символа
Symbols Check(char c) {

    if (IsChar(c)) return Char;
    if (IsEnd(c)) return End;
    if (c == '$') return Middle;
    return Other;
}

void InputData()
{
    // Открытие файла для считывания
    ifstream in("input.txt", ios::binary);

    if (in)
    {
        cout << "File OK" << endl;
        // Задание изначального размера файла
        int size = 0;

        // Переход в конец файла
        in.seekg(0, ios::end);

        // Получение текущей позиции
        size = in.tellg();

        // Отсчитывание позиции с начала файла
        in.seekg(0, ios::beg);

        // Выделение памяти под входную строку
        char* line = new char[size + 1];

        // Считывание входной строки
        in.read(&line[0], size);

        // Завершение входной строки нулем
        line[size] = 0;

        // Закрытие файла для чтения
        in.close();

        // Создание вектора под слова, соответствующие заданию
        vector<char*> vec;

        // Заполнение вектора
        vec = TextProcessing(line);

        // Передача вектора в функцию вывода в файл
        OutputData(vec);

        // Удаление изначальной строки
        delete[] line;
    }
}

// Функция, проверяющая размер каждого отдельного слова
vector<char*> TextProcessing(char* line)
{
    // Передача строки в переменную
    char* ch = line;

    // Создание вектора под букву слова
    vector<char*> v;

    // Пока есть строка
    while (*ch)
    {
        // Когда встречаем символ разрыва строки
        while (IsEnd(*ch))

            // Пропускаем его
            ch++;

        // Устанавливаем флаг начала слова на следующей позиции после символа разыва строки
        char* first = ch;

        // Пока не встретится символ разрыва строки
        while (!IsEnd(*ch))

            // Продолжаем двигаться по слову
            ch++;

        // Вычисление длины слова
        int s = ch - first;

        // Если длина слова меньше или равна 6-и
        if (s <= 6)
        {
            // Создание массив под слово
            char* w = new char[s + 1];

            // Копирование s элементов из first в w
            strncpy(w, first, s);

            // Завершающий 0 в конце слова
            w[s] = 0;

            // Запись слов в вектор
            v.push_back(w);
        }
    }
    // Передача вектора слов в функцию лексического анализатора
    LexAnalysis(v);

    // Возврат вектора слов
    return v;
}

// Функция лексического анализатора
void LexAnalysis(vector<char*>& v)
{
    // Проход по вектору
    for (int i = 0; i < (int)v.size(); i++)
    {
        // Установка состояния начала
        States state = First;

        // Определние длины слова
        int size = strlen(v[i]);

        // Создание копии для слова
        char* word;

        // Обнаружение слова с нечетным количеством букв
        if (strlen(v[i]) % 2)
        {
            // Запись текущего слова в копию
            word = new char[strlen(v[i])];

            // Определение середины слова
            int mid = strlen(v[i]) / 2 + 1;

            // Перепись слова вплоть до середины из вектора в копию 
            strncpy(word, v[i], mid);

            // Проверка на то, является ли середина слова русской буквой
            if (IsChar(word[mid - 1]))

                // Замена середины слова на специальный символ
                word[mid - 1] = '$';

            // Копирование второй половины слова 
            strncpy(word + mid, v[i] + mid, (mid)-1);

            // Завершающий 0 в конце копии слова
            word[strlen(v[i])] = 0;
        }
        // Обнаружение слова с четным количеством букв
        else
        {
            // Запись текущего слова в копию с увеличенным на единицу размером
            word = new char[strlen(v[i]) + 1];

            // Определение середины слова
            int mid = strlen(v[i]) / 2;

            // Перепись первой половины слова в копию
            strncpy(word, v[i], mid);

            // Замена середины слова на специальный символ
            word[mid] = '$';

            // Копирование второй половины слова
            strncpy(word + mid + 1, v[i] + mid, (mid));

            // Завершающий 0 в конце копии слова
            word[strlen(v[i]) + 1] = 0;
        }

        // Создание таблицы автомата
        States table[4][4];
        CreateTable(table);

        // Создание магазина для автомата
        stack <char> shop;

        // Проход по копии слова
        for (int i = 0; i <= size && !word[i] == '\0'; i++)
        {
            // Если в слове достигнута середина
            if (state == Right)
            {
                // Сравнение верхнего элемента магазина и текущего в слове
                if (shop.top() == word[i])
                {
                    // Удаление символа из магазина
                    shop.pop();
                }
                else { break; }
            }
            // Установка состояния
            state = table[Check(word[i])][state];

            // Если в слове не достигнута середина
            if (state == Left)
            {
                // Добавление символа в магазин
                shop.push(word[i]);
            }

        }

        // Если состояние ошибочное или магазин пуст
        if (state == Error || !shop.empty())
        {
            // Удаление слова из вектора
            v.erase(v.begin() + i);
            i--;
        }
    }
}

// Функция записи в файл
void OutputData(vector <char*> vec)
{
    // Открытие файла для записи
    ofstream out("output.txt", ios::binary);

    // Вывод вектора слов - палиндромов
    for (int i = 0; i < (int)vec.size(); i++)
    {
        out << ' ' << vec[i];
    }

    // Закрытие файла для записи
    out.close();
}

int main()
{
    setlocale(LC_ALL, ".1251");

    // Функция считывания из файла
    InputData();
}