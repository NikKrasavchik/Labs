#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <string>

#pragma warning(disable: 4996)

using namespace std;

double countRVector(int x, int y, int z)
{
    double RVector = sqrt(x * x + y * y + z * z);
    return RVector;
}


int main()
{
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
    {
        cout << "ERROR\n";
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

    if (newConnection == 0)
    {
        cout << "ERROR #2\n";
    }
    else
    {
        cout << "Client connected!\n";
        char x[256], y[256], z[256];
        recv(newConnection, x, sizeof(x), NULL);
        recv(newConnection, y, sizeof(y), NULL);
        recv(newConnection, z, sizeof(z), NULL);
        
        int ix = atoi(x);
        int iy = atoi(y);
        int iz = atoi(z);

        string strRVector = to_string(countRVector(ix, iy, iz)) + "\0";
        send(newConnection, strRVector.c_str(), sizeof(strRVector), NULL);
    }

    system("pause");
}