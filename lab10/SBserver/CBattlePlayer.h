#pragma once
#include <fstream>

#include "CAquatory.h"
#include "CShip.h"
#include <vector>
#include <regex>

#include <iostream>
#include <iomanip>

#include "winsock2.h" 

class CBattlePlayer
{
public:
	CBattlePlayer();
	~CBattlePlayer();

	string prepareMsg;
	string tempPrepareMsg;
	string lastMoveResult;
	string lastMove;
	vector<string> lastMoveLog;
	CAquatory m_Aqua;
	vector <CShip*> m_Ships;
	vector<string> allHits;
	vector<string> computerAllHits;
	vector<string> computerLastSuccessfulHits;
	int computerHitStatus;
	int computerHitAttempt;

	SOCKET m_sock;

	string computerGenerateHit();
	void computerProcessingHits();

	int choosePlayWith();

	int selectLocationType();
	vector<string> generateShip(int length, bool orientation);
	void generatePrepareShips(bool player);
	void PrepareShips();
	void handPrepareShips();
	void filePrepareShips();
	bool ShipsAreReady();
	void DoMove(bool player);
	void PrepareMessage(int active);
	void MoveMessage(int active);

	bool countShip(vector<string> ship);
	bool isShipSolid(vector<string> ship);
	vector<string> isRecieveShipValid(string ship);
	string isRecieveHitValid(string hit);
	bool Try2PlaceShip(vector<string> ship);
	void Message(string str);
	void UIcommand(int cmd);

	string recieve();

	CBattlePlayer *m_pAnotherPlayer;

	bool IsAlive();
};

