#pragma once
#include "CBattlePlayer.h"
#include <Windows.h>
#include <regex>
#include <thread>

#define MOVE1 1
#define MOVE2 -1



class CBattleGame
{
public:
	CBattleGame();
	~CBattleGame();

	int m_iCurrentMove;

	int StartTCP(string ip, int port);

	void DoPlay(int playWith);
	void PlayWithPlayer();
	void PlayWithComputer();

	CBattlePlayer m_Player1, m_Player2;
};

