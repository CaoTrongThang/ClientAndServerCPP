#include "HeaderFiles/DataHandler.h"
#include <WS2tcpip.h>
#include <iostream>
#include <string>

using namespace std;

bool Contains(const string &str, const string &strToFind)
{
    if (str.length() < strToFind.length())
    {
        return false;
    }
    for (size_t i = 0; i < str.length(); i++)
    {
        for (size_t x = 0; x < strToFind.length(); x++)
        {
            if (x + i > str.length())
            {
                return false;
            }
            if (str[i + x] == strToFind[x])
            {
                if (x == strToFind.length() - 1)
                {
                    return true;
                }
            }
            else
            {
                break;
            }
        }
    }

    return false;
}

void DataReciever(string pData, SOCKET *client)
{
    srand(time(NULL));

    if (Contains(pData, "random"))
    {
        int randNum = rand();
        string msg = "Your random number is: " + to_string(randNum);

        send(*client, msg.c_str(), msg.length(), 0);
    }
    else
    {
        send(*client, pData.c_str(), pData.length(), 0);
    }
}