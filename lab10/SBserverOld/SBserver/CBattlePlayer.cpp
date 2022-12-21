#include "CBattlePlayer.h"


//#define TEST

CBattlePlayer::CBattlePlayer()
{
	m_sock = 0;
	m_pAnotherPlayer = NULL;
	prepareMsg = "\nИстория расстановки кораблей:\n";
	tempPrepareMsg = "";
	lastMoveResult = "";
	lastMove = "";
	computerHitStatus = 0;
	computerHitAttempt = 0;
}

CBattlePlayer::~CBattlePlayer()
{
	for (size_t i = 0; i < m_Ships.size(); i++)
	{
		delete m_Ships[i];
	}

	m_Ships.clear();

}

void CBattlePlayer::Message(string str)
{
	str = "\n" + str + "\n";
	send(m_sock, str.c_str(), str.size() + 1, 0);
}

void CBattlePlayer::UIcommand(int cmd)
{
	string msg = "cmd" + to_string(cmd) + "\n";
	send(m_sock, msg.c_str(), msg.size() + 1, 0);
}

string CBattlePlayer::computerGenerateHit()
{
	string hit = "";
	if (computerHitStatus == 0)
	{
		while (hit == "")
		{
			int letter(rand() % 10), num(rand() % 10);
			hit += char(letter + 97) + to_string(num + 1);
			for (int i = 0; i < computerAllHits.size(); i++)
				if (computerAllHits[i] == hit)
					hit = "";
		}
		return hit;
	}
	else if (computerHitStatus == 1)
	{
		string successfulHit;
		successfulHit += computerLastSuccessfulHits[computerLastSuccessfulHits.size() - 1];
		cout << "1generateSuccessfulHits: " << successfulHit << endl;
		int letter = int(successfulHit[0]);
		successfulHit.erase(0, 1);
		int num = stoi(successfulHit);
		if (computerHitAttempt == 0 && letter != 97)
		{
			hit = char(letter - 1) + to_string(num);
			for (int i = 0; i < computerAllHits.size(); i++)
				if (computerAllHits[i] == hit)
					hit = "";
		}
		if (((computerHitAttempt == 1 || computerHitAttempt == 0) && num != 10) && hit == "")
		{
			hit = char(letter) + to_string(num + 1);
			for (int i = 0; i < computerAllHits.size(); i++)
				if (computerAllHits[i] == hit)
					hit = "";
		}
		if (((computerHitAttempt == 2 || computerHitAttempt == 1 || computerHitAttempt == 0) && letter != 106) && hit == "")
		{
			hit = char(letter + 1) + to_string(num);
			for (int i = 0; i < computerAllHits.size(); i++)
				if (computerAllHits[i] == hit)
					hit = "";
		}
		if (hit == "")
			hit = char(letter) + to_string(num - 1);
	}
	else
	{
		sort(computerLastSuccessfulHits.begin(), computerLastSuccessfulHits.end());
		string successfulHit1 = computerLastSuccessfulHits[0];
		string successfulHit2 = computerLastSuccessfulHits[computerLastSuccessfulHits.size() - 1];
		int letter1 = int(successfulHit1[0]);
		int letter2 = int(successfulHit2[0]);
		successfulHit1.erase(0, 1);
		successfulHit2.erase(0, 1);
		int num1 = stoi(successfulHit1);
		int num2 = stoi(successfulHit2);
		bool orientation(letter1 == letter2 ? true : false);
		if (orientation)
		{
			if (computerHitAttempt == 0 && num2 != 10)
			{
				hit = char(letter2) + to_string(num2 - 1);
				for (int i = 0; i < computerAllHits.size(); i++)
					if (computerAllHits[i] == hit)
						hit = "";
			}
			if (hit == "")
			{
				hit = char(letter1) + to_string(num1 - 1);
			}
		}
		else
		{
			if (computerHitAttempt == 0 && letter1 != 97)
			{
				hit = char(letter1 - 1) + to_string(num1);
				for (int i = 0; i < computerAllHits.size(); i++)
					if (computerAllHits[i] == hit)
						hit = "";
			}
			if (hit == "")
				hit = char(letter2 + 1) + to_string(num2);
		}
	}


	return hit;
}

