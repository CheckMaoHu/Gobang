#include "Game.h"

void Game::BackstageAI()
{
	depthkongzhi = false;
	poinT result[11];
	int num = heuristic(left, right, top, bottom, cComputer, result);
	for (int i = 0; i < num; i++)
	{
		if (AIkongzhi)
			return;
		chess[result[i].x][result[i].y].flag = cPeople;
		CalculateInitHashKey();
		Hash_MakeMove(result[i].x, result[i].y, cPeople);//单独加点
		for (int i = 1; i <= 9; i++)
		{
			if (depthkongzhi)
				break;
			MaxMin(i);
		}
		chess[result[i].x][result[i].y].flag = SPACE;
		Hash_UnMakeMove(result[i].x, result[i].y, cPeople);//撤回
	}
}