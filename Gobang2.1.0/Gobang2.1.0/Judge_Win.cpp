#include "Game.h"
#include <memory>
#include <iostream>
#include <ctime> 
bool Game::judge(int x, int y)
{
	if (!chess[x][y].flag)
		return true;
	else
		return false;
}
bool Game::ifWin(int x, int y)
{
	int judge=GetCheng5ChangLian(x, y, chess[x][y].flag);

	if (judge==1)
		return true;
	else
		return false;
}
//int Game::IsKinjite(int row, int col)
//{
//	//根据规则如果黑棋在形成五连的同时，又形成禁手，那么仍然是黑棋胜
//
//	Search(row, col, BLACK_CHESS);
//
//	if (changlian)
//		return 1;
//	if (cheng5)  // 
//		return 0;
//	if (lian3 + tiao3 >= 2)
//		return 2;
//	if (huo4 + chong4 + tiaochong4 >= 2)
//		return 3;
//
//	return 0;
//}
bool Game::judge_IsKinjite(int row, int col)
{
	if (chess[row][col].flag == BLACK_CHESS && IsKinjite(row, col))
	{
		return  true;
	}
	else return false;
}
