#include <iostream>
#include "CBattleGame.h"
#include "time.h"

using namespace std;

void connectTCP(CBattleGame game, vector<int> &startTCPrequests, int port)
{
	cout << "запуск с портом " << port << endl;
	//startTCPrequests.push_back(game.StartTCP(port));
}

void Play(CBattleGame game, int TCPrequest)
{
	/*cout << TCPrequest << " запуск\n";
	if (TCPrequest != 0)
		game.DoPlay(TCPrequest);*/

	Sleep(100000);
}


int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	vector <thread> thrds;
	vector <CBattleGame> games;

	CBattleGame game1, game2;
	string ip = "120.0.0.1";
	game1.StartTCP(ip, 5000);
	ip = "120.0.0.2";
	game2.StartTCP(ip, 5001);

	//vector <int> startTCPrequests;
	//for (int i = 0; i < 5; i++)
	//{
	//	cout << "i " << i << endl;
	//	CBattleGame game;
	//	games.push_back(game);
	//	connectTCP(games[i], startTCPrequests, (5000 + i));
	//	//thrds.push_back(thread(Play, games[i], startTCPrequests[i]));
	//	//thrds[i].join();
	//	//thrds[i].join();
	//}
	return 0;



}
