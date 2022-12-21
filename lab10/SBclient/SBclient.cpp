#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream> 
#include <cstdio> 
#include <cstring> 
#include <winsock2.h> 
#include <string>
#include <windows.h>
#pragma comment(lib, "WS2_32.lib")

using namespace std;

void commands(int cmd)
{
	switch (cmd)
	{
	case 0:
		system("cls");
		break;

	case 1:
		cout << "Соперник подключился! Игра начнётся через 3 секунды." << endl;
		Sleep(3000);
		system("cls");
		break;
	}
}

DWORD WINAPI clientReceive(LPVOID lpParam) //Получение данных от сервера
{ 
	char buffer[1024] = { 0 };
	SOCKET server = *(SOCKET*)lpParam;
	while (true) {
		if (recv(server, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
			cout << "сбой функции recv с ошибкой: " << WSAGetLastError() << endl;
			return -1;
		}
		if (strcmp(buffer, "exit\n") == 0) {
			cout << "Сервер отключен." << endl;
			return 1;
		}
		if (buffer[0] == 'c' && buffer[1] == 'm' && buffer[2] == 'd')
		{
			string scmd(buffer);
			scmd.erase(0, 3);
			int cmd = stoi(scmd);
			commands(cmd);
		}
		else
			cout << buffer << endl;
		memset(buffer, 0, sizeof(buffer));
	}
	return 1;
}

DWORD WINAPI clientSend(LPVOID lpParam) //Отправка данных на сервер
{ 
	char buffer[1024] = { 0 };
	SOCKET server = *(SOCKET*)lpParam;
	while (true) {
		fgets(buffer, 1024, stdin);
		if (send(server, buffer, sizeof(buffer), 0) == SOCKET_ERROR) 
		{
			cout << "Ошибка при попытке отправить сообщение" << WSAGetLastError() << endl;
			return -1;
		}
		if (strcmp(buffer, "exit") == 0) {
			break;
		}
	}
	return 1;
}

int main() {
	setlocale(LC_ALL, "RU");
	WSADATA WSAData;
	SOCKET server;
	SOCKADDR_IN addr;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "Создание сокета завершилось с ошибкой: " << WSAGetLastError() << endl;
		return -1;
	}


	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //коннект к серверу
	addr.sin_family = AF_INET;

	for (int i = 0; i < 5; i++)
	{
		addr.sin_port = htons(5000 + i); //порт
		if (connect(server, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			cout << "Не удалось подключиться к серверу: " << WSAGetLastError() << endl;
		}
		else
		{
			cout << "Подключено к серверу с портом: " << 5000 + i<< endl;
			Sleep(1000000);
			break;
		}
	}

	cout << "Подключение к серверу успешно выполнено!" << endl;

	DWORD tid;
	HANDLE t1 = CreateThread(NULL, 0, clientReceive, &server, 0, &tid);
	if (t1 == NULL) cout << "Ошибка создания потока: " << GetLastError();
	HANDLE t2 = CreateThread(NULL, 0, clientSend, &server, 0, &tid);
	if (t2 == NULL) cout << "Ошибка создания потока: " << GetLastError();

	cout << "подключился" << endl;

	WaitForSingleObject(t1, INFINITE);
	WaitForSingleObject(t2, INFINITE);
	closesocket(server);
	WSACleanup();
}
