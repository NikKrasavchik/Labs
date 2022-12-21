#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "CBattleGame.h"

#pragma comment (lib, "ws2_32.lib")
#include <iostream>

#include "winsock2.h" 

//#define TEST

using namespace std;

CBattleGame::CBattleGame()
{
	m_iCurrentMove = MOVE1;
	m_Player1.m_pAnotherPlayer = &m_Player2;
	m_Player2.m_pAnotherPlayer = &m_Player1;
}
CBattleGame::~CBattleGame()
{

}

int CBattleGame::StartTCP(int port)
{
	setlocale(LC_ALL, "Rus");

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("Error WSAStartup %i\n", WSAGetLastError());
		return 0;
	}

	SOCKET mysocket;

	if ((mysocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		printf("Error socket %i\n", WSAGetLastError());
		WSACleanup(); // Деиницилизация библиотеки Winsock
		return 0;
	}

	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);
	local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(mysocket, (sockaddr*)&local_addr, sizeof(local_addr)))
	{

		printf("Error bind %d\n", WSAGetLastError());
		closesocket(mysocket);
		WSACleanup();
		return 0;
	}

	if (listen(mysocket, 0x100))
	{
		printf("Error listen %d\n", WSAGetLastError());
		closesocket(mysocket);
		WSACleanup();
		return 0;
	}
	printf("Начинаем игру\n");

	SOCKET client_socket;
	sockaddr_in client_addr;

	int client_addr_size = sizeof(client_addr);


	client_socket = accept(mysocket, (sockaddr*)&client_addr, &client_addr_size);


	m_Player1.m_sock = client_socket;

	HOSTENT* hst;
	hst = gethostbyaddr((char*)&client_addr.sin_addr.s_addr, 4, AF_INET);

	// вывод сведений о клиенте
	printf("Игрок1 с IP [%s] на связи!\n", inet_ntoa(client_addr.sin_addr));

	if (m_Player1.choosePlayWith() == 1)
	{

		client_socket = accept(mysocket, (sockaddr*)&client_addr, &client_addr_size);

		m_Player2.m_sock = client_socket;

		hst = gethostbyaddr((char*)&client_addr.sin_addr.s_addr, 4, AF_INET);

		// вывод сведений о клиенте
		printf("Игрок2 с IP [%s] на связи!\n", inet_ntoa(client_addr.sin_addr));

		return 1;
	}
	else
		return 2;
}

void CBattleGame::DoPlay(int playWith)
{
	switch (playWith)
	{
	case 1:
		PlayWithPlayer();
		break;
	case 2:
		PlayWithComputer();
		break;
	}
}

void CBattleGame::PlayWithPlayer()
{
	m_Player1.UIcommand(1);
	m_Player2.UIcommand(1);
	Sleep(3100);

	thread p2Prepare([&]()
		{
			m_Player2.PrepareShips();
		});
	m_Player1.PrepareShips();
	p2Prepare.join();

	Sleep(100);
	m_Player1.PrepareMessage(3);
	m_Player2.PrepareMessage(3);
	Sleep(3000);
	m_Player1.UIcommand(0);
	m_Player2.UIcommand(0);
	Sleep(300);

	(rand() % 2 ? m_iCurrentMove = 1 : m_iCurrentMove = -1);

	while (m_Player1.IsAlive() and m_Player2.IsAlive())
	{
		if (m_iCurrentMove == MOVE1)
		{
			m_Player1.MoveMessage(1);
			m_Player2.MoveMessage(2);
			Sleep(300);
			m_Player1.DoMove(true);
		}

		if (m_iCurrentMove == MOVE2)
		{
			m_Player2.MoveMessage(1);
			m_Player1.MoveMessage(2);
			Sleep(300);
			m_Player2.DoMove(true);
		}

		m_iCurrentMove *= -1;
	}
	Sleep(1000);
}

void CBattleGame::PlayWithComputer()
{
	m_Player1.UIcommand(1);
	Sleep(3100);
	m_Player1.PrepareShips();
	m_Player2.generatePrepareShips(false);
	
	Sleep(100);
	m_Player1.PrepareMessage(3);
	m_Player1.UIcommand(0);
	Sleep(300);

	(rand() % 2 ? m_iCurrentMove = 1 : m_iCurrentMove = -1);

	while (m_Player1.IsAlive() and m_Player2.IsAlive())
	{
		if (m_iCurrentMove == MOVE1)
		{
			m_Player1.MoveMessage(1);
			Sleep(300);
			m_Player1.DoMove(false);
		}

		if (m_iCurrentMove == MOVE2)
		{
			m_Player2.computerProcessingHits();
			Sleep(300);
		}

		m_iCurrentMove *= -1;
	}
	Sleep(1000);
}