void CBattlePlayer::computerProcessingHits()
{
	CShip* ship = NULL;
	if (computerLastSuccessfulHits.size() == 0 || computerHitStatus == 0)
	{
		computerAllHits.push_back(computerGenerateHit());

		if (m_pAnotherPlayer->m_Aqua.TestShip(computerAllHits[computerAllHits.size() - 1], &ship))
		{
			if (!ship->Alive())
			{
				if (!m_pAnotherPlayer->IsAlive())
				{
					m_pAnotherPlayer->MoveMessage(4);
					return;
				}
				else
				{
					computerLastSuccessfulHits.clear();
					computerHitStatus = 0;
					computerHitAttempt = 0;
				}
			}
			else
			{
				computerLastSuccessfulHits.push_back(computerAllHits[computerAllHits.size() - 1]);
				computerHitStatus = 1;
				computerHitAttempt = 0;
			}
			m_pAnotherPlayer->MoveMessage(2);
			computerProcessingHits();
		}
		else
		{
			computerHitStatus = 0;
			computerHitAttempt = 0;
		}
	}
	else
	{
		computerAllHits.push_back(computerGenerateHit());

		if (m_pAnotherPlayer->m_Aqua.TestShip(computerAllHits[computerAllHits.size() - 1], &ship))
		{
			if (!ship->Alive())
			{
				if (!m_pAnotherPlayer->IsAlive())
				{
					m_pAnotherPlayer->MoveMessage(4);
					return;
				}
				else
				{
					computerLastSuccessfulHits.clear();
					computerHitStatus = 0;
					computerHitAttempt = 0;
				}
			}
			else
			{
				computerLastSuccessfulHits.push_back(computerAllHits[computerAllHits.size() - 1]);
				computerHitStatus += 1;
				computerHitAttempt = 0;
			}
			m_pAnotherPlayer->MoveMessage(2);
			computerProcessingHits();
		}
		else
			computerHitAttempt += 1;
	}
}

int CBattlePlayer::choosePlayWith()
{
	UIcommand(0);
	string lastErr = "";
	while (true)
	{
		string msg = "";
		msg += "Выберите с кем играть:\n";
		msg += "\t1. Играть с другим игроком.\n";
		msg += "\t2. Играть с компьютером.\n\n";
		msg += lastErr;
		Message(msg);
		Message(msg);

		int type = 0;
		string stype(recieve());
		cmatch result, tempResult;
		regex reg("\\d{1}");
		regex_search(stype.c_str(), result, reg);
		if (result.size() != 0)
		{
			type = stoi(result[0].str());
			if (type == 1 || type == 2)
			{
				lastErr = "";
				return type;
			}
			else
			{
				UIcommand(0);
				lastErr = "Неправильно введён номер!\n";
			}
		}
		else
		{
			UIcommand(0);
			lastErr = "Введено не число!\n";
		}
	}
}

int CBattlePlayer::selectLocationType()
{
	UIcommand(0);
	string lastErr = "";
	while (true)
	{
		string msg = "";
		msg += "Выберите тип расстановки кораблей!\n\n";
		msg += "Доступные виды:\n";
		msg += "\t1. Расстановка кораблей вручную.\n";
		msg += "\t2. Расстановка кораблей по заранее подготовленному файлу.\n";
		msg += "\t3. Случайная расстановка.\n\n";
		msg += lastErr;
		Message(msg);

		int type = 0;
		string stype(recieve());
		cmatch result, tempResult;
		regex reg("\\d{1}");
		regex_search(stype.c_str(), result, reg);
		if (result.size() != 0)
		{
			type = stoi(result[0].str());
			if (type == 1 || type == 2 || type == 3)
			{
				lastErr = "";
				return type;
			}
			else
			{
				UIcommand(0);
				lastErr = "Неправильно введён номер!\n";
			}
		}
		else
		{
			UIcommand(0);
			lastErr = "Введено не число!\n";
		}
	}
}

void CBattlePlayer::PrepareShips()
{
	int type = selectLocationType();
	switch (type)
	{
	case 1:
		handPrepareShips();
		break;
	case 2:
		filePrepareShips();
		break;
	case 3:
		generatePrepareShips(true);
		break;
	}
}

