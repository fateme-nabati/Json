#include "../header/json.hpp"
using namespace std;
vector<string> pathgv;
static int numbergv = 0;
void searchgv(const string &json, int &countj, int &flag);
void Bracegv(const string &json, int &countj, int &flag);
void Bracketsgv(const string &json, int &countj, int &flag);
void getValue(string &OtherCommands, const string &json)
{
    pathgv.clear();
    numbergv = 0;
    int counto = 0, flag = 0;
    int countj = 0;
    string str;
    if (json == "")
    {
        cerr << ">> Your Json data is not valid. Please go to the data set command " << endl;
    }
    else
    {
        crossing(OtherCommands, counto);
        str = "";
        int size = OtherCommands.size();
        size -= 2;
        if (OtherCommands[size] == '.')
            cerr << ">> syntaxError: your Json data is not valid" << endl;
        else
        {
            while (OtherCommands[counto])
            {

                while (OtherCommands[counto] != '.' && OtherCommands[counto] != '\t' && OtherCommands[counto] != '\n' &&
                       OtherCommands[counto] != ' ' && OtherCommands[counto])
                {
                    str += OtherCommands[counto];
                    ++counto;
                }
                ++counto;
                pathgv.push_back(str);
                ++numbergv;
                str = "";
            }
            searchgv(json, countj, flag);
        }
    }
}
void searchgv(const string &json, int &countj, int &flag)
{
    numbergv = 0;
    crossingjson(json, countj);
    if (json[countj] == '[')
    {
        Bracketsgv(json, countj, flag);
    }
    else if (json[countj] == '{')
    {
        Bracegv(json, countj, flag);
    }
}
/****************************************************************************/
void Bracegv(const string &json, int &countj, int &flag)
{
    string str = "";
    if (pathgv[numbergv] >= "0" && pathgv[numbergv] <= "9")
        cerr << ">>  InvalidArgumentError: Cannot find the given path " << endl;
    else
    {
        ++countj;
        crossingjson(json, countj);
        int num1 = 1, num2 = 0;
        int flag2 = 0;
        while (num1 != num2 && (countj < json.size()))
        {
            str = "";
            while (json[countj] != '\"' && (num2 != num1) && (countj < json.size()))
            {
                if (json[countj] == '}')
                {
                    ++num2;
                }
                else if (json[countj] != '{')
                    ++num1;
                if (num1 == num2)
                {
                    break;
                }
                ++countj;
                crossingjson(json, countj);
            }
            ++countj;
            if (num1 == num2)
            {
                break;
            }
            else
            {
                while (json[countj] != '\"' && (num2 != num1) && (countj < json.size()))
                {
                    str += json[countj];
                    ++countj;
                }
                ++countj;
                crossingjson(json, countj);
                if (str == pathgv[numbergv] && json[countj] == ':' && (countj < json.size()))
                {
                    flag2 = 1;
                    break;
                }
                ++countj;
                crossingjson(json, countj);
            }
        }
        if (flag2 == 1)
        {
            ++countj;
            crossingjson(json, countj);
            if (pathgv.size() == (numbergv + 1))
            {
                if (json[countj] == '{')
                    cout << "> Object" << endl;
                else if (json[countj] == '[')
                {
                    cout << "> Array" << endl;
                }
                else if (json[countj] == '\"')
                {
                    string s = "";
                    s += '\"';
                    ++countj;
                    while (json[countj] != '\"')
                    {
                        s += json[countj];
                        ++countj;
                    }
                    s += '\"';
                    cout << "> " << s << endl;
                }
                else if (json[countj] == 't' || json[countj] == 'f')
                {
                    if (json[countj] == 't')
                        cout << "> true" << endl;
                    else
                        cout << "> false" << endl;
                }
                else if (json[countj] == 'n')
                {
                    cout << "> null" << endl;
                }
                else if ((json[countj] >= '0' && json[countj] <= '9') || (json[countj] == '-'))
                {
                    string s = "";
                    while (json[countj] != ' ' && json[countj] != '\t' &&
                           json[countj] != '\n' && json[countj] != ',' && json[countj] != '}')
                    {
                        s += json[countj];
                        ++countj;
                    }
                    cout << "> " << s << endl;
                }
            }
            else
            {
                if (json[countj] == 'n' || json[countj] == 't' || json[countj] == 'f' ||
                    (json[countj] >= '0' && json[countj] <= '9') || (json[countj] == '-') || json[countj] == '\"')
                    cerr << ">> Your request is impossible " << endl;
                else
                {
                    ++numbergv;
                    if (json[countj] == '[')
                    {
                        Bracketsgv(json, countj, flag);
                    }
                    else if (json[countj] == '{')
                    {
                        Bracegv(json, countj, flag);
                    }
                }
            }
        }
        else
        {
            cerr << ">> Your request was not found " << endl;
        }
    }
}
/****************************************************************************/
void Bracketsgv(const string &json, int &countj, int &flag)
{
    while (true)
    {
        ++countj;
        crossingjson(json, countj); //boolean_number_string
        if ((json[countj] == '\"' ||
             ((json[countj] >= '0' && json[countj] <= '9') || json[countj] == '-') ||
             (json.substr(countj, 4) == "true" || json.substr(countj, 5) == "false")))
        {
            if (!(pathgv[numbergv] >= "0" && pathgv[numbergv] <= "9"))
                cerr << ">>  InvalidArgumentError: Cannot find the given pathgv " << endl;
            else
            {
                int number2, i = 0;
                stringstream geek(pathgv[numbergv]);
                geek >> number2;
                while ((i < number2) && json[countj])
                {
                    while (json[countj] != ',')
                    {
                        ++countj;
                    }
                    ++countj;
                    ++i;
                    if (i < (number2 - 1) && countj > (json.size() - 1))
                    {
                        throw out_of_range(">> TypeError: Your request is out of range");
                    }
                }
                crossingjson(json, countj);
                if ((json[countj] >= '0' && json[countj] <= '9') || (json[countj] == '-'))
                {
                    string s = "";
                    while (json[countj] != ' ' && json[countj] != '\t' &&
                           json[countj] != '\n' && json[countj] != ',' && json[countj] != ']')
                    {
                        s += json[countj];
                        ++countj;
                    }
                    cout << "> " << s << endl;
                }
                else if (json.substr(countj, 4) == "true" || json.substr(countj, 5) == "false")
                {
                    if (json[countj] == 't')
                        cout << "> true " << endl;
                    else
                        cout << "> false " << endl;
                }
                else if (json[countj] == '\"')
                {
                    string s = "";
                    s += '\"';
                    ++countj;
                    while (json[countj] != '\"')
                    {
                        s += json[countj];
                        ++countj;
                    }
                    s += '\"';
                    cout << "> " << s << endl;
                }
                else if (json.substr(countj, 4) == "null")
                {
                    cout << "> null" << endl;
                }
            }
            break;
        }
        else if (json[countj] == '{')
        {
            if (!(pathgv[numbergv] >= "0" && pathgv[numbergv] <= "9"))
                cerr << ">>  InvalidArgumentError: Cannot find the given path " << endl;
            else
            {
                int number1, i = 0;
                stringstream geek(pathgv[numbergv]);
                geek >> number1;
                crossingjson(json, countj);
                for (size_t i = 0; (i < number1 && json[countj]); ++i)
                {
                    if (json.substr(countj, 4) == "null")
                    {
                        countj += 4;
                        ++countj;
                        crossingjson(json, countj);
                    }
                    else
                    {
                        int num1 = 0, num2 = 0;
                        if (countj == '{')
                            ++num1;
                        crossingjson(json, countj);
                        while (true)
                        {
                            while (json[countj] != '{' && json[countj] != '}')
                                ++countj;
                            if (json[countj] == '{' || json[countj] == '}')
                            {
                                if (json[countj] == '}')
                                {
                                    ++num2;
                                    if (num1 == num2)
                                        break;
                                }
                                else
                                {
                                    ++num1;
                                }
                            }
                            ++countj;
                        }
                        ++countj; //'}'
                        crossingjson(json, countj);
                        ++countj;
                        crossingjson(json, countj);
                    }
                } //{
                if (pathgv.size() == (numbergv + 1))
                {
                    if (json[countj] == '{')
                        cout << "> Object" << endl;
                    else if (json[countj] == 'n')
                    {
                        cout << "> null" << endl;
                    }
                }
                else
                {
                    ++numbergv;
                    Bracegv(json, countj, flag);
                }
            }
            break;
        }
        else if (json[countj] == ']')
        {
            cerr << ">>  InvalidArgumentError: Cannot find the given path " << endl;
            break;
        }
        else if (json[countj] == '[')
        {
            if (!(pathgv[numbergv] >= "0" && pathgv[numbergv] <= "9"))
                cerr << ">>  InvalidArgumentError: Cannot find the given path " << endl;
            else
            {
                int number1, i = 0;
                stringstream geek(pathgv[numbergv]);
                geek >> number1;
                crossingjson(json, countj);
                for ( i = 0; (i < number1 && json[countj]); ++i)
                {
                    if (json.substr(countj, 4) == "null")
                    {
                        countj += 4;
                        crossingjson(json, countj);
                    }
                    else
                    {
                        int num1 = 0, num2 = 0;
                        if (countj == '[')
                            ++num1;
                        crossingjson(json, countj);
                        while (true)
                        {
                            while (json[countj] != '[' && json[countj] != ']')
                                ++countj;
                            if (json[countj] == '[' || json[countj] == ']')
                            {
                                if (json[countj] == ']')
                                {
                                    ++num2;
                                    if (num1 == num2)
                                        break;
                                }
                                else
                                {
                                    ++num1;
                                }
                            }
                            ++countj;
                        }
                        ++countj; //']'}
                        crossingjson(json, countj);
                    }
                    if (json[countj] != ',' && json[countj] != ']')
                    {
                        cerr << ">> Error : Your request is impossible " << endl;
                    }
                    else
                    {
                        if (json[countj] == ',')
                        {
                            ++countj;
                            crossingjson(json, countj);
                        }
                        else
                        {
                            cout << "Error: We are finished" << endl;
                        }
                    }

                } //{
                if (i < (number1 - 1))
                {
                    throw out_of_range(">> TypeError: Your request is out of range");
                }
                if (pathgv.size() == (numbergv + 1))
                {
                    if (json[countj] == '[')
                        cout << "> Array" << endl;
                    else if (json[countj] == 'n')
                    {
                        cout << "> null" << endl;
                    }
                }
                else
                {
                    ++numbergv;
                    Bracketsgv(json, countj, flag);
                }
            }
            break;
        }
        else if (json.substr(countj, 4) == "null")
        {
            if (pathgv[0] == "0")
            {
                cout << "> Null" << endl;
                break;
            }
            else
            {
                countj += 4;
                crossingjson(json, countj);
                if (json[countj] == ']')
                {
                    break;
                }
                if (json[countj] != ',')
                {
                    cerr << ">>  SyntaxError: after null it did not end in , or ]" << endl;
                    break;
                }
                int num;
                stringstream(pathgv[0]) >> num;
                --num;
                pathgv[0] = to_string(num);
                cout << num << endl;
            }
        }
    }
}
