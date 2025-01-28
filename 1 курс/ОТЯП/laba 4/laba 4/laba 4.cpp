#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
//#include <string.h>

using namespace std;

// Структура лексемы
struct Lex
{
    enum class LexType { lWl, lIf, lEl, lTh, lEn, lNo, lEq, lCo, lAo, lLo, lId, lVl, lSc, };

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
        case Lex::LexType::lIf:
            out << "[if]";
            break;
        case Lex::LexType::lEl:
            out << "[el]";
            break;
        case Lex::LexType::lTh:
            out << "[th]";
            break;
        case Lex::LexType::lEn:
            out << "[en]";
            break;
        case Lex::LexType::lNo:
            out << "[no]";
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
        case Lex::LexType::lLo:
            out << "[lo]";
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

// Состояния лексического анализатора 
enum State { Sep, Error, Alpha, Digit, SgnAsgn, SgnSml, SgnBig, SgnArthm, Smcln };
//enum Symbol { alp, dig, ssm, sbg, asgn, arthm, semi, sep, oth, End };


// Матрица переходов лексического анализатора
const State table[9][9]
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

// Проверка на арифметические знаки
bool isarith(char c) { return (c == '+' || c == '-' || c == '*' || c == '/'); }

// Состояния синтаксического анализатора 
enum StateSyntax { S, A, C, D, E, G, H, I, J, K, F, ER };

// Матрица переходов синтаксического анализатора
StateSyntax table_synt[11][12]
{
    //       if  th  el  en  no  lo  id  vl  co  eq  ao  sc
    /*S*/   {A,  ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER,},
    /*A*/   {ER, ER, ER, ER, E,  ER, D,  D,  ER, ER, ER, ER,},
    /*C*/   {ER, ER, ER, ER, ER, ER, D,  D,  ER, ER, ER, ER,},
    /*D*/   {ER, G,  ER, ER, ER, A,  ER, ER, C,  C, ER, ER,},
    /*E*/   {ER, ER, ER, ER, ER, ER, D,  D,  ER, ER, ER, ER,},
    /*G*/   {ER, ER, ER, ER, ER, ER, H,  ER, ER, ER, ER, ER,},
    /*H*/   {ER, ER, ER, ER, ER, ER, ER, ER, ER, I,  ER, ER,},
    /*I*/   {ER, ER, ER, ER, ER, ER, J,  J,  ER, ER, ER, ER,},
    /*J*/   {ER, ER, G,  F,  ER, ER, ER, ER, ER, ER, I,  K, },
    /*K*/   {ER, ER, ER, ER, ER, ER, H,  ER, ER, ER, ER, ER,},
    /*F*/   {A,  ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER,},
};

// Допустимые символы
int Check(char c)
{
    if (c == '\0' || c == '\t' || c == '\n' || c == ' ') return 1;
    if (isalpha(c)) return 2;
    if (isdigit(c)) return 3;
    if (c == '=') return 4;
    if (c == '<') return 5;
    if (c == '>') return 6;
    if (isarith(c)) return 7;
    if (c == ';') return 8;
    else
        return 0;
}

// Логика работы синтаксического анализатора
int syntAnalysis(Lex::LexType type)
{
    switch (type)
    {
    case Lex::LexType::lIf:
        return 0;
    case Lex::LexType::lTh:
        return 1;
    case Lex::LexType::lEl:
        return 2;
    case Lex::LexType::lEn:
        return 3;
    case Lex::LexType::lNo:
        return 4;
    case Lex::LexType::lLo:
        return 5;
    case Lex::LexType::lId:
        return 6;
    case Lex::LexType::lVl:
        return 7;
    case Lex::LexType::lCo:
        return 8;
    case Lex::LexType::lEq:
        return 9;
    case Lex::LexType::lAo:
        return 10;
    case Lex::LexType::lSc:
        return 11;
    }

    return 0;
}

// Ожидаемые лексемы после ошибки
const char* alsoSyntAnalysis(StateSyntax state) {
    switch (state) {
    case StateSyntax::S:
        return "if";
    case StateSyntax::A:
        return "id no vl";
    case StateSyntax::C:
        return "id vl";
    case StateSyntax::D:
        return "co eq lo th";
    case StateSyntax::E:
        return "vl id";
    case StateSyntax::G:
        return "id";
    case StateSyntax::H:
        return "eq";
    case StateSyntax::I:
        return "id vl";
    case StateSyntax::J:
        return "ao el en sc";
    case StateSyntax::K:
        return "id";
    case StateSyntax::F:
        return "if";
    }
    return 0;
}

// Определение лексемы ключевых слов
Lex::LexType kW(const char* const b, const char* const e) {
    if (b >= e || e - b > 5)
        return Lex::LexType::lWl;

    int size = e - b;

    if (size == 2 && strncmp(b, "or", size) == 0)
        return Lex::LexType::lLo;

    if (size == 3 && strncmp(b, "and", size) == 0)
        return Lex::LexType::lLo;

    if (size == 3 && strncmp(b, "end", size) == 0)
        return Lex::LexType::lEn;

    if (size == 3 && strncmp(b, "not", size) == 0)
        return Lex::LexType::lNo;

    if (size == 2 && strncmp(b, "if", size) == 0)
        return Lex::LexType::lIf;

    if (size == 4 && strncmp(b, "then", size) == 0)
        return Lex::LexType::lTh;

    if (size == 4 && strncmp(b, "else", size) == 0)
        return Lex::LexType::lEl;

    return Lex::LexType::lId;
}

// Проверка на допустимое число
bool is_vl(const char* const b, const char* const e) {
    if (e - b > 5)
        return false;

    int vl = 0;
    for (auto line = b; line < e; ++line) {
        vl *= 10;
        vl += *b - '0';
    }

    return vl <= 33333;
}

// Функция лексического анализатора
void lexAnalysis(vector<Lex>& list, const char* line) {
    State state = State::Sep;
    Lex l;
    l.b = line;

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
            l.type = kW(l.b, line);
            break;

        case State::Digit:
            if (state == State::Error || state == State::Digit)
                continue;


            l.type = is_vl(l.b, line) ? Lex::LexType::lVl : Lex::LexType::lWl;
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

// Функция вывода ошибки
const char* ERROR(vector<Lex>& list, int& p) {
    StateSyntax state = StateSyntax::S;

    p = 0;
    for (const Lex& line : list)
    {
        StateSyntax nextstate = table_synt[(int)state][syntAnalysis(line.type)];
        if (nextstate == StateSyntax::ER)
            return alsoSyntAnalysis(state);

        state = nextstate;
        ++p;
    }

    return 0;
}

// Функция вывода 
int OutputData(vector<Lex>& list)
{

    ofstream out("output.txt", ios::binary);

    if (out)
    {
        int pos;

        const char* nextlexems = ERROR(list, pos);

        for (const Lex lexem : list) {
            lexem.output(out, true), out << " ";

        }

        out << "\n", cout << "\n";
        if (nextlexems) {
            out << pos << " " << nextlexems;

        }
        else {
            out << "OK";

        }

        out.close();
    }
    else
        cout << "File not open";

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