void CBattlePlayer::filePrepareShips()
{
	ifstream file;
	string filename;
	filename = "prepare.txt";
	file.open("..\\field\\" + filename);
	for (int i = 0; i < 10; i++)
	{
		string recieveShip;
		file >> recieveShip;
		vector<string> ship(isRecieveShipValid(recieveShip));
		Try2PlaceShip(ship);
	}
	file.close();
	PrepareMessage(2);
}

void CBattlePlayer::handPrepareShips()
{
	PrepareMessage(1);

	while (!ShipsAreReady())
	{
		string recieveShip(recieve());
		vector<string> ship(isRecieveShipValid(recieveShip));
		if (ship.size() != 0)
		{
			for (int i = 0; i < ship.size(); i++)
				prepareMsg += ship[i];
			if (countShip(ship))
			{
				if (Try2PlaceShip(ship))
				{
					prepareMsg += ": OK\n";
				}
				else
				{
					prepareMsg += ": Ошибка в расположении корабля!\n";
				}
			}
		}
		else
		{
			recieveShip.erase(recieveShip.size() - 1);
			prepareMsg += recieveShip + ": Корабль введён неправильно!\n";
		}
		if (!ShipsAreReady())
			PrepareMessage(1);
	}
	PrepareMessage(2);
}

vector<string> CBattlePlayer::generateShip(int length, bool orientation)
{
	vector<string> ship;
	int staticNum = rand() % 10;
	vector<int> dynamicNums;
	dynamicNums.push_back(rand() % 10);

	int upperPosition = dynamicNums[0];
	int lowerPosition = dynamicNums[0];

	while (dynamicNums.size() != length)
	{
		bool position(rand() % 2);
		if (position)
			if (upperPosition == 0)
				position = false;
		else
			if (lowerPosition == 9)
				position = true;

		if (position)
		{
			dynamicNums.push_back(upperPosition - 1);
			upperPosition = dynamicNums[dynamicNums.size() - 1];
		}
		else
		{
			dynamicNums.push_back(lowerPosition + 1);
			lowerPosition = dynamicNums[dynamicNums.size() - 1];
		}
	}
	sort(dynamicNums.begin(), dynamicNums.end());

	if (orientation)
		for (int i = 0; i < length; i++)
			ship.push_back(char(staticNum + 97) + to_string(dynamicNums[i] + 1));
	else
		for (int i = 0; i < length; i++)
			ship.push_back(char(dynamicNums[i] + 97) + to_string(staticNum + 1));
	return ship;
}

void CBattlePlayer::generatePrepareShips(bool player)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < i + 1; j++)
		{
			vector<string> ship = generateShip(4 - i, rand() % 2);
			if (!Try2PlaceShip(ship))
				j--;
		}
	if (player)
		PrepareMessage(2);
}

void CBattlePlayer::DoMove(bool player)
{
	CShip* ship = NULL;
	string hit, rhit;
	do {
		rhit = recieve();
		hit = isRecieveHitValid(rhit);
		rhit.erase(rhit.size() - 1);
		lastMove = rhit;
		if (hit.size() == 0)
		{
			if (lastMoveResult.size() == 0)
				lastMoveResult = "Некорректная точка для удара!";
			MoveMessage(1);
		}
	} while (hit.size() == 0);

	if (m_pAnotherPlayer->m_Aqua.TestShip(hit, &ship))
	{
		lastMoveResult = "Попадание!";

		if (!ship->Alive())
		{
			lastMoveResult = "Корабль потоплен!";

			if (!m_pAnotherPlayer->IsAlive())
			{
				MoveMessage(3);
				if (player)
					m_pAnotherPlayer->MoveMessage(4);
				return;
			}
		}
		MoveMessage(1);
		if (player)
			m_pAnotherPlayer->MoveMessage(2);
		DoMove(player);

	}
	else
		if (lastMoveResult.size() == 0)
			lastMoveResult = "Мимо!";

	return;

}

