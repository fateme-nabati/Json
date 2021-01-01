#include "../header/json.hpp"
using namespace std;
int main()//The program starts from the main function
{
     cout << "welcome to my program!!!" << endl;
     for (;;)
    {
        string MainCommand, OtherCommands;
        string InputCommand;
        cout << "->";
        string str;
        getline(cin, str);
        while (str != "</>") //Data is retrieved from the input until the program reaches </>
        {
            InputCommand += str;
            InputCommand += '\n';
            getline(cin, str);
        }
        MainCommand = "";
        int count = 0;
        while (InputCommand[count] != '\n' && InputCommand[count] != ' ' && InputCommand[count] && InputCommand[count] != '{' && InputCommand[count] != '[' && InputCommand[count] != '\t')
        {
            MainCommand += InputCommand[count];
            ++count;
        }
        while (InputCommand[count])
        {
            OtherCommands += InputCommand[count];
            ++count;
        }
        if (MainCommand == "exit") //Exit the program
        {
            cout << "I hope you enjoyed my program" << endl;
            break;
        }
        commandFunc(MainCommand, OtherCommands); //call commandFunc function
    }

    return 0;
}
