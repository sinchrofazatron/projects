#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Класс "Прямоугольник"
class Rectangle
{

public:
    double x; // Координаты
    double y; // центра
    double length; // Длина 
    double width; // Ширина

    // Конструктор по умолчанию
    Rectangle() : x(0), y(0), length(0), width(0) {}

    // Конструктор копирования
    Rectangle(const Rectangle& R)
    {
        x = R.x;
        y = R.y;
        length = R.length;
        width = R.width;
    }

    // Конструктор инициализации
    Rectangle(double x, double y, double length, double width) : x(x), y(y), length(length), width(width) {}

    // Деструктор 
    ~Rectangle() {};

    // Вспомогательная структура точки центра прямоугольника
    struct Point
    {
        double x;
        double y;

        // Чтоб можно было читать данные типа "точка точка"
        friend istream& operator>>(istream& in, Point& p)
        {
            in >> p.x >> p.y;
            return in;
        }

        friend ostream& operator<<(ostream& out, const Point& p)
        {
            out << p.x << " " << p.y;
            return out;
        }
    };

    // Вспомогательная структура стороны прямоугольника
    struct Side
    {
        double length;
        double width;

        // Чтоб можно было читать данные типа "сторона сторона"
        friend istream& operator>>(istream& in, Side& s)
        {
            in >> s.length >> s.width;
            return in;
        }

        friend ostream& operator<<(ostream& out, const Side& s)
        {
            out << s.length << " " << s.width;
            return out;
        }
    };

    // Перегрузка операции присваивания
    Rectangle& operator=(const Rectangle& rhs)
    {
        if (this != &rhs) {
            x = rhs.x;
            y = rhs.y;
            length = rhs.length;
            width = rhs.width;
        }
        return *this;
    }

    // "Дружим" операции чтения из потока и вывода в поток с классом
    friend ofstream& operator << (ofstream&, const Rectangle&);
    friend ifstream& operator >> (ifstream&, Rectangle&);

    // Метод замены центра прямоугольника
    Rectangle changeCentre(double x_new, double y_new)
    {
        x = x_new;
        y = y_new;
        return *this;
    }

    // Метод замены сторон прямоугольника
    Rectangle changeLength(double l_new, double w_new)
    {
        length = l_new;
        width = w_new;
        return *this;
    }

    // Вычисление площади
    double Square(double l, double w)
    {
        return l * w;
    }

    // Вычисление периметра
    double Perimetr(double l, double w)
    {
        return 2 * l + 2 * w;
    }

    // Сумма прямоугольников (нет ограничения на количество)
    static Rectangle sumRectangles(const vector<Rectangle>& rectangles)
    {
        Rectangle sumRect;

        double sumX = 0, sumY = 0, sumLength = 0, sumWidth = 0;

        for (const auto& rect : rectangles)
        {
            sumX += rect.x;
            sumY += rect.y;
            sumLength += rect.length;
            sumWidth += rect.width;
        }

        sumRect.x = sumX / rectangles.size();
        sumRect.y = sumY / rectangles.size();
        sumRect.length = sumLength;
        sumRect.width = sumWidth;

        return sumRect;
    }

};

// Перегрузка оператора чтения из потока
ifstream& operator >> (ifstream& in, Rectangle& R)
{
    in >> R.x >> R.y >> R.length >> R.width;
    return in;
}

// Перегрузка оператора вывода в поток
ofstream& operator << (ofstream& out, const Rectangle& R)
{
    out << R.x << " " << R.y << " " << R.length << " " << R.width;
    return out;
}

// Перегрузка оператора >
bool operator>(Rectangle& lhs, Rectangle& rhs)
{
    return (lhs.Square(lhs.length, lhs.width) > rhs.Square(rhs.length, rhs.width));
}

// Перегрузка оператора < 
bool operator<(Rectangle& lhs, Rectangle& rhs)
{
    return (lhs.Square(lhs.length, lhs.width) < rhs.Square(rhs.length, rhs.width));
}

// Перегрузка оператора >=  
bool operator>=(Rectangle& lhs, Rectangle& rhs)
{
    return (lhs.Square(lhs.length, lhs.width) >= rhs.Square(rhs.length, rhs.width));
}

// Перегрузка оператора <=  
bool operator<=(Rectangle& lhs, Rectangle& rhs)
{
    return (lhs.Square(lhs.length, lhs.width) <= rhs.Square(rhs.length, rhs.width));
}

// Перегрузка оператора ==  
bool operator==(Rectangle& lhs, Rectangle& rhs)
{
    return (lhs.Square(lhs.length, lhs.width) == rhs.Square(rhs.length, rhs.width));
}

// Функция выбора метода
void chooseMethod()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int method;

    // Считываем номер метода
    in >> method;

    Rectangle R;

    switch (method)
    {
    case 1:
    {
        Rectangle::Point point;
        in >> point;
        Rectangle::Point newPoint;
        in >> newPoint;
        out << R.changeCentre(newPoint.x, newPoint.y);
        break;
    }

    case 2:
    {
        Rectangle::Side side;
        in >> side;
        Rectangle::Side newSide;
        in >> newSide;
        out << R.changeLength(newSide.length, newSide.width);
        break;
    }

    case 3:
    {
        in >> R;
        out << R.Square(R.length, R.width);
        break;
    }

    case 4:
    {
        in >> R;
        out << R.Perimetr(R.length, R.width);
        break;
    }

    case 5:
    {
        // Создаем вектор, чтобы хранить данные неограниченного числа прямоугольников
        vector<Rectangle> rectangles;

        while (!in.eof())
        {
            Rectangle R;
            in >> R;
            rectangles.push_back(R);
        }

        Rectangle sumRect = Rectangle::sumRectangles(rectangles);
        out << sumRect;

        break;
    }

    case 6:
    {
        // Операции сравнения
        Rectangle R1, R2;
        in >> R1 >> R2;
        out << "Square 1: " << R1.Square(R1.length, R1.width) << " " << "Square 2: " << R2.Square(R2.length, R2.width) << endl;
        out << "R1 > R2: " << (R1 > R2) << endl;
        out << "R1 < R2: " << (R1 < R2) << endl;
        out << "R1 >= R2: " << (R1 >= R2) << endl;
        out << "R1 <= R2: " << (R1 <= R2) << endl;
        out << "R1 == R2: " << (R1 == R2) << endl;
        break;
    }

    case 7:
    {
        // Операция присваивания неинициализированному прямоугольнику R2 данных инициализированного прямоугольника R1
        Rectangle R1, R2;
        out << R2 << endl;
        in >> R1;
        out << (R2 = R1);
        break;
    }
    }

    in.close();
    out.close();
}

int main()
{
    chooseMethod();
}

