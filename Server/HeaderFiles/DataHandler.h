#include <WS2tcpip.h>
#include <iostream>
#include <string>

using namespace std;

void DataReciever(string pData, SOCKET *client);
void Replace(string *str, string *stringToReplace, string *replaceString);