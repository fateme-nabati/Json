#include "../header/json.hpp"
using namespace std;
vector<string> pathc1;
static int numberc = 0;
string returnType(string &OtherCommands, const string &json);
string searchc(const string &json, int &countj, int &flag);
string Bracec(const string &json, int &countj, int &flag);
string Bracketsc(const string &json, int &countj, int &flag);
string returnValue(string &OtherCommands, const string &json);
string searchgvc(const string &json, int &countj, int &flag);
string Bracegvc(const string &json, int &countj, int &flag);
string Bracketsgvc(const string &json, int &countj, int &flag);
void compare(string &OtherCommands, const string &json)
{
    pathc1.clear();
    string command1 = "", command2 = "";
    numberc = 0;
    int counto = 0, flag = 0;
    int countj = 0;
    string str;
    if (json == "")
    {
        cerr << ">> SyntaxError: Your Json data is not valid. Please go to the data set command " << endl;
    }
    else
    {
        crossing(OtherCommands, counto);
        str = "";
        int size = OtherCommands.size();
        size -= 2;
        if (OtherCommands[size] == '.')
            cerr << ">> SyntaxError: your Json data is not valid" << endl;
        else
        {
            while (OtherCommands[counto] != ' ' && OtherCommands[counto] != '\t' && OtherCommands[counto] != '\n' && OtherCommands[counto])
            {
                command1 += OtherCommands[counto];
                ++counto;
            }
            crossing(OtherCommands, counto);
            while (OtherCommands[counto] != '\n' && OtherCommands[counto] != '\t' && OtherCommands[counto] != ' ' && OtherCommands[counto])
            {
                command2 += OtherCommands[counto];
                ++counto;
            }
        }
    }
    string result1, result2;
    if (command1 == "" || command2 == "")
        cerr << ">> SyntaxError : Your command is not possible " << endl;
    else
    {
        result1 = returnType(command1, json);
        result2 = returnType(command2, json);
        if (result1 == "failed" || result2 == "failed")
            cerr << ">> TypeError: Cannot compare at least one of the data is not possible" << endl;

        else if (result1.substr(2) != result2.substr(2))
        {
            cerr << ">> TypeError: Cannot compare " << result1.substr(2) << " with " << result2.substr(2) << endl;
        }
        else
        {
            if (result1 != "> Number" && result2 != "> Number")
            {
                cerr << ">> TypeError: Cannot compare 2" << result1.substr(2) << " with " << result2.substr(2) << endl;
            }
            else
            {
                result1 = returnValue(command1, json);
                result2 = returnValue(command2, json);
                result1 = result1.substr(2);
                result2 = result2.substr(2);
                float n1, n2;
                stringstream(result1) >> n1;
                stringstream(result2) >> n2;
                if (n1 > n2)
                    cout << "> Left" << endl;
                else if (n2 > n1)
                    cout << "> Right" << endl;
                else
                {
                    cout << "> Equals" << endl;
                }
            }
        }
    }
}
/**********************************************************/
string returnType(string &OtherCommands, const string &json)
{
    pathc1.clear();
    numberc = 0;
    int counto = 0, flag = 0;
    int countj = 0;
    string str;
    if (json == "")
    {
        cerr << ">> Your Json data is not valid. Please go to the data set command " << endl;
        return "failed";
    }
    else
    {
        crossing(OtherCommands, counto);
        str = "";
        int size = OtherCommands.size();
        size -= 1;
        if (OtherCommands[size] == '.')
        {
            cerr << ">> syntaxError: your Json data is not valid" << endl;
        }
        else
        {
            OtherCommands += " ";
            while (OtherCommands[counto])
            {

                while (OtherCommands[counto] != '.' && OtherCommands[counto] != '\t' && OtherCommands[counto] != '\n' &&
                       OtherCommands[counto] != ' ' && OtherCommands[counto] && OtherCommands[counto])
                {
                    str += OtherCommands[counto];
                    ++counto;
                }
                ++counto;
                pathc1.push_back(str);
                ++numberc;
                str = "";
            }
        }
        string j = searchc(json, countj, flag);
        return j;
    }
}
/********************************************************/
string searchc(const string &json, int &countj, int &flag)
{
    string x;
    numberc = 0;
    crossingjson(json, countj);
    if (json[countj] == '[')
    {
        x = "";
        x = Bracketsc(json, countj, flag);
        return x;
    }
    else if (json[countj] == '{')
    {
        x = "";
        x = Bracec(json, countj, flag);
        return x;
    }
    return "failed";
}
/**********************************************************/
string Bracec(const string &json, int &countj, int &flag)
{
    string str = "";
    string x;
    if (pathc1[numberc] >= "0" && pathc1[numberc] <= "9")
        return ">>  InvalidArgumentError: Cannot find the given path ";
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
                ++countj;
            }
            ++countj;
            while (json[countj] != '\"' && (num2 != num1) && (countj < json.size()))
            {
                str += json[countj];
                ++countj;
            }
            ++countj;
            crossingjson(json, countj);
            if (str == pathc1[numberc] && json[countj] == ':' && (countj < json.size()))
            {
                flag2 = 1;
                break;
            }
            ++countj;
            crossingjson(json, countj);
        }
        if (flag2 == 1)
        {
            ++countj;
            crossingjson(json, countj);
            if (pathc1.size() == (numberc + 1))
            {
                if (json[countj] == '{')
                {
                    x = "> Object";
                    return x;
                }
                else if (json[countj] == '[')
                {
                    x = "> Array";
                    return x;
                }
                else if (json[countj] == '\"')
                {
                    x = "> String";
                    return x;
                }
                else if (json[countj] == 't' || json[countj] == 'f')
                {
                    x = "> Boolean";
                    return x;
                }
                else if (json[countj] == 'n')
                {
                    x = "> Null";
                    return x;
                }
                else if ((json[countj] >= '0' && json[countj] <= '9') || (json[countj] == '-'))
                {
                    x = "> Number";
                    return x;
                }
            }
            else
            {
                if (json[countj] == 'n' || json[countj] == 't' || json[countj] == 'f' ||
                    (json[countj] >= '0' && json[countj] <= '9') || (json[countj] == '-') || json[countj] == '\"')
                {
                    return ">> Your request is impossible ";
                }
                else
                {
                    ++numberc;
                    if (json[countj] == '[')
                    {
                        return Bracketsc(json, countj, flag);
                    }
                    else if (json[countj] == '{')
                    {
                        return Bracec(json, countj, flag);
                    }
                }
            }
        }
        else
        {
            return ">> Error : Your request was not found ";
        }
    }
    return "faild";
}
/**********************************************************/
string Bracketsc(const string &json, int &countj, int &flag)
{
    while (true)
    {
        ++countj;
        crossingjson(json, countj); //boolean_number_string
        if ((json[countj] == '\"' ||
             ((json[countj] >= '0' && json[countj] <= '9') || json[countj] == '-') ||
             (json.substr(countj, 4) == "true" || json.substr(countj, 5) == "false")))
        {
            if (!(pathc1[numberc] >= "0" && pathc1[numberc] <= "9"))
                return ">>  InvalidArgumentError: Cannot find the given path ";
            else
            {
                int number2, i = 0;
                stringstream geek(pathc1[numberc]);
                geek >> number2;
                while ((i < number2) && json[countj])
                {
                    while (json[countj] != ',')
                    {
                        ++countj;
                    }
                    ++countj;
                    ++i;
                    if (i < (number2 - 1) && countj >= (json.size() - 1))
                    {
                        throw out_of_range(">> TypeError: Your request is out of range");
                    }
                }
                crossingjson(json, countj);
                if ((json[countj] >= '0' && json[countj] <= '9') || (json[countj] == '-'))
                {
                    return "> Number";
                }
                else if (json.substr(countj, 4) == "true" || json.substr(countj, 5) == "false")
                {
                    return "> Boolean";
                }
                else if (json[countj] == '\"')
                {
                    return "> String";
                }
                else if (json.substr(countj, 4) == "null")
                {
                    return "> Null";
                }
            }
            break;
        }
        else if (json[countj] == '{')
        {
            if (!(pathc1[numberc] >= "0" && pathc1[numberc] <= "9"))
                return ">>  InvalidArgumentError: Cannot find the given path ";
            else
            {
                int number1, i = 0;
                stringstream geek(pathc1[numberc]);
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
                if (pathc1.size() == (numberc + 1))
                {
                    if (json[countj] == '{')
                        return "> Object";
                    else if (json[countj] == 'n')
                    {
                        return "> Null";
                    }
                }
                else
                {
                    ++numberc;
                    return Bracec(json, countj, flag);
                }
            }
            break;
        }
        else if (json[countj] == ']')
        {
            return ">>  InvalidArgumentError: Cannot find the given path ";
            break;
        }
        else if (json[countj] == '[')
        {
            if (!(pathc1[numberc] >= "0" && pathc1[numberc] <= "9"))
                return ">>  InvalidArgumentError: Cannot find the given path ";
            else
            {
                int number1, i = 0;
                stringstream geek(pathc1[numberc]);
                geek >> number1;
                crossingjson(json, countj);
                for (size_t i = 0; (i < number1 && json[countj]); ++i)
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
                        return ">> Error : Your request is impossible ";
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
                            return "Error: We are finished";
                        }
                    }

                } //{
                if (i < (number1 - 1))
                {
                    throw out_of_range(">> TypeError: Your request is out of range");
                }
                if (pathc1.size() == (numberc + 1))
                {
                    if (json[countj] == '[')
                        return "> Array";
                    else if (json[countj] == 'n')
                    {
                        return "> Null";
                    }
                }
                else
                {
                    ++numberc;
                    return Bracketsc(json, countj, flag);
                }
            }
            break;
        }
        else if (json.substr(countj, 4) == "null")
        {
            if (pathc1[0] == "0")
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
                stringstream(pathc1[0]) >> num;
                --num;
                pathc1[0] = to_string(num);
            }
        }
    }
    return "failed";
}
/*********************************************************/
string returnValue(string &OtherCommands, const string &json)
{
    pathc1.clear();
    numberc = 0;
    int counto = 0, flag = 0;
    int countj = 0;
    string str;
    if (json == "")
    {
        cerr << ">> Your Json data is not valid. Please go to the data set command " << endl;
        return "failed";
    }
    else
    {
        crossing(OtherCommands, counto);
        str = "";
        int size = OtherCommands.size();
        size -= 1;
        if (OtherCommands[size] == '.')
        {
            cerr << ">> syntaxError: your Json data is not valid" << endl;
            return "failed";
        }
        else
        {
            OtherCommands += " ";
            while (OtherCommands[counto] != ' ')
            {

                while (OtherCommands[counto] != '.' && OtherCommands[counto] != '\t' && OtherCommands[counto] != '\n' &&
                       OtherCommands[counto] != ' ' && OtherCommands[counto] && OtherCommands[counto])
                {
                    str += OtherCommands[counto];
                    ++counto;
                }
                ++counto;
                pathc1.push_back(str);
                ++numberc;
                str = "";
            }
        }
        string j = searchgvc(json, countj, flag);
        return j;
    }
}
/*********************************************************/
string searchgvc(const string &json, int &countj, int &flag)
{
    string x;
    numberc = 0;
    crossingjson(json, countj);
    if (json[countj] == '[')
    {
        x = "";
        x = Bracketsgvc(json, countj, flag);
        return x;
    }
    else if (json[countj] == '{')
    {
        x = "";
        x = Bracegvc(json, countj, flag);
        return x;
    }
    return "failed";
}
/**********************************************************/
string Bracegvc(const string &json, int &countj, int &flag)
{
    string str = "";
    if (pathc1[numberc] >= "0" && pathc1[numberc] <= "9")
    {
        cerr << ">>  InvalidArgumentError: Cannot find the given path " << endl;
        return "failed 1";
    }
    else
    {
        ++countj;
        crossingjson(json, countj);
        int num1 = 1, num2 = 0;
        int flag2 = 0;
        while (num1 != num2)
        {
            str = "";
            while (json[countj] != '\"' && (num2 != num1))
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
                while (json[countj] != '\"' && (num2 != num1))
                {
                    str += json[countj];
                    ++countj;
                }
                ++countj;
                crossingjson(json, countj);
                if (str == pathc1[numberc] && json[countj] == ':')
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
            if (pathc1.size() == (numberc + 1))
            {
                if (json[countj] == '{')
                    return "> Object";
                else if (json[countj] == '[')
                {
                    return "> Array";
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
                    return ("> " + s);
                }
                else if (json[countj] == 't' || json[countj] == 'f')
                {
                    if (json[countj] == 't')
                        return "> true";
                    else
                        return "> false";
                }
                else if (json[countj] == 'n')
                {
                    return "> null";
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
                    return ("> " + s);
                }
            }
            else
            {
                if (json[countj] == 'n' || json[countj] == 't' || json[countj] == 'f' ||
                    (json[countj] >= '0' && json[countj] <= '9') || (json[countj] == '-') || json[countj] == '\"')
                {
                    cerr << ">> Your request is impossible " << endl;
                    return "failed 2";
                }
                else
                {
                    ++numberc;
                    if (json[countj] == '[')
                    {
                        return Bracketsgvc(json, countj, flag);
                    }
                    else if (json[countj] == '{')
                    {
                        return Bracegvc(json, countj, flag);
                    }
                }
            }
        }
        else
        {
            cerr << ">> Your request was not found " << endl;
            return "failed";
        }
    }
    return "failed";
}
/**********************************************************/
string Bracketsgvc(const string &json, int &countj, int &flag)
{
    while (true)
    {
        ++countj;
        crossingjson(json, countj); //boolean_number_string
        if ((json[countj] == '\"' ||
             ((json[countj] >= '0' && json[countj] <= '9') || json[countj] == '-') ||
             (json.substr(countj, 4) == "true" || json.substr(countj, 5) == "false")))
        {
            if (!(pathc1[numberc] >= "0" && pathc1[numberc] <= "9"))
            {
                cerr << ">>  InvalidArgumentError: Cannot find the given pathc1 " << endl;
                return "failed";
            }
            else
            {
                int number2, i = 0;
                stringstream geek(pathc1[numberc]);
                geek >> number2;
                while ((i < number2) && json[countj])
                {
                    while (json[countj] != ',')
                    {
                        ++countj;
                    }
                    ++countj;
                    ++i;
                    if (i < (number2 - 1) && countj >= (json.size() - 1))
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
                    return ("> " + s);
                }
                else if (json.substr(countj, 4) == "true" || json.substr(countj, 5) == "false")
                {
                    if (json[countj] == 't')
                        return "true";
                    else
                        return "false";
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
                    return ("> " + s);
                }
                else if (json.substr(countj, 4) == "null")
                {
                    return "null";
                }
            }
            break;
        }
        else if (json[countj] == '{')
        {
            if (!(pathc1[numberc] >= "0" && pathc1[numberc] <= "9"))
            {
                cerr << ">>  InvalidArgumentError: Cannot find the given path " << endl;
                return "failed";
            }
            else
            {
                int number1, i = 0;
                stringstream geek(pathc1[numberc]);
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
                if (pathc1.size() == (numberc + 1))
                {
                    if (json[countj] == '{')
                        return "> Object";
                    else if (json[countj] == 'n')
                    {
                        return "> null";
                    }
                }
                else
                {
                    ++numberc;
                    return Bracegvc(json, countj, flag);
                }
            }
            break;
        }
        else if (json[countj] == ']')
        {
            cerr << ">>  InvalidArgumentError: Cannot find the given path " << endl;
            return "failed";
            break;
        }
        else if (json[countj] == '[')
        {
            if (!(pathc1[numberc] >= "0" && pathc1[numberc] <= "9"))
            {
                cerr << ">>  InvalidArgumentError: Cannot find the given path " << endl;
                return "failed";
            }
            else
            {
                int number1, i = 0;
                stringstream geek(pathc1[numberc]);
                geek >> number1;
                crossingjson(json, countj);
                for (size_t i = 0; (i < number1 && json[countj]); ++i)
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
                        return "failed";
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
                            cerr << ">> Error: We are finished" << endl;
                            return "failed";
                        }
                    }

                } //{
                if (i < (number1 - 1))
                {
                    throw out_of_range(">> TypeError: Your request is out of range");
                }

                if (pathc1.size() == (numberc + 1))
                {
                    if (json[countj] == '[')
                        return "> Array";
                    else if (json[countj] == 'n')
                    {
                        return "> null";
                    }
                }
                else
                {
                    ++numberc;
                    return Bracketsgvc(json, countj, flag);
                }
            }
            break;
        }
        else if (json.substr(countj, 4) == "null")
        {
            if (pathc1[0] == "0")
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
                stringstream(pathc1[0]) >> num;
                --num;
                pathc1[0] = to_string(num);
            }
        }
    }
    return "failed";
}
