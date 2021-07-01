#include "RationalFracs.h"
#include "Matrix.h"
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool Find(string str, char n)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == n) {
            return true;
        }
        i++;
    }
    return false;
}
int CountChrs(string str, char n)
{
    int count = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == n) {
            count++;
        }
        i++;
    }
    return count;
}

vector<string> FillStrokes(vector<string> strokes, string stroke)
{
    int numofstroke = 0;
    strokes.push_back("");
    for (int i = 0; i < stroke.length(); i++)
    {
        if (stroke[i] != '\n' && stroke[i] != '\0')
            strokes[numofstroke] += stroke[i];
        else if (stroke[i] != '\0') {
            strokes.push_back("");
            numofstroke++;
        }
    }
    return strokes;
}
std::string readFile(const std::string& fileName) {
    std::ifstream f(fileName);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}
int main()
{
    setlocale(LC_ALL, "Russian");
    char k;
    string curstroke;
    string stroke;
    string filename;
    vector<string> strokes;
    map<string, Matrix<double>> matrixes;
    map<string, Frac> fracs;

    bool exit = false;
    bool end = false;

    //Ввод пользователем комманд
    cout << "Ввод комманд должен соответствовать следующим требованиям: " << endl;
    cout << "1. Пробелы должны стоять между знаками: =, /, *, +, -, между числами." << endl;
    cout << "2. Строки в матрицах отделяются знаком ';', после которого должен быть пробел, до него пробел не ставится." << endl;
    cout << "3. Название матрицы должно начинаться с буквы 'm', вектор - 'v', рациональное число - 'r'." << endl;
    cout << "4. Регистр символов не важен." << endl << endl;

    cout << "Пример корректного ввода комманд: " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "V1 = [ 1 2 3 ]\nM1 = [ 1 0 0; 0 1 0; 0 0 1 ]\nv2 = m1 * v1\nr = 1 / 3\nV3 = V2 * R\nM2 = T(M1)\nm2 = m1\nv3\nm2" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "k - Ввести значения с клавиатуры" << endl;
    cout << "f - Ввести значения с файла" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    cin >> k;
    switch (k)
    {
    case 'f':
        cout << "Введите имя файла: " << endl;
        cin >> filename;
        try
        {
            stroke = readFile(filename);
        }
        catch (const std::length_error&)
        {
            cout << "Файл не найден. " << endl;
            std::exit(EXIT_FAILURE);
        }
        break;
    case 'k':
        cout << "Можете начинать ввод комманд." << endl;
        cout << "Введите 'e', если хотите закончить ввод комманд: " << endl << endl;
        getline(cin, curstroke);
        while (!end)
        {
            getline(cin, curstroke);
            if (curstroke != "e")
                stroke += curstroke + "\n";
            else {
                end = true;
                stroke[stroke.length() - 1] = '\0';
            }
        }
        break;
    default:
        cout << "Введено неверное значение. " << endl;
        std::exit(EXIT_FAILURE);
        break;
    }

    //Преобразовываем команды в нижний регистр, чтобы все символы были одинаковые в этом плане.
    transform(stroke.begin(), stroke.end(), stroke.begin(), tolower);

    //Заполняем вектор строк
    strokes = FillStrokes(strokes, stroke);

    /*cout << strokes.size() << endl;
    for (int i = 0; i < strokes.size(); i++)
    {
        cout << strokes[i] << endl;
    }*/

    int nchar;
    int rows;
    int colms;
    string name;
    string num;
    string num2;
    string oper;
    vector<double> vals;
    string var;
    //Проходимся по всем строкам
    for (int i = 0; i < strokes.size(); i++)
    {
        nchar = 0;
        num = "";
        name = "";
        num2 = "";
        oper = "";
        vals.erase(vals.begin(), vals.end());
        rows = 0;
        colms = 0;
        //Определяем имя первой переменной, с которой будем работать
        while (strokes[i][nchar] != ' ' && strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0')
        {
            name += strokes[i][nchar];
            nchar++;
        }
        //В зависимости от переменной, продолжаем работу
        if (name[0] == 'm' || name[0] == 'v')
        {

            if (!Find(strokes[i], '=')) {
                cout << "-------------------------------------" << endl;
                cout << matrixes.find(name)->second << endl;
            }
            else {
                if (strokes[i][nchar] != ' ')
                {
                    cout << "Не найден пробел." << endl;
                    std::exit(EXIT_FAILURE);
                }
                if (strokes[i][nchar + 1] != '=')
                {
                    cout << "Не найден знак равенства." << endl;
                    std::exit(EXIT_FAILURE);
                }
                if (strokes[i][nchar + 2] != ' ')
                {
                    cout << "Не найден пробел." << endl;
                    std::exit(EXIT_FAILURE);
                }
                nchar += 3;
                if (strokes[i][nchar] == '[') {
                    if (!Find(strokes[i], ']')) {
                        cout << "Не найдена закрывающая скобка." << endl;
                        std::exit(EXIT_FAILURE);
                    }
                    if (name[0] == 'v')
                    {
                        rows = 1;
                        for (int j = nchar + 2; strokes[i][j] != ']'; j++)
                        {
                            if (strokes[i][j] != ' ')
                            {
                                num += strokes[i][j];
                            }
                            else if (strokes[i][j] == ' ')
                            {
                                vals.push_back(stod(num));
                                num.clear();
                            }
                            else {
                                cout << "Неправильно введенные данные." << endl;
                                std::exit(EXIT_FAILURE);
                            }
                        }
                        colms = vals.size();
                        //cout << colms << endl;

                        matrixes.emplace(name, Matrix<double>{rows, colms, name, vals});
                    }
                    rows = CountChrs(strokes[i], ';') + 1;
                    for (int j = nchar + 2; strokes[i][j] != ']'; j++)
                    {
                        if (strokes[i][j] != ';' && strokes[i][j] != ' ')
                        {
                            num += strokes[i][j];
                        }
                        if (colms == 0 && strokes[i][j] == ';')
                        {
                            vals.push_back(stod(num));
                            num.clear();
                            colms = vals.size();
                        }
                        else if (colms != 0 && strokes[i][j] == ';')
                        {
                            vals.push_back(stod(num));
                            num.clear();
                        }
                        if (colms != 0 && strokes[i][j] == ' ' && !num.empty())
                        {
                            vals.push_back(stod(num));
                            num.clear();
                        }
                        if (strokes[i][j] == ' ' && colms == 0 && !num.empty())
                        {
                            vals.push_back(stod(num));
                            num.clear();
                        }

                    }
                    //cout << num << endl;
                    if (rows == 1) colms = vals.size();
                    matrixes.emplace(name, Matrix<double>{rows, colms, name, vals});

                    //cout << Matrix<double>{rows, colms, name, vals} << endl;

                }
                else if (strokes[i][nchar] == 't') {

                    nchar += 2;

                    while (strokes[i][nchar] != ')') {
                        num += strokes[i][nchar];
                        nchar++;
                    }

                    //cout << matrixes.find(name)->second << endl;

                    matrixes.erase(name);
                    matrixes.emplace(name, (matrixes.find(num)->second).MatrixTrans());
                }
                else if (strokes[i][nchar] == 'm' || strokes[i][nchar] == 'v')
                {
                    while (strokes[i][nchar] != ' ' && strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                        num += strokes[i][nchar];
                        nchar++;
                    }
                    if (strokes[i][nchar] == '\n' || strokes[i][nchar] == '\0')
                    {
                        if (name[0] == 'm')
                        {
                            matrixes.erase(name);
                            matrixes.emplace(name, (matrixes.find(num)->second));
                        }
                        else if (name[0] == 'v')
                        {
                            cout << "Вектору нельзя присвоить матрицу. " << endl;
                            std::exit(EXIT_FAILURE);
                        }
                    }
                    else {
                        nchar++;

                        switch (strokes[i][nchar])
                        {
                        case '*':
                            nchar += 2;
                            while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                                num2 += strokes[i][nchar];
                                nchar++;
                            }

                            if (isdigit(num2[0]) || num2[0] == '-')
                            {
                                matrixes.erase(name);
                                matrixes.emplace(name, (matrixes.find(num)->second) * double(stod(num2)));
                            }
                            else
                                switch (num2[0])
                                {
                                case 'm':
                                    matrixes.erase(name);
                                    matrixes.emplace(name, (matrixes.find(num)->second) * (matrixes.find(num2)->second));
                                    break;
                                case 'v':
                                    matrixes.erase(name);
                                    matrixes.emplace(name, (matrixes.find(num)->second) * (matrixes.find(num2)->second));
                                    break;
                                case 'r':
                                    matrixes.erase(name);
                                    matrixes.emplace(name, (matrixes.find(num)->second) * double(fracs.find(num2)->second));
                                    break;
                                default:
                                    cout << "Данной переменной не существует." << endl;
                                    std::exit(EXIT_FAILURE);
                                    break;
                                }

                            break;
                        case '+':
                            nchar += 2;
                            while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                                num2 += strokes[i][nchar];
                                nchar++;
                            }

                            if (isdigit(num2[0]) || num2[0] == '-')
                            {
                                cout << "Нельзя складывать матрицу и число." << endl;
                                std::exit(EXIT_FAILURE);
                            }
                            else
                                switch (num2[0])
                                {
                                case 'm':
                                    matrixes.erase(name);
                                    matrixes.emplace(name, (matrixes.find(num)->second) + (matrixes.find(num2)->second));
                                    break;
                                case 'v':
                                    matrixes.erase(name);
                                    matrixes.emplace(name, (matrixes.find(num)->second) + (matrixes.find(num2)->second));
                                    break;
                                case 'r':
                                    cout << "Нельзя складывать матрицу и число. " << endl;
                                    std::exit(EXIT_FAILURE);
                                    break;
                                default:
                                    cout << "Данной переменной не существует." << endl;
                                    std::exit(EXIT_FAILURE);
                                    break;
                                }

                            break;
                        case '-':
                            nchar += 2;
                            while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                                num2 += strokes[i][nchar];
                                nchar++;
                            }

                            if (isdigit(num2[0]) || num2[0] == '-')
                            {
                                cout << "Нельзя вычитать матрицу и число. " << endl;
                                std::exit(EXIT_FAILURE);
                            }
                            else
                                switch (num2[0])
                                {
                                case 'm':
                                    matrixes.erase(name);
                                    matrixes.emplace(name, (matrixes.find(num)->second) - (matrixes.find(num2)->second));
                                    break;
                                case 'v':
                                    matrixes.erase(name);
                                    matrixes.emplace(name, (matrixes.find(num)->second) - (matrixes.find(num2)->second));
                                    break;
                                case 'r':
                                    cout << "Нельзя вычитать матрицу и число. " << endl;
                                    std::exit(EXIT_FAILURE);
                                    break;
                                default:
                                    cout << "Данной переменной не существует." << endl;
                                    std::exit(EXIT_FAILURE);
                                    break;
                                }

                            break;
                        case '/':
                            nchar += 2;
                            while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                                num2 += strokes[i][nchar];
                                nchar++;
                            }

                            if (isdigit(num2[0]))
                            {
                                matrixes.erase(name);
                                matrixes.emplace(name, (matrixes.find(num)->second) * (1 / double(stod(num2))));
                            }
                            else
                                switch (num2[0])
                                {
                                case 'm':
                                    cout << "Не существует операции деления матрицы на матрицу." << endl;
                                    std::exit(EXIT_FAILURE);
                                    break;
                                case 'v':
                                    cout << "Не существует операции деления матрицы на матрицу." << endl;
                                    std::exit(EXIT_FAILURE);
                                    break;
                                case 'r':
                                    matrixes.erase(name);
                                    matrixes.emplace(name, (matrixes.find(num)->second) * (1 / double(fracs.find(num2)->second)));
                                    break;
                                default:
                                    cout << "Данной переменной не существует." << endl;
                                    std::exit(EXIT_FAILURE);
                                    break;
                                }

                            break;
                        default:
                            cout << "Данной операции не существует." << endl;
                            std::exit(EXIT_FAILURE);
                            break;
                        }
                    }

                }
                else if (strokes[i][nchar] == 'r')
                {
                    while (strokes[i][nchar] != ' ') {
                        num += strokes[i][nchar];
                        nchar++;
                    }
                    nchar++;
                    switch (strokes[i][nchar])
                    {
                    case '*':
                        nchar += 2;
                        while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                            num2 += strokes[i][nchar];
                            nchar++;
                        }

                        if (isdigit(num2[0]) || num2[0] == '-')
                        {
                            cout << "Матрица не может быть равна числу." << endl;
                            std::exit(EXIT_FAILURE);
                        }
                        else
                            switch (num2[0])
                            {
                            case 'm':
                                matrixes.erase(name);
                                matrixes.emplace(name, (matrixes.find(num2)->second) * double(fracs.find(num)->second));
                                break;
                            case 'v':
                                matrixes.erase(name);
                                matrixes.emplace(name, (matrixes.find(num2)->second) * double(fracs.find(num)->second));
                                break;
                            case 'r':
                                cout << "Матрица не может быть равна числу." << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            default:
                                cout << "Данной переменной не существует." << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            }

                        break;
                    case '+':
                        cout << "Нельзя сложить число и матрицу/число. " << endl;
                        std::exit(EXIT_FAILURE);
                        break;
                    case '-':
                        cout << "Нельзя сложить число и матрицу/число. " << endl;
                        std::exit(EXIT_FAILURE);
                        break;
                    case '/':
                        cout << "Нельзя сложить число и матрицу/число. " << endl;
                        std::exit(EXIT_FAILURE);
                        break;
                    }
                }
                else if (isdigit(strokes[i][nchar]) || strokes[i][nchar] == '-')
                {
                    while (strokes[i][nchar] != ' ') {
                        num += strokes[i][nchar];
                        nchar++;
                    }
                    nchar++;

                    switch (strokes[i][nchar])
                    {
                    case '*':
                        nchar += 2;
                        while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                            num2 += strokes[i][nchar];
                            nchar++;
                        }

                        if (isdigit(num2[0]) || num2[0] == '-')
                        {
                            cout << "Нельзя матрице присвоить число. " << endl;
                            std::exit(EXIT_FAILURE);
                        }
                        else
                            switch (num2[0])
                            {
                            case 'm':
                                matrixes.erase(name);
                                matrixes.emplace(name, (matrixes.find(num2)->second) * stod(num));
                                break;
                            case 'v':
                                matrixes.erase(name);
                                matrixes.emplace(name, (matrixes.find(num2)->second) * stod(num));
                                break;
                            case 'r':
                                cout << "Матрица не может быть равна числу. " << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            default:
                                cout << "Данной переменной не существует." << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            }

                        break;
                    case '+':
                        nchar += 2;
                        while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                            num2 += strokes[i][nchar];
                            nchar++;
                        }

                        if (isdigit(num2[0]) || num2[0] == '-')
                        {
                            cout << "Нельзя матрице присвоить число. " << endl;
                            std::exit(EXIT_FAILURE);
                        }
                        else
                            switch (num2[0])
                            {
                            case 'm':
                                cout << "Нельзя складывать матрицу и число. " << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            case 'v':
                                cout << "Нельзя складывать матрицу и число. " << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            case 'r':
                                cout << "Матрица не может быть равна числу. " << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            default:
                                cout << "Данной переменной не существует." << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            }

                        break;
                    case '-':
                        nchar += 2;
                        while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                            num2 += strokes[i][nchar];
                            nchar++;
                        }

                        if (isdigit(num2[0]) || num2[0] == '-')
                        {
                            cout << "Нельзя матрице присвоить число. " << endl;
                            std::exit(EXIT_FAILURE);
                        }
                        else
                            switch (num2[0])
                            {
                            case 'm':
                                cout << "Нельзя вычитать матрицу и число. " << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            case 'v':
                                cout << "Нельзя вычитать матрицу и число. " << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            case 'r':
                                cout << "Матрица не может быть равна числу.  " << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            default:
                                cout << "Данной переменной не существует." << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            }

                        break;
                    case '/':
                        nchar += 2;
                        while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                            num2 += strokes[i][nchar];
                            nchar++;
                        }

                        if (isdigit(num2[0]) || num2[0] == '-')
                        {
                            cout << "Нельзя матрице присвоить число. " << endl;
                            std::exit(EXIT_FAILURE);
                        }
                        else
                            switch (num2[0])
                            {
                            case 'm':
                                cout << "Не существует операции деления матрицы на матрицу." << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            case 'v':
                                cout << "Не существует операции деления матрицы на матрицу." << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            case 'r':
                                cout << "Матрица не может быть равна числу.  " << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            case '-':
                                cout << "Матрица не может быть равна числу.  " << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            default:
                                cout << "Данной переменной не существует." << endl;
                                std::exit(EXIT_FAILURE);
                                break;
                            }

                        break;
                    default:
                        cout << "Данной операции не существует." << endl;
                        std::exit(EXIT_FAILURE);
                        break;
                    }
                }
                else {
                    cout << "Пропущен символ [" << endl;
                    std::exit(EXIT_FAILURE);
                }
            }
        }
        else if (name[0] == 'r') {
            if (!Find(strokes[i], '=')) {
                if (fracs.size() != 0)
                {
                    cout << "-------------------------------------" << endl;
                    cout << fracs.find(name)->second << endl;
                }
            }
            else {
                if (strokes[i][nchar] != ' ')
                {
                    cout << "Не найден пробел." << endl;
                    std::exit(EXIT_FAILURE);
                }
                if (strokes[i][nchar + 1] != '=')
                {
                    cout << "Не найден знак равенства." << endl;
                    std::exit(EXIT_FAILURE);
                }
                if (strokes[i][nchar + 2] != ' ')
                {
                    cout << "Не найден пробел." << endl;
                    std::exit(EXIT_FAILURE);
                }
                nchar += 3;
                if (!isdigit(strokes[i][nchar]) && strokes[i][nchar] != '-' && strokes[i][nchar] != 'r')
                {
                    cout << "Неправильно введена дробь. " << endl;
                    std::exit(EXIT_FAILURE);
                }
                else {
                    while (strokes[i][nchar] != ' ' && strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                        num += strokes[i][nchar];
                        nchar++;
                    }
                    if (strokes[i][nchar] == '\n' || strokes[i][nchar] == '\0')
                    {
                        if (name[0] == 'r')
                        {
                            fracs.erase(name);
                            fracs.emplace(name, (fracs.find(num)->second));
                        }
                        else if (name[0] == 'm' || name[0] == 'v')
                        {
                            cout << "Рациональной дроби нельзя присвоить матрицу/вектор." << endl;
                            std::exit(EXIT_FAILURE);
                        }
                    }
                    else {
                        nchar++;
                        if (strokes[i][nchar] != '/') {
                            cout << "Неправильно введена дробь. " << endl;
                            std::exit(EXIT_FAILURE);
                        }
                        else {
                            nchar += 2;
                            while (strokes[i][nchar] != '\n' && strokes[i][nchar] != '\0') {
                                num2 += strokes[i][nchar];
                                nchar++;
                            }
                            fracs.emplace(name, Frac{ stoi(num), stoi(num2) });
                        }
                    }

                }
            }
        }
        else {
            cout << "Вы ввели неверное имя переменной." << endl;
            std::exit(EXIT_FAILURE);
        }
    }
}
