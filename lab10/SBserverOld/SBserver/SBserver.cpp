#include <iostream>
#include "CBattleGame.h"
#include "time.h"

using namespace std;

int main()
{
	srand(time(NULL));
	CBattleGame game;

	int startTCPrequest(game.StartTCP(5000));

	if (startTCPrequest != 0)
		game.DoPlay(startTCPrequest);



}