void CBattlePlayer::PrepareMessage(int active)
{
	UIcommand(0);
	if (active == 0)
	{
		string moving = "_____СОПЕРНИК РАССТАВЛЯЕТ КОРАБЛИ. ПОДОЖДИТЕ НЕКОТОРОЕ ВРЕМЯ._____\n\n";
		string msg = moving + m_Aqua.PreparePrint();
		Message(msg);
		tempPrepareMsg = "";
	}
	else if (active == 1)
	{
		string moving = "_______________РАССТАВЛЯЙТЕ КОРАБЛИ!_______________\n\n";
		string nextShip = "\nСледующий корабль:";
		string msg = moving + m_Aqua.PreparePrint() + prepareMsg + tempPrepareMsg + nextShip;
		Message(msg);
		tempPrepareMsg = "";
	}
	else if (active == 2)
	{
		string moving = "_______________ОЖИДАЙТЕ, ПОКА СОПЕРНИК РАССТАВИТ СВОИ КОРАБЛИ_______________\n\n";
		string msg = moving + m_Aqua.PreparePrint() + prepareMsg;
		Message(msg);
	}
	else if (active == 3)
	{
		string moving = "_______________ВСЕ КОРАБЛИ РАССТАВЛЕНЫ, ОЖИДАЙТЕ 3 СЕКУНДЫ ДО БОЯ_______________\n\n";
		string msg = moving + m_Aqua.PreparePrint() + prepareMsg;
		Message(msg);
	}
}

void CBattlePlayer::MoveMessage(int active)
{
	UIcommand(0);
	if (active == 1)
	{
		string moving = "_________________________ВАШ ХОД_________________________\n\n";
		string todo = "Следующий удар:";
		if (lastMoveLog.size() == 5)
			lastMoveLog.erase(lastMoveLog.begin());
		 if (lastMoveResult != "" && lastMove != "")
			lastMoveLog.push_back(lastMove + ": " + lastMoveResult + "\n");
		string msg = moving + m_Aqua.MovePrint(m_pAnotherPlayer->m_Aqua.m_Cells) + "\n";
		for (int i = lastMoveLog.size() - 1; i >= 0; i--)
			msg += lastMoveLog[i];
		msg += todo;
		Message(msg);
		lastMoveResult = "";
		lastMove = "";
	}
	else if (active == 2)
	{
		string moving = "_____________________ХОД ПРОТИВНИКА______________________\n\n";
		if (lastMoveLog.size() == 5)
			lastMoveLog.erase(lastMoveLog.begin());
		if (lastMoveResult != "" || lastMove != "")
			lastMoveLog.push_back(lastMove + ": " + lastMoveResult + "\n");
		string msg = moving + m_Aqua.MovePrint(m_pAnotherPlayer->m_Aqua.m_Cells) + "\n";
		for (int i = lastMoveLog.size() - 1; i >= 0; i--)
			msg += lastMoveLog[i];
		Message(msg);
		lastMoveResult = "";
		lastMove = "";
	}
	else if (active == 3)
	{
		string ending = "____________________!!!ВЫ ВЫИГРАЛИ!!!____________________\n\n";
		string msg = ending + m_Aqua.MovePrint(m_pAnotherPlayer->m_Aqua.m_Cells);
		Message(msg);
	}
	else if (active == 4)
	{
		string ending = "____________________!!!ВЫ ПРОИГРАЛИ!!!___________________\n\n";
		string msg = ending + m_Aqua.MovePrint(m_pAnotherPlayer->m_Aqua.m_Cells);
		Message(msg);
	}
}

