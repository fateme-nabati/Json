#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;
#ifndef JSON_HPP
#define JSON_HPP
//--------------------------------------------------
void setData(string &);                                    //set-data command
void getType(string &, const string &);                    //get-type command
void getValue(string &, const string &);                   //get-value command
void compare(string &, const string &);                    //compare command
void calculate(string &OtherCommands, const string &json); //calculate command
void commandFunc(string &, string &);                      //menu
//---------------------------------------------------
void crossing(string &OtherCommands, int &counto);         // ignore white space
void crossingjson(const string &json, int &countj);        //ignore white space
string returnType(string &OtherCommands, const string &json);
string searchc(const string &json, int &countj, int &flag);
string Bracec(const string &json, int &countj, int &flag);
string Bracketsc(const string &json, int &countj, int &flag);
string returnValue(string &OtherCommands, const string &json);
string searchgvc(const string &json, int &countj, int &flag);
string Bracegvc(const string &json, int &countj, int &flag);
string Bracketsgvc(const string &json, int &countj, int &flag);
#endif