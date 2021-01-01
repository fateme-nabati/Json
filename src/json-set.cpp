#include "../header/json.hpp"
using namespace std;
string json ; /*"{\"z\":  20 ,\"f\" : {\"l\": {\"o\" : [null]} , \"p\" : -9 },\"k\" :null,  \"mina\" : 80} "*/ /*"[null,{\"l\" : -0.9, \"p\" :false},null,{\"u\" : {\"nma\" : 20}}]"*//* "{\"m\" : [[],[9,0],null],\"n\" : [-0.78] }";*/
void stringBrackets(string &, int &, int &);
void numberBrackets(string &, int &, int &);
void crossingSpaces(string &, int &);
void objectBrackets(string &, int &, int &);
void boolBrackets(string &, int &, int &);
void object(string &, int &, int &);
void arrayBrackets(string &, int &, int &);
void menuBrackets(string &, int &, int &);
void check(string &, int &, int &, int &);
/*******************************************************************************/
void setData(string &OtherCommands)
{
    int count = 0;
    crossingSpaces(OtherCommands, count);
    int flag = 0;
    if (OtherCommands[count] == '[')
    {
        menuBrackets(OtherCommands, count, flag);
    }
    else if (OtherCommands[count++] == '{')
    {
        object(OtherCommands, count, flag);
    }
    else
    {
        cerr << ">> SyntaxError: Expect to enter object or array" << endl;
    }
}
/*******************************************************************************/
//menu
void commandFunc(string &MainCommand, string &OtherCommands)
{
    if (MainCommand == "set-data")
    {
        setData(OtherCommands);
    }
    else if (MainCommand == "get-value")
    {
        try
        {
            getValue(OtherCommands, json);
        }
        catch (out_of_range &s)
        {
            cerr << s.what() << endl;
        }
    }
    else if (MainCommand == "get-type")
    {
        try
        {
            getType(OtherCommands, json);
        }
        catch (out_of_range &s)
        {
            cerr << s.what() << endl;
        }
    }
    else if (MainCommand == "compare")
    {
        try
        {
            compare(OtherCommands, json);
        }
        catch (out_of_range &s)
        {
            cerr << ">> " << s.what() << endl;
        }
    }
    else if (MainCommand == "calculate")
    {
        try
        {
            calculate(OtherCommands, json);
        }
        catch (out_of_range &s)
        {
            cerr << s.what() << endl;
        }
    }
    else
    {
        cerr << ">> SyntaxError: Your request is not valid. Please try again " << endl;
    }
}
/*******************************************************************************/
// ignore white space
void crossingSpaces(string &OtherCommands, int &count)
{
    while (OtherCommands[count] == ' ' || OtherCommands[count] == '\n' || OtherCommands[count] == '\t')
    {
        ++count;
    }
}
/*******************************************************************************/
//function for string brackets -> ["mina","yaghoubi","computer"]
void stringBrackets(string &OtherCommands, int &count, int &flag)
{
    while (OtherCommands[count] != ']')
    {
        if (OtherCommands[count] == '\"')
            ++count;
        crossingSpaces(OtherCommands, count);
        if (OtherCommands.substr(count, 4) == "null")
            count += 3;
        else
        {
            while (OtherCommands[count] != '\"' && (count < OtherCommands.size()))
            {
                ++count;
            }
        }
        if (count == (OtherCommands.size() - 1))
        {
            cerr << ">>  SyntaxError: This data is not valid" << endl;
            flag = 1;
            return;
        }
        else
        {
            ++count;
            crossingSpaces(OtherCommands, count);
            if (OtherCommands[count] != ',' && OtherCommands[count] != ']')
            {
                cerr << ">> SyntaxError: after\" it did not end in , or ] " << endl;
                flag = 1;
                break;
                return;
            }
            if (OtherCommands[count] != ']')
            {
                ++count;
                crossingSpaces(OtherCommands, count);
                if (OtherCommands[count] != '\"' && (OtherCommands.substr(count, 4) != "null"))
                {
                    cerr << ">> SyntaxError: Because after \',\' it did not end in \"" << endl;
                    flag = 1;
                    break;
                }
            }
        }
    }
    if (flag != 1)
    {
        json = OtherCommands;
    }
}
/*******************************************************************************/
//function for number brackets -> [7,9,0,-0.9]
void numberBrackets(string &OtherCommands, int &count, int &flag)
{
    while (OtherCommands[count] != ']')
    {
        int dot = 0;
        crossingSpaces(OtherCommands, count);
        if (OtherCommands.substr(count, 4) == "null")
        {
            count += 4;
        }
        else
        {
            int place1, place2;
            if (OtherCommands[count] == '-')
            {
                place1 = count + 1;
            }
            else
            {
                place1 = count;
            }
            ++count;
            while ((OtherCommands[count] >= '0' && OtherCommands[count] <= '9') || OtherCommands[count] == '.')
            {
                if (OtherCommands[count] == '.')
                    ++dot;
                ++count;
            }
            place2 = count - 1;
            if (dot > 1 || (OtherCommands[place1] == '.' || OtherCommands[place2] == '.'))
            {
                flag = 1;
                cerr << ">> SyntaxError: Your Json data structure is invalid " << endl;
                break;
                return;
            }
        }
        crossingSpaces(OtherCommands, count);
        if (OtherCommands[count] != ',' && OtherCommands[count] != ']')
        {
            cerr << ">>  SyntaxError: after dgit number it did not end in , or ]" << endl;
            flag = 1;
            break;
            return;
        }
        if (OtherCommands[count] != ']')
        {
            ++count;
            crossingSpaces(OtherCommands, count);
            if ((OtherCommands[count] < '0' && OtherCommands[count] > '9' && (OtherCommands.substr(count, 4) != "null") && OtherCommands[count] != '-'))
            {
                cerr << ">> SyntaxError: Because after \',\' it did not end in dgit number " << endl;
                flag = 1;
                break;
                return;
            }
        }
    }
    if (flag != 1)
    {
        json = OtherCommands;
    }
}
/*******************************************************************************/
//function for object brackets -> [{},{"name":"mina","stn":98123580413}]
void objectBrackets(string &OtherCommands, int &count, int &flag)
{
    crossingSpaces(OtherCommands, count);
    while (OtherCommands[count] != ']')
    {
        int num1 = 1, num2 = 0, flag = 0;
        if (OtherCommands.substr(count, 4) == "null")
        {
            count += 4;
            crossingSpaces(OtherCommands, count);
            if (OtherCommands[count] != ']' && OtherCommands[count] != ',')
            {
                cerr << ">> SyntaxError: after data it did not end in , or ] " << endl;
                flag = 1;
                break;
                return;
            }
            else
            {
                if (OtherCommands[count] != ']')
                    ++count;
                crossingSpaces(OtherCommands, count);
            }
        }
        else
        {
            ++count;
            crossingSpaces(OtherCommands, count);
            if (OtherCommands[count] == '}')
            {
                //++count;
            }
            else
            {
                while (num1 != num2)
                {

                    if (OtherCommands[count] == '}')
                    {
                        //++count;
                    }
                    crossingSpaces(OtherCommands, count);
                    if (OtherCommands.substr(count, 4) == "null")
                    {
                        count += 4;
                        crossingSpaces(OtherCommands, count);
                        if (OtherCommands[count] != '}' && OtherCommands[count] != ',')
                        {
                            cerr << ">> SyntaxError: after data it did not end in , or } " << endl;
                            flag = 1;
                            break;
                            return;
                        }
                        else
                        {
                            if (OtherCommands[count] == '}')
                                ++num2;
                            else
                            {
                                ++count;
                                crossingSpaces(OtherCommands, count);
                            }
                        }
                    }
                    else
                    {
                        if (OtherCommands[count] != '\"')
                        {
                            cerr << ">> SyntaxError: Your data object structure is not valid " << endl;
                            flag = 1;
                            break;
                            return;
                        }
                        else
                        {
                            if (OtherCommands[count] == '}')
                                ++num2;
                            else
                            {
                                ++count;
                                while (OtherCommands[count] != '\"' && count < (OtherCommands.size()))
                                {
                                    ++count;
                                }
                                if (count == (OtherCommands.size() - 1))
                                {
                                    cerr << ">> SyntaxError: This data is not valid" << endl;
                                    flag = 1;
                                    break;
                                    return;
                                }
                                else
                                {
                                    ++count;
                                    crossingSpaces(OtherCommands, count);
                                    if (OtherCommands[count] != ':')
                                    {
                                        cerr << ">> syntaxError : after \'\"\' it did not end in \':\' " << endl;
                                        flag = 1;
                                        break;
                                        return;
                                    }
                                    else
                                    {
                                        ++count;
                                        crossingSpaces(OtherCommands, count);
                                        if (OtherCommands[count] == '[')
                                        {
                                            menuBrackets(OtherCommands, count, flag);
                                            ++count;
                                        }
                                        else if (OtherCommands[count] == '{')
                                        {
                                            ++count;
                                            object(OtherCommands, count, flag);
                                            ++count;
                                        }
                                        else if (OtherCommands[count] == '\"')
                                        {
                                            ++count;
                                            while (OtherCommands[count] != '\"')
                                            {
                                                ++count;
                                            }
                                            ++count;
                                        }
                                        else if ((OtherCommands[count] >= '0' && OtherCommands[count] <= '9') || OtherCommands[count] == '-')
                                        {
                                            int dot = 0;
                                            int place1, place2;
                                            if (OtherCommands[count] == '-')
                                            {
                                                place1 = count + 1;
                                            }
                                            else
                                            {
                                                place1 = count;
                                            }
                                            ++count;
                                            while ((OtherCommands[count] >= '0' && OtherCommands[count] <= '9') || OtherCommands[count] == '.')
                                            {
                                                if (OtherCommands[count] == '.')
                                                    ++dot;
                                                ++count;
                                            }
                                            place2 = count - 1;
                                            if (dot > 1 || (OtherCommands[place1] == '.' || OtherCommands[place2] == '.'))
                                            {
                                                flag = 1;
                                                cerr << ">> SyntaxError: Your Json data structure is invalid " << endl;
                                                break;
                                                return;
                                            }
                                            //______________________
                                        }
                                        else if (OtherCommands.substr(count, 4) == "true")
                                        {
                                            count += 4;
                                        }
                                        else if (OtherCommands.substr(count, 5) == "false")
                                        {
                                            count += 5;
                                        }
                                        else if (OtherCommands.substr(count, 4) == "null")
                                        {
                                            count += 4;
                                        }
                                        else
                                        {
                                            cerr << ">>  SyntaxError: This data is not valid" << endl;
                                            flag = 1;
                                            break;
                                            return;
                                        }
                                        crossingSpaces(OtherCommands, count);
                                        if (OtherCommands[count] != '}' && OtherCommands[count] != ',')
                                        {
                                            cerr << ">> SyntaxError: after data it did not end in , or } " << endl;
                                            flag = 1;
                                            break;
                                            return;
                                        }
                                        else
                                        {
                                            if (OtherCommands[count] == '}')
                                                ++num2;
                                            else
                                            {
                                                ++count;
                                                crossingSpaces(OtherCommands, count);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            ++count;
            crossingSpaces(OtherCommands, count);
            if (flag != 1)
            {
                if (OtherCommands[count] != ',' && OtherCommands[count] != ']')
                {
                    cerr << ">> syntaxError: Json data is not valid " << endl;
                    break;
                    return;
                }
                if (OtherCommands[count] != ']')
                {
                    ++count;
                    crossingSpaces(OtherCommands, count);
                    if (OtherCommands[count] != '{' && OtherCommands.substr(count, 4) != "null")
                    {
                        cerr << ">> syntaxError: Json data is not valid " << endl;
                        break;
                        return;
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    if (flag != 1)
    {
        json = OtherCommands;
    }
    else
    {
        json = "";
    }
}
/*******************************************************************************/
//function for object -> {}or{"name":"mina","stn":98123580413}
void object(string &OtherCommands, int &count, int &flag)
{
    int num1 = 1, num2 = 0;
    while (num1 != num2)
    {
        crossingSpaces(OtherCommands, count);
        if (OtherCommands[count] == '{' || OtherCommands[count] == '}')
        {
            if (OtherCommands[count] == '}')
            {
                ++num2;
                continue;
            }
            ++count;
            crossingSpaces(OtherCommands, count);
        }
        if (OtherCommands[count] != '\"' && OtherCommands[count] != '}')
        {
            cerr << ">> SyntaxError: Your data object structure is not valid " << endl;
            flag = 1;
            break;
        }
        else
        {
            if (OtherCommands[count] == '}')
            {
                ++num2;
                break;
            }
            else
            {
                ++count;
                while (OtherCommands[count] != '\"' && count < (OtherCommands.size()))
                {
                    ++count;
                }
                if (count == (OtherCommands.size() - 1))
                {
                    cerr << " SyntaxError: This data is not valid" << endl;
                    flag = 1;
                    break;
                }
                else
                {
                    ++count;
                    crossingSpaces(OtherCommands, count);
                    if (OtherCommands[count] != ':')
                    {
                        cout << ">> syntaxError : after \'\"\' it did not end in \':\' " << endl;
                        flag = 1;
                        break;
                    }
                    else
                    {
                        ++count;
                        crossingSpaces(OtherCommands, count);
                        if (OtherCommands[count] == '[')
                        {
                            int f2 = 0;
                            crossingSpaces(OtherCommands, count);
                            if (OtherCommands[count] == '{')
                            {
                                f2 = 1;
                            }
                            menuBrackets(OtherCommands, count, flag);
                            crossingSpaces(OtherCommands, count);
                            ++count;

                            crossingSpaces(OtherCommands, count);
                        }
                        else if (OtherCommands[count] == '{')
                        {
                            ++count;
                            object(OtherCommands, count, flag);
                            ++count;
                        }
                        else if (OtherCommands[count] == '\"')
                        {
                            ++count;
                            while (OtherCommands[count] != '\"')
                            {
                                ++count;
                            }
                            ++count;
                        }
                        else if ((OtherCommands[count] >= '0' && OtherCommands[count] <= '9') || OtherCommands[count] == '-')
                        {
                            int dot = 0;
                            int place1, place2;
                            if (OtherCommands[count] == '-')
                            {
                                place1 = count + 1;
                            }
                            else
                            {
                                place1 = count;
                            }
                            ++count;
                            while ((OtherCommands[count] >= '0' && OtherCommands[count] <= '9') || OtherCommands[count] == '.')
                            {
                                if (OtherCommands[count] == '.')
                                    ++dot;
                                ++count;
                            }
                            place2 = count - 1;
                            if (dot > 1 || (OtherCommands[place1] == '.' || OtherCommands[place2] == '.'))
                            {
                                flag = 1;
                                cerr << ">> SyntaxError: Your Json data structure is invalid " << endl;
                                break;
                            }
                        }
                        else if (OtherCommands.substr(count, 4) == "true")
                        {
                            count += 4;
                        }
                        else if (OtherCommands.substr(count, 5) == "false")
                        {
                            count += 5;
                        }
                        else if (OtherCommands.substr(count, 4) == "null")
                        {
                            count += 4;
                        }
                        else
                        {
                            cerr << ">>  SyntaxError: This data is not valid" << endl;
                            flag = 1;
                            break;
                        }
                        crossingSpaces(OtherCommands, count);
                        if (OtherCommands[count] != '}' && OtherCommands[count] != ',')
                        {
                            crossingSpaces(OtherCommands, count);
                            cerr << ">> SyntaxError: after data it did not end in , or } " << endl;
                            flag = 1;
                            break;
                        }
                        else
                        {
                            if (OtherCommands[count] == '}')
                                ++num2;
                            else
                            {
                                ++count;
                                crossingSpaces(OtherCommands, count);
                            }
                        }
                    }
                }
            }
        }
    }
    if (flag != 1)
    {
        json = OtherCommands;
    }
    else
    {
        json = "";
    }
}
/*******************************************************************************/
//function for boolean brackets -> [true,false,null]
void boolBrackets(string &OtherCommands, int &count, int &flag)
{
    if (OtherCommands.substr(count, 4) == "true")
    {
        count += 4;
    }
    else
    {
        count += 5;
    }
    crossingSpaces(OtherCommands, count);
    if (OtherCommands[count] != ',' && OtherCommands[count] != ']')
    {
        cerr << ">> SyntaxError: after true/false it did not end in , or ] " << endl;
        flag = 1;
        return;
    }
    else
    {
        ++count;
        crossingSpaces(OtherCommands, count);
        string str = "";
        while (OtherCommands[count] != '\n' && OtherCommands[count] != '\t' && OtherCommands[count] != ' ' && OtherCommands[count] != ']' && OtherCommands[count] != ',')
        {
            str += OtherCommands[count];
            ++count;
        }
        if (str != "false" && str != "true" && str != "null" && str != "]")
        {
            cerr << ">> SyntaxError: Because after \',\' it did not end in true or false " << endl;
            flag = 1;
            return;
        }
        else
        {
            while (OtherCommands[count] != ']')
            {
                crossingSpaces(OtherCommands, count);
                if (OtherCommands[count] != ',' && OtherCommands[count] != ']')
                {
                    cerr << ">>  SyntaxError: after true/false  it did not end in , or ]" << endl;
                    flag = 1;
                    break;
                    return;
                }
                else
                {
                    ++count;
                    crossingSpaces(OtherCommands, count);
                    string str = "";
                    while (OtherCommands[count] != '\t' && OtherCommands[count] != '\n' && OtherCommands[count] != ' ' && OtherCommands[count] != ']' && OtherCommands[count] != ',')
                    {
                        str += OtherCommands[count];
                        ++count;
                    }
                    crossingSpaces(OtherCommands, count);
                    if (str != "false" && str != "true" && str != "null" && str != "]")
                    {
                        cerr << ">> SyntaxError: Because after , it did not end in true or false" << endl;
                        flag = 1;
                        break;
                        return;
                    }
                }
            }
        }
    }
    if (flag != 1)
    {
        json = OtherCommands;
    }
}
/*******************************************************************************/
//mensu for calling brackets funnctions
void menuBrackets(string &OtherCommands, int &count, int &flag)
{
    while (true)
    {
        ++count;
        crossingSpaces(OtherCommands, count);
        if (OtherCommands[count] == '\"')
        {
            stringBrackets(OtherCommands, count, flag);
            break;
        }
        else if ((OtherCommands[count] >= '0' && OtherCommands[count] <= '9') || OtherCommands[count] == '-')
        {
            numberBrackets(OtherCommands, count, flag);
            break;
        }
        else if (OtherCommands[count] == '{')
        {
            objectBrackets(OtherCommands, count, flag);
            break;
        }
        else if (OtherCommands.substr(count, 4) == "true" || OtherCommands.substr(count, 5) == "false")
        {
            boolBrackets(OtherCommands, count, flag);
            break;
        }
        else if (OtherCommands[count] == ']')
        {
            break;
        }
        else if (OtherCommands[count] == '[')
        {
            arrayBrackets(OtherCommands, count, flag);
            break;
        }
        else if (OtherCommands.substr(count, 4) == "null")
        {
            count += 4;
            crossingSpaces(OtherCommands, count);
            if (OtherCommands[count] == ']')
            {
                break;
            }
            if (OtherCommands[count] != ',')
            {
                cerr << ">>  SyntaxError: after null it did not end in , " << endl;
                break;
                return;
            }
        }
        else
        {
            cerr << ">> SyntaxError: The data inside the bracket is not part of json data" << endl;
            break;
            return;
        }
    }
}
/*******************************************************************************/
//function for array brackets -> [[true,false,null],["mina","yaghoubi"],null]
void arrayBrackets(string &OtherCommands, int &count, int &flag)
{
    while (OtherCommands[count] != ']')
    {
        menuBrackets(OtherCommands, count, flag);
        ++count;
        crossingSpaces(OtherCommands, count);
        if (flag != 1)
        {
            if (OtherCommands[count] != ',' && OtherCommands[count] != ']')
            {
                cerr << ">> SyntaxError: after [...]  it did not end in , or ]" << endl;
                flag = 1;
                break;
                return;
            }
            if (OtherCommands[count] != ']')
            {
                ++count;
                crossingSpaces(OtherCommands, count);
                int flag2 = 0;
                check(OtherCommands, count, flag, flag2);
                if (flag2 == 1)
                {
                    if (OtherCommands[count - 1] != 'l')
                        --count;
                    if (OtherCommands[count] != ',' && OtherCommands[count] != ']')
                    {
                        cerr << ">> SyntaxError: after [...]  it did not end in , or ]" << endl;
                        flag = 1;
                        break;
                        return;
                    }
                    if (OtherCommands[count] != ']')
                    {
                        ++count;
                        crossingSpaces(OtherCommands, count);
                        if (OtherCommands[count] != '[')
                        {
                            cerr << ">> SyntaxError: Because after \',\' it did not end in true or false" << endl;
                            flag = 1;
                            break;
                            return;
                        }
                    }
                }
                else if (OtherCommands[count] != '[')
                {
                    cerr << ">> SyntaxError: Because your Json data is invalid" << endl;
                    flag = 1;
                    break;
                    return;
                }
            }
        }
    }
    if (flag != 1)
    {
        json = OtherCommands;
    }
    else
    {
        json = "";
    }
}
/*******************************************************************************/
void check(string &OtherCommands, int &count, int &flag, int &flag2)
{
    if (OtherCommands.substr(count, 4) == "null")
    {
        count += 4;
        crossingSpaces(OtherCommands, count);
        if (OtherCommands[count] != ',' && OtherCommands[count] != ']')
        {
            cerr << ">> SyntaxError: after [...]  it did not end in , or ]" << endl;
            flag = 1;
            return;
        }
        else if (OtherCommands[count] != ']' && flag != 1)
        {
            ++count;
            crossingSpaces(OtherCommands, count);
            check(OtherCommands, count, flag, flag2);
        }
        flag2 = 1;
    }
}
/*******************************************************************************/