#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string.h>

using namespace std;

// Состояния
enum State { Sep, Error, Alpha, Digit, SgnAsgn, SgnSml, SgnBig, SgnArthm, Smcln };
enum Symbol { alp, dig, ssm, sbg, asgn, arthm, semi, sep, oth, End };

// Проверка на арифметические знаки
//bool isarith(char c) { return (c == '+' || c == '-' || c == '*' || c == '/'); }

// Проверка на ключевое слово
bool isKeyword(const char* const b, const char* const e)
{
    if (b >= e)
        return false;

    const char* const keyWord[]{ "and", "if", "else", "not", "or", "then", "end" };

    for (const char* kW : keyWord)
        if (strlen(kW) == (size_t)(e - b) && strncmp(b, kW, e - b) == 0)
            return true;

    return false;
}

// Соответствие допустимым символам
int Check(char c)
{
    if (c == '\0')
        return 1;

    const char* const symbols[]{ " \t\n", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", "0123456789", "=", "<", ">", "+-*/", ";" };

    int count = 0;
    for (const char* ch : symbols)
    {
        count++;

        while (*ch) {
            if (c == *ch)
                return count;

            ch++;
        }
    }

    return 0;
}

// Структура лексемы
struct Lex
{
    enum class LexType { lWl, lKw, lEq, lCo, lAo, lId, lVl, lSc, };

    LexType type = LexType::lWl;

    // Указатели на начало и конец лексемы
    const char* b = 0;
    const char* e = 0;

    // Функция вывода лексем с ее типом
    void output(ostream& out, bool t) const
    {
        const char* p = b;
        while (p < e && *p != '\0')
            out << *p++;

        if (!t)
            return;

        switch (type) {
        case Lex::LexType::lWl:
            out << "[wl]";
            break;
        case Lex::LexType::lKw:
            out << "[kw]";
            break;
        case Lex::LexType::lEq:
            out << "[eq]";
            break;
        case Lex::LexType::lCo:
            out << "[co]";
            break;
        case Lex::LexType::lAo:
            out << "[ao]";
            break;
        case Lex::LexType::lId:
            out << "[id]";
            break;
        case Lex::LexType::lVl:
            out << "[vl]";
            break;
        case Lex::LexType::lSc:
            out << "[sc]";
            break;
        }
    }
};

// Еще одна функция проверки, которая не пригодилась
//Symbol check(char c)
//{
//    if (c == '\0') return End;
//    if (isspace(c) || iscntrl(c)) return sep;
//    if (isalpha(c)) return alp;
//    if (isdigit(c)) return dig;
//    if (c == '=') return asgn;
//    if (c == ';') return semi;
//    if (isarith(c)) return arthm;
//    if (c == '<') return ssm;
//    if (c == '>') return sbg;
//    return oth;
//}

// Функция лексического анализатора
void lexAnalysis(vector<Lex>& list, const char* line) {
    State state = State::Sep;
    Lex l;
    l.b = line;

    State table[9][9]
    {
        /*Begin  Error     Sep    Alpha    Digit      SgnAsgn      SgnSml      SgnBig       SgnArthm      Smcln*/
        /*alp*/  {Error,   Sep,   Alpha,   Digit,     SgnAsgn,     SgnSml,     SgnBig,      SgnArthm,     Smcln},
        /*dig*/  {Error,   Sep,   Error,   Error,     SgnAsgn,     SgnSml,     SgnBig,      SgnArthm,     Smcln},
        /*ssm*/  {Error,   Sep,   Alpha,   Alpha,     SgnAsgn,     SgnSml,     SgnBig,      SgnArthm,     Smcln},
        /*sbg*/  {Error,   Sep,   Error,   Digit,     SgnAsgn,     SgnSml,     SgnBig,      SgnArthm,     Smcln},
        /*asgn*/ {Error,   Sep,   Alpha,   Digit,     SgnAsgn,     SgnSml,     SgnBig,      SgnArthm,     Smcln},
        /*arthm*/{Error,   Sep,   Alpha,   Digit,     SgnAsgn,     SgnSml,     SgnBig,      SgnArthm,     Smcln},
        /*semi*/ {Error,   Sep,   Alpha,   Digit,     SgnAsgn,     SgnSml,     SgnBig,      SgnArthm,     Smcln},
        /*sep*/  {Error,   Sep,   Alpha,   Digit,     SgnAsgn,     SgnSml,     SgnBig,      SgnArthm,     Smcln},
        /*oth*/  {Error,   Sep,   Alpha,   Digit,     SgnAsgn,     SgnSml,     SgnBig,      SgnArthm,     Smcln},
        /*end*/
    };

    // Логика конечного автомата
    do {
        State prevState = state;
        state = table[(int)state][Check(*line)];

        switch (prevState) {
        case State::Sep:
            l.b = line;
            continue;

        case State::Error:
            if (state == State::Error)
                continue;

            l.type = Lex::LexType::lWl;
            break;

        case State::Alpha:
            if (state == State::Error || state == State::Alpha)
                continue;

            if (line - l.b > 5)
                l.type = Lex::LexType::lWl;
            else
                l.type = isKeyword(l.b, line) ? Lex::LexType::lKw : Lex::LexType::lId;

            break;

        case State::Digit:
            if (state == State::Error || state == State::Digit)
                continue;


            l.type = Lex::LexType::lVl;
            break;

        case State::SgnSml:
            if (state == State::SgnBig)
                continue;

        case State::SgnBig:
            l.type = Lex::LexType::lCo;
            break;

        case State::SgnAsgn:
            l.type = Lex::LexType::lEq;
            break;

        case State::SgnArthm:
            l.type = Lex::LexType::lAo;
            break;

        case State::Smcln:
            l.type = Lex::LexType::lSc;
            break;
        }

        l.e = line;
        list.push_back(l);
        l.b = line;

    } while (*line++);
}

// Функция вывода 
int OutputData(vector<Lex>& list)
{
    ofstream out("output.txt", ios::binary);

    if (out)
    {
        for (const Lex lexem : list)
            lexem.output(out, true), out << " ";

        out << "\n", cout << "\n";
        for (const Lex lexem : list)
            if (lexem.type == Lex::LexType::lId)
                lexem.output(out, false), out << " ";

        out << "\n";

        for (const Lex lexem : list)
            if (lexem.type == Lex::LexType::lVl)
                lexem.output(out, false), out << " ";

        out.close();
    }
    else
    {
        cout << "File not open";
        return 1;
    }

    return 0;
}


int InputData()
{
    // Открытие файла для считывания
    ifstream in("input.txt", ios::binary);

    if (in)
    {
        cout << "File OK" << endl;

        int size = 0;

        // Переход в конец файла
        in.seekg(0, ios::end);

        // Получение текущей позиции
        size = in.tellg();

        // Отсчитывание позиции с начала файла
        in.seekg(0, ios::beg);

        char* line = new char[size + 1];

        // Считывание входной строки
        in.read(line, size);

        line[size] = 0;

        // Закрытие файла для чтения
        in.close();

        // Создание вектора лексем
        vector<Lex>list;
        lexAnalysis(list, line);

        OutputData(list);

        delete[] line;
    }
    else
        cout << "File not open";

    return 0;
}

int main()
{
    setlocale(LC_ALL, ".1251");
    InputData();
}