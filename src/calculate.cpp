#include "../header/json.hpp"
#include <cfloat>
using namespace std;
vector<string> pathcalculate;
static int numbercal = 0;
/************************************************/
void calculate(string &OtherCommands, const string &json)
{
    //cout<<setprecision
    pathcalculate.clear();
    string command1 = "", command2 = "";
    numbercal = 0;
    int counto = 0, flag = 0;
    int countj = 0;
    string str;
    char ch;
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
            while (OtherCommands[counto] != ' ' && OtherCommands[counto] != '\t' && OtherCommands[counto] != '\n' && OtherCommands[counto] &&
                   OtherCommands[counto] != '+' && OtherCommands[counto] != '-' && OtherCommands[counto] != '*' && OtherCommands[counto] != '/' &&
                   OtherCommands[counto] != '^')
            {
                command1 += OtherCommands[counto];
                ++counto;
            }
            crossing(OtherCommands, counto);
            ch = OtherCommands[counto];
            ++counto;
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
        if (result1 != result2)
        {
            cerr << ">> TypeError: Cannot compare " << result1.substr(2) << " with " << result2.substr(2) << endl;
        }
        else
        {
            if (result1 == "failed" || result2 == "failed")
                cerr << ">> TypeError: Cannot compare at least one of the data is not possible" << endl;
            else if (result1 != "> Number" && result2 != "> Number")
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
                switch (ch)
                {
                case '+':
                    cout << "> " << (n1 + n2) << endl;
                    break;
                case '-':
                    cout << "> " << (n1 - n2) << endl;
                    break;
                case '*':
                    cout << "> " << (n1 * n2) << endl;
                    break;
                case '/':
                    cout << "> " << (n1 / n2) << endl;
                    break;
                case '^':
                    cout << "> " << powf(n1, n2) << endl;
                    break;
                default:
                    cerr << ">> InvalidArgumentError: Unknown operation " << ch << endl;
                    break;
                }
            }
        }
    }
}
/************************************************/