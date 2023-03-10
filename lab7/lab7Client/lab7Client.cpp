#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>

#pragma warning(disable: 4996)

using namespace std;

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

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        cout << "ERROR: Failed connect to client!\n";
        return 1;
    }
    cout << "Connected!\n\n";

    char x[256], y[256], z[256];
    cin >> x >> y >> z;
    send(Connection, x, sizeof(x), NULL);
    send(Connection, y, sizeof(y), NULL);
    send(Connection, z, sizeof(z), NULL);

    char RVector[256];
    recv(Connection, RVector, sizeof(RVector), NULL);
    cout << RVector << endl;

    system("pause");
}