#include "ArgGetter.h"

using namespace std;

list<vector<int>> ArgGetter::getArgs(istream& is)
{
    string str;
    stringstream strstr;
    int number;
    list<vector<int>> to_return;
    vector<int> to_push;

    while(getline(is, str))
    {
        if(str.empty())
            break;
        strstr.str(str); //this is my favourite line
        while(strstr >> number)
        {
            to_push.push_back(number);
        }
        to_return.push_back(to_push);
        to_push.clear();
        strstr.clear();
    }
    return to_return;
}
