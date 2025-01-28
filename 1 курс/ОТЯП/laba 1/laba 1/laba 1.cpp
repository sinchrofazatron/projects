
#include <iostream>
#include <fstream>
using namespace std;

// Функция, определяющая, является ли символ буквой русского алфавита
bool is_alpha(char c) { return ((c <= 'я' && c >= 'А') || c == 'ё' || c == 'Ё') ? true : false; }

// Функция, определяющая, является ли слово палиндромом
bool palindrom(char* line, int beg, int end) // beg - указатель на начало слова, end - на конец
{
    for (; beg < end; beg++, end--)
        if (line[beg != line[end]])
            return false;
    return true;
}

// Функция прохода по массиву char и поиск разделителей строки
void func(char* line, ofstream& out)
{
    // cur - указатель на начало слова
    int cur = 0;
    for (int i = 0; i < 100; i++)
    {
        // Проход по массиву char до момента встречи символов-разделителей строки
        if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t' || line[i] == '\0')
        {
            // Проверка слова на соответствие палиндрому
            if (palindrom(line, cur, i - 1))
            {
                // Вывод палиндрома
                for (int c = cur; c < i; c++)
                {
                    cout << line[c];
                    out << line[c];
                }
                // Если последний символ - конец строки, пробел выводиться не будет
                if (line[i] != '\0')
                {
                    cout << " ";
                    out << " ";
                }
            }
            // Двигаемся по массиву до тех пор, пока i-й элемент не будет являться буквой
            while (!is_alpha(line[i])) cur = ++i; // Передвигаем указатель на букву, то есть на начало нового слова
        }
    }
}

int main()
{
    setlocale(LC_ALL, ".1251");

    ifstream in;

    ofstream out;
    // Открытие исходного файла
    in.open("input.txt");
    // Открытие файла для записи результата
    out.open("output.txt");

    char line[100];

    in.getline(line, 100, '\0');

    func(line, out);
    // Закрытие исходного файла
    in.close();
    // Закрытие файла для записи результата
    out.close();
}