bool CBattlePlayer::countShip(vector<string> ship)
{

	int n4Deck, n3Deck, n2Deck, n1Deck;

	n4Deck = n3Deck = n2Deck = n1Deck = 0;

	for (size_t i = 0; i < m_Ships.size(); i++)
	{
		if (!m_Ships[i]->IsPlaced())
			return false;
		else {
			switch (m_Ships[i]->m_Deck)
			{
			case 1:
				n1Deck++;
				break;
			case 2:
				n2Deck++;
				break;
			case 3:
				n3Deck++;
				break;
			case 4:
				n4Deck++;
				break;

			}
		}
	}
	
	switch (ship.size())
	{
	case 4:
		if (n4Deck != 1)
			return true;
		break;
	case 3:
		if (n3Deck != 2)
			return true;
		break;
	case 2:
		if (n2Deck != 3)
			return true;
		break;
	case 1:
		if (n1Deck != 4)
			return true;
		break;
	}
	prepareMsg += ": Все корабли такого типа уже расставлены! Побробуйте другой!\n";
	tempPrepareMsg += "\n---Доступно " + to_string(1 - n4Deck) + " четырёхпалубн" + ((1 - n4Deck) == 1 ? "ый" : "ых") + ", " + to_string(2 - n3Deck) + " трёхпалубн" + ((2 - n3Deck) == 1 ? "ый" : "ых") + ", " + to_string(3 - n2Deck) + " двухпалубн" + ((3 - n2Deck) == 1 ? "ый" : "ых") + " и " + to_string(4 - n1Deck) + " однопалубн" + ((4 - n1Deck) == 1 ? "ый" : "ых") + " кораблей.---\n";
	return false;
}

bool CBattlePlayer::isShipSolid(vector<string> ship)
{
	vector<string> tempShip(ship);
	for (int i = 0; i < ship.size(); i++)
		tempShip[i].erase(0, 1);
	vector<int> intShip;
	for (int i = 0; i < ship.size(); i++)
		intShip.push_back(stoi(tempShip[i]));

	bool jSolid = true;
	for (int i = 0; i < ship.size(); i++)
		for (int j = i + 1; j < ship.size(); j++)
			if (ship[i][0] != ship[j][0])
				jSolid = false;

	if (jSolid)
	{
		sort(intShip.begin(), intShip.end());
		bool mContinuity = true, pContinuity = true;
		for (int i = 0; i < intShip.size() - 1; i++)
			if (intShip[i + 1] != (intShip[i] + 1))
				pContinuity = false;
		if (pContinuity == false)
			for (int i = 0; i < intShip.size() - 1; i++)
				if (intShip[i + 1] != (intShip[i] - 1))
					mContinuity = false;
		return pContinuity * mContinuity;
	}
	else
	{
		for (int i = 0; i < ship.size(); i++)
			for (int j = 1; j < ship.size(); j++)
				if (intShip[i] != intShip[j])
					return false;

		vector<int> intLetter;
		for (int i = 0; i < ship.size(); i++)
			intLetter.push_back((int)ship[i][0]);
		sort(intLetter.begin(), intLetter.end());
		bool mContinuity = true, pContinuity = true;
		for (int i = 0; i < intLetter.size() - 1; i++)
			if (intLetter[i + 1] != (intLetter[i] + 1))
				pContinuity = false;
		if (pContinuity == false)
			for (int i = 0; i < intLetter.size() - 1; i++)
				if (intLetter[i + 1] != (intLetter[i] - 1))
					mContinuity = false;
		return pContinuity * mContinuity;
	}
	return true;
}

