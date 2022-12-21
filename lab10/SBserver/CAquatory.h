#pragma once
#include "CCell.h"
#include <string>
#include <iostream>

using namespace std;
class CAquatory
{
public:
	CAquatory();
	~CAquatory();


	string MovePrint(CCell enemy_Cells[10][10]);
	string PreparePrint();


	CCell m_Cells[10][10];

	bool Try2PlaceDeck(string cell, CCell **pCell,CShip *sh);
	bool TestCell4ShipDeck(int i, int j, CShip *s);
	int Letter2Number(char l);

	bool TestShip(string cell, CShip **ship);
	
	bool ParseCell(string cell, int &i, int&j);

};

