#include <WS2tcpip.h>
#include <iostream>
#include <thread>
#include <string>
#include "HeaderFiles/DataHandler.h"

using namespace std;

#define PORT 55555
#define BUFLENGTH 5000

int main()
{
    string ip = "127.0.0.1";

    WSADATA wsaData;
    int wsErr = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsErr == 0)
    {
        cout << "Winsock dll found" << endl;
        cout << "Status: " << wsaData.szSystemStatus << endl;
    }

    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == 0)
    {
        cout << "Socket is created!" << endl;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

    int isBound = bind(listening, (sockaddr *)&hint, sizeof(hint));
    if (isBound == 0)
    {
        cout << "The ip and port are bound to the socket" << endl;
    }

    listen(listening, 15);

    sockaddr_in clientAddress;
    int addressLength;
    SOCKET clientSocket = accept(listening, (sockaddr*)&clientAddress, &addressLength);
    
    cout << inet_ntoa(clientAddress.sin_addr) << ":" << clientAddress.sin_port << endl;


    char recvChar[BUFLENGTH];
    while (true)
    {
        ZeroMemory(recvChar, BUFLENGTH);
        int bytesRecievedLength = recv(clientSocket, recvChar, BUFLENGTH, 0);
        string data = string(recvChar, 0, bytesRecievedLength);
        DataReciever(data, &clientSocket);
    }

    return 0;
}