vector<string> CBattlePlayer::isRecieveShipValid(string ship)
{
	vector <string> finalShip;

	regex reg("(([a-j]|[A-J])\\d{1,2}){1,4}");

	cmatch tempResult;
	regex_search(ship.c_str(), tempResult, reg);
	if (tempResult.size() != 0) // выбрасывание ненужных данных
		ship.erase(tempResult[0].str().size());
	if (tempResult[0].str() != ship && tempResult[0].str().size() != ship.size()) // проверка на первый символ
		return finalShip;

	cmatch fullResult;
	regex_match(ship.c_str(), fullResult, reg);

	if (fullResult.size() == 0) // проверка на валидность по маске
		return finalShip;

	int iDeck = 0;
	string strFullResult = fullResult[0].str();
	string normalW = "abcdefghijABCDEFGHIJ";

	for (int i = 0; i < strFullResult.length(); i++)
	{
		for (int j = 0; j < normalW.length(); j++)
		{
			if (isdigit(strFullResult[i]))
				break;
			else if (strFullResult[i] == normalW[j])
			{
				iDeck++;
				break;
			}
		}
	}

	vector <string> cell; // полученные данные перевёрнуты по i
	cmatch separateResult;

	switch (iDeck)
	{
	case 4:
		reg = "(([a-j]|[A-J])\\d{1,2}){4}";
		regex_search(strFullResult.c_str(), separateResult, reg);
		cell.push_back(separateResult[1].str());
	case 3:
		reg = "(([a-j]|[A-J])\\d{1,2}){3}";
		regex_search(strFullResult.c_str(), separateResult, reg);
		cell.push_back(separateResult[1].str());
	case 2:
		reg = "(([a-j]|[A-J])\\d{1,2}){2}";
		regex_search(strFullResult.c_str(), separateResult, reg);
		cell.push_back(separateResult[1].str());
	case 1:
		reg = "(([a-j]|[A-J])\\d{1,2}){1}";
		regex_search(strFullResult.c_str(), separateResult, reg);
		cell.push_back(separateResult[1].str());
		break;
	}

	for (int i = 0; i < cell.size(); i++)
	{
		if (cell[i][1] == '0') // проверка на 0 после цифры
			return finalShip;

		for (int j = 1; j < cell[i].size(); j++) // проверка числа на валидность
			if (j != 1 && cell[i][j] != '0')
				return finalShip;

		for (int j = i + 1; j < cell.size(); j++) // проверка на идентичность клеток
			if (cell[i] == cell[j])
				return finalShip;
	}


	vector<string> tempShip;
	for (int i = 0; i < cell.size(); i++)
		tempShip.push_back(cell[i]);

	if (isShipSolid(tempShip))
	{
		for (int i = tempShip.size()-1; i >= 0; i--)
			finalShip.push_back(tempShip[i]);
	}
	else
		return finalShip;

	return finalShip;
}

string CBattlePlayer::isRecieveHitValid(string hit)
{
	string finalHit = "";

	regex reg("(([a-j]|[A-J])\\d{1,2}){1}");

	cmatch tempResult;
	regex_search(hit.c_str(), tempResult, reg);
	if (tempResult.size() != 0) // выбрасывание ненужных данных
		hit.erase(tempResult[0].str().size());
	if (tempResult[0].str() != hit && tempResult[0].str().size() != hit.size()) // проверка на первый символ
		return finalHit;

	cmatch result;
	regex_match(hit.c_str(), result, reg);

	if (result.size() == 0)
		return finalHit;

	string tempHit = result[0].str();

	if (tempHit[1] == '0') // проверка на 0 после цифры
		return finalHit;

	for (int j = 1; j < tempHit.size(); j++) // проверка числа на валидность
		if (j != 1 && tempHit[j] != '0')
			return finalHit;

	for (int i = 0; i < allHits.size(); i++)
		if (allHits[i] == tempHit)
		{
			lastMoveResult = "Выстрел в данную область уже был произведён!";
			return "";
		}
	

	finalHit = tempHit;
	allHits.push_back(finalHit);
	return finalHit;
}

bool CBattlePlayer::ShipsAreReady()
{
#ifndef TEST
	if (m_Ships.size() == 10)
		return true;

#endif

#ifdef TEST
	if (m_Ships.size() == 1)
		return true;
#endif

	return false;
}

bool CBattlePlayer::Try2PlaceShip(vector<string> ship)
{
	char cell[4][10];
	for (int i = 0; i < ship.size(); i++)
		sscanf_s(ship[i].c_str(), "%[^\n],", cell[i], 4);
	
	CShip *s = new CShip(ship.size());

	for (int i = 0; i < ship.size(); i++)
	{
		CCell *pCell= NULL;
		if (m_Aqua.Try2PlaceDeck(cell[i],&pCell,s))
		{
			s->m_pCells.push_back(pCell);
			pCell->m_pShip = s;
		}
		else
		{
			s->ClearCells();
			delete s;
			return false;
		}
	}

	m_Ships.push_back(s);


	return true;
}

string CBattlePlayer::recieve()
{
	char buff[1024];
	recv(m_sock, &buff[0], sizeof(buff), 0);
	return buff;
}

bool CBattlePlayer::IsAlive()
{
	for (size_t i = 0; i < m_Ships.size(); i++)
	{
		if (m_Ships[i]->Alive())
			return true;
	}

	return false;
}