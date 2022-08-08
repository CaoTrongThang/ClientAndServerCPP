#include <iostream>
#include <WS2tcpip.h>
#include <string>

using namespace std;

int main()
{
    //SERVER IP0
    string ip = "127.0.0.1";

    int port = 55555;

    //INITIALIZE WINSOCK
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2,2);
    
    int wsErr = WSAStartup(wVersionRequested, &wsaData);

    //CREATE A SOCKET
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        cout << "Socket built failed" << endl;
    }

    //INITIALIZE SERVER DATA
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str() , &hint.sin_addr);

    //CONNECT THIS CLIENT SOCKET TO SERVER SOCKET(hint) AND BIND IT UNTIL WE HAVE TO CLOSE THE CONNECT
    while(connect(sock, (sockaddr*)&hint, sizeof(hint)) != 0)
    {
        cout << "The connection is fail, please connect again..." << endl;
    }


    char buf[4096];
    string userInput;
    do
    {
        cout << "> ";
        getline(cin, userInput);
        send(sock, userInput.c_str(), userInput.size(), 0 );
        ZeroMemory(buf, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if(bytesReceived > 0)
        {
            cout << "SERVER > " << string(buf, 0, bytesReceived) << endl;
        }


    } while (userInput.size() > 0);
    
    closesocket(sock);
    WSACleanup();
}