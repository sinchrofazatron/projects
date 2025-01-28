#include <iostream>
#include <fstream>
using namespace std;
// Функция считывания данных из файла
void inputData(double** mas, int& s, double& d)
{

    ifstream in;
    in.open("input.txt");
    // Проверка открытия файла
    if (!in.is_open())
        cout << "File not open";
    else
    {
        // Считывание данных до конца файла
        while (!in.eof())
        {
            double data;
            // Считали данные в переменную
            in >> data;
            if (!in.bad())
            {
                // Создаем новый динамический массив с размером на единицу больше старого
                double* new_mas = new double[s + 1];

                // Запись старого массива в новый
                for (int i = 0; i < s; i++)
                    new_mas[i] = (*mas)[i];

                // Добавление нового элемента в новый массив
                new_mas[s] = data;

                // Удаление массива
                delete[] * mas;

                *mas = new_mas;
                s++;

                // Присвоение d первого элемента массива, с которым будут сраниваться остальные элементы
                d = new_mas[0];
            }
        }

    }

    // Закрытие файла для чтения результата
    in.close();
}

// Функция подсчета суммы чисел, удовлетворяющих заданию
double mainFunc(double* mas, int s, double d)
{
    double summ = 0;

    // Начинаем проход со второго элемента, т.к. идет сравнение с первым 
    for (int i = 1; i < s; i++)
    {
        // Проверка на соответствие условию задания
        if (mas[i] < 0 && mas[i] <= d)
            // Добавление элемента к общему результату в случае выполнения условия
            summ += mas[i];
    }
    // Возврат результата
    return summ;
}

// Функция записи данных в файл
void outputData(double* mas, int s, double d)
{
    ofstream out;
    out.open("output.txt");

    // Подсчет суммы
    double summ = mainFunc(mas, s, d);

    // Вывод данных в файл
    out << summ;

    // Вывод данных в консоль
    cout << summ;

    // Закрытие файла для вывода результата
    out.close();
}

int main()
{
    // Создание динамического массива
    double* mas = NULL;

    // Размера
    int s = 0;
    // Параметр (первый элемент массива), с которым будут сравниваться остальные элементы массива
    double d = 0;
    inputData(&mas, s, d);
    outputData(mas, s, d);

    // Удаление старого массива
    delete[] mas;
}