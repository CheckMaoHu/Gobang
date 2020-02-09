#include "Game.h"
#include <memory>
#include <iostream>
#include <ctime> 

int Game::GetHuo4(int row, int col, char chessFlag)
{
	//  假设在chess[row][col].flag 落子后，返回构成活4的数量 
	int huo4 = 0, left, right, i, j;
	bool flag;

	// 横 
	for (i = col - 1, left = 0; i >= 0 && chessFlag == chess[row][i].flag; --i, ++left);
	for (i = col + 1, right = 0; i<SIZE && chessFlag == chess[row][i].flag; ++i, ++right);

	if (3 == left + right && col - left - 1 >= 0 && SPACE == chess[row][col - left - 1].flag
		&& col + right + 1 < SIZE && SPACE == chess[row][col + right + 1].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (col - left - 2 >= 0 && chessFlag == chess[row][col - left - 2].flag)
				flag = false;
			if (col + right + 2 < SIZE && chessFlag == chess[row][col + right + 2].flag)
				flag = false;
		}
		if (flag)
			++huo4;
	}

	// 竖
	for (i = row - 1, left = 0; i >= 0 && chessFlag == chess[i][col].flag; --i, ++left);
	for (i = row + 1, right = 0; i<SIZE && chessFlag == chess[i][col].flag; ++i, ++right);

	if (3 == left + right && row - left - 1 >= 0 && SPACE == chess[row - left - 1][col].flag
		&& row + right + 1 < SIZE && SPACE == chess[row + right + 1][col].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (row - left - 2 >= 0 && chessFlag == chess[row - left - 2][col].flag)
				flag = false;
			if (row + right + 2 < SIZE && chessFlag == chess[row + right + 2][col].flag)
				flag = false;
		}
		if (flag)
			++huo4;
	}

	// ' \ '
	for (i = row - 1, j = col - 1, left = 0; i >= 0 && j >= 0 && chessFlag == chess[i][j].flag; --i, --j, ++left);
	for (i = row + 1, j = col + 1, right = 0; i<SIZE && j<SIZE && chessFlag == chess[i][j].flag; ++i, ++j, ++right);
	if (3 == left + right && row - left - 1 >= 0 && col - left - 1 >= 0 && SPACE == chess[row - left - 1][col - left - 1].flag
		&& row + right + 1 < SIZE && col + right + 1 < SIZE && SPACE == chess[row + right + 1][col + right + 1].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (row - left - 2 >= 0 && col - left - 2 >= 0 && chessFlag == chess[row - left - 2][col - left - 2].flag)
				flag = false;
			if (row + right + 2 < SIZE && col + right + 2 < SIZE && chessFlag == chess[row + right + 2][col + right + 2].flag)
				flag = false;
		}
		if (flag)
			++huo4;
	}

	// ' / '
	for (i = row - 1, j = col + 1, left = 0; i >= 0 && j<SIZE && chessFlag == chess[i][j].flag; --i, ++j, ++left);
	for (i = row + 1, j = col - 1, right = 0; i<SIZE && j >= 0 && chessFlag == chess[i][j].flag; ++i, --j, ++right);
	if (3 == left + right && row - left - 1 >= 0 && col + left + 1 < SIZE && SPACE == chess[row - left - 1][col + left + 1].flag
		&& row + right + 1 < SIZE && col - right - 1 >= 0 && SPACE == chess[row + right + 1][col - right - 1].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (row - left - 2 >= 0 && col + left + 2 < SIZE && chessFlag == chess[row - left - 2][col + left + 2].flag)
				flag = false;
			if (row + right + 2 < SIZE && col - right - 2 >= 0 && chessFlag == chess[row + right + 2][col - right - 2].flag)
				flag = false;
		}
		if (flag)
			++huo4;
	}

	return huo4;
}
pair<int, pair<int, int> > Game::GetChong3Chong4(int row, int col, char chessFlag)
{
	int chong3 = 0, chong4 = 0, tiaochong4 = 0, i, j, num1, num2; // num1,num2 记录两边空格的数量 
	int left1, left2, right1, right2; // left1,righ1 记录碰到空格之前的 chessFlag 数量，.... 

									  // 横
	num1 = num2 = 0;
	left1 = left2 = right1 = right2 = 0;

	for (i = col - 1; i >= 0; --i)
	{
		if (SPACE == chess[row][i].flag)
		{
			++num1;
			if (num1 >= 2)
				break;
			if (i - 1 >= 0 && SPACE == chess[row][i - 1].flag)
				break;
		}
		else if (chessFlag == chess[row][i].flag)
			num1 ? ++left2 : ++left1;
		else
			break;
	}
	// 继续搜索另一边 
	for (i = col + 1; i<SIZE; ++i)
	{
		if (SPACE == chess[row][i].flag)
		{
			++num2;
			if (num2 >= 2)
				break;
			if (i + 1 < SIZE && SPACE == chess[row][i + 1].flag)
				break;
		}
		else if (chessFlag == chess[row][i].flag)
			num2 ? ++right2 : ++right1;
		else
			break;
	}

	if (left1 + left2 + right1 >= 2)
	{
		if (0 == num1 && 2 == left1 + right1 && num2)
			++chong3;
		if (num1 && left1 < 2 && right1 < 2 && left2)
			++chong3;
	}
	if (right1 + right2 + left1 >= 2)
	{
		if (0 == num2 && 2 == left1 + right1 && num1)
			++chong3;
		if (num2 && left1 < 2 && right1 < 2 && right2)
			++chong3;
	}
	if (left1 + left2 + right1 >= 3)
	{
		if (0 == num1 && 3 == left1 + right1 && num2)
			++chong4;
		if (num1 && left1 < 3 && right1 < 3 && left2)
			++tiaochong4;
	}
	if (right1 + right2 + left1 >= 3)
	{
		if (0 == num2 && 3 == left1 + right1 && num1)
			++chong4;
		if (num2 && left1 < 3 && right1 < 3 && right2)
			++tiaochong4;
	}


	// 竖 
	num1 = num2 = 0;
	left1 = left2 = right1 = right2 = 0;
	for (i = row - 1; i >= 0; --i)
	{
		if (SPACE == chess[i][col].flag)
		{
			++num1;
			if (num1 >= 2)
				break;
			if (i - 1 >= 0 && SPACE == chess[i - 1][col].flag)
				break;
		}
		else if (chessFlag == chess[i][col].flag)
			num1 ? ++left2 : ++left1;
		else
			break;
	}
	for (i = row + 1; i<SIZE; ++i)
	{
		if (SPACE == chess[i][col].flag)
		{
			++num2;
			if (num2 >= 2)
				break;
			if (i + 1 < SIZE && SPACE == chess[i + 1][col].flag)
				break;
		}
		else if (chessFlag == chess[i][col].flag)
			num2 ? ++right2 : ++right1;
		else
			break;
	}

	if (left1 + left2 + right1 >= 2)
	{
		if (0 == num1 && 2 == left1 + right1 && num2)
			++chong3;
		if (num1 && left1 < 2 && right1 < 2 && left2)
			++chong3;
	}
	if (right1 + right2 + left1 >= 2)
	{
		if (0 == num2 && 2 == left1 + right1 && num1)
			++chong3;
		if (num2 && left1 < 2 && right1 < 2 && right2)
			++chong3;
	}
	if (left1 + left2 + right1 >= 3)
	{
		if (0 == num1 && 3 == left1 + right1 && num2)
			++chong4;
		if (num1 && left1 < 3 && right1 < 3 && left2)
			++tiaochong4;
	}
	if (right1 + right2 + left1 >= 3)
	{
		if (0 == num2 && 3 == left1 + right1 && num1)
			++chong4;
		if (num2 && left1 < 3 && right1 < 3 && right2)
			++tiaochong4;
	}

	// ' \ '
	num1 = num2 = 0;
	left1 = left2 = right1 = right2 = 0;
	for (i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
	{
		if (SPACE == chess[i][j].flag)
		{
			++num1;
			if (num1 >= 2)
				break;
			if (i - 1 >= 0 && j - 1 >= 0 && SPACE == chess[i - 1][j - 1].flag)
				break;
		}
		else if (chessFlag == chess[i][j].flag)
			num1 ? ++left2 : ++left1;
		else
			break;
	}
	for (i = row + 1, j = col + 1; i<SIZE && j<SIZE; ++i, ++j)
	{
		if (SPACE == chess[i][j].flag)
		{
			++num2;
			if (num2 >= 2)
				break;
			if (i + 1 < SIZE && j + 1 < SIZE && SPACE == chess[i + 1][j + 1].flag)
				break;
		}
		else if (chessFlag == chess[i][j].flag)
			num2 ? ++right2 : ++right1;
		else
			break;
	}

	if (left1 + left2 + right1 >= 2)
	{
		if (0 == num1 && 2 == left1 + right1 && num2)
			++chong3;
		if (num1 && left1 < 2 && right1 < 2 && left2)
			++chong3;
	}
	if (right1 + right2 + left1 >= 2)
	{
		if (0 == num2 && 2 == left1 + right1 && num1)
			++chong3;
		if (num2 && left1 < 2 && right1 < 2 && right2)
			++chong3;
	}
	if (left1 + left2 + right1 >= 3)
	{
		if (0 == num1 && 3 == left1 + right1 && num2)
			++chong4;
		if (num1 && left1 < 3 && right1 < 3 && left2)
			++tiaochong4;
	}
	if (right1 + right2 + left1 >= 3)
	{
		if (0 == num2 && 3 == left1 + right1 && num1)
			++chong4;
		if (num2 && left1 < 3 && right1 < 3 && right2)
			++tiaochong4;
	}

	// ' / '
	num1 = num2 = 0;
	left1 = left2 = right1 = right2 = 0;
	for (i = row - 1, j = col + 1; i >= 0 && j<SIZE; --i, ++j)
	{
		if (SPACE == chess[i][j].flag)
		{
			++num1;
			if (num1 >= 2)
				break;
			if (i - 1 >= 0 && j + 1 < SIZE && SPACE == chess[i - 1][j + 1].flag)
				break;
		}
		else if (chessFlag == chess[i][j].flag)
			num1 ? ++left2 : ++left1;
		else
			break;
	}
	for (i = row + 1, j = col - 1; i<SIZE && j >= 0; ++i, --j)
	{
		if (SPACE == chess[i][j].flag)
		{
			++num2;
			if (num2 >= 2)
				break;
			if (i + 1 < SIZE && j - 1 >= 0 && SPACE == chess[i + 1][j - 1].flag)
				break;
		}
		else if (chessFlag == chess[i][j].flag)
			num2 ? ++right2 : ++right1;
		else
			break;
	}

	if (left1 + left2 + right1 >= 2)
	{
		if (0 == num1 && 2 == left1 + right1 && num2)
			++chong3;
		if (num1 && left1 < 2 && right1 < 2 && left2)
			++chong3;
	}
	if (right1 + right2 + left1 >= 2)
	{
		if (0 == num2 && 2 == left1 + right1 && num1)
			++chong3;
		if (num2 && left1 < 2 && right1 < 2 && right2)
			++chong3;
	}
	if (left1 + left2 + right1 >= 3)
	{
		if (0 == num1 && 3 == left1 + right1 && num2)
			++chong4;
		if (num1 && left1 < 3 && right1 < 3 && left2)
			++tiaochong4;
	}
	if (right1 + right2 + left1 >= 3)
	{
		if (0 == num2 && 3 == left1 + right1 && num1)
			++chong4;
		if (num2 && left1 < 3 && right1 < 3 && right2)
			++tiaochong4;
	}

	return pair<int, pair<int, int> >(chong3, pair<int, int>(chong4, tiaochong4));
}
pair<int, int> Game::GetLian2Lian3(int row, int col, char chessFlag)
{

	// 假设在chess[row][col].flag 落子后，返回构成连2和连3的数量 
	// 严格定义 "连三"，因为禁手规则需要，"连二"的话没必要非常严格。

	int lian2 = 0, lian3 = 0, left, right, i, j, num1, num2;
	bool flag;

	// 横 
	for (i = col - 1, left = 0; i >= 0 && chessFlag == chess[row][i].flag; --i, ++left);
	for (i = col + 1, right = 0; i<SIZE && chessFlag == chess[row][i].flag; ++i, ++right);

	if (1 == left + right)
	{
		for (i = col - left - 1, num1 = 0; i >= 0 && SPACE == chess[row][i].flag; --i, ++num1);
		for (i = col + right + 1, num2 = 0; i<SIZE && SPACE == chess[row][i].flag; ++i, ++num2);
		if (num1 && num2 && num1 + num2 >= 4)
			++lian2;
	}

	if (2 == left + right)
	{
		flag = true;

		if (flag)
		{
			for (i = col - left - 1, num1 = 0; i >= 0 && SPACE == chess[row][i].flag; --i, ++num1);
			for (i = col + right + 1, num2 = 0; i<SIZE && SPACE == chess[row][i].flag; ++i, ++num2);
			if (num1 && num2 && num1 + num2 >= 3)
				++lian3;
		}
	}

	// 竖
	for (i = row - 1, left = 0; i >= 0 && chessFlag == chess[i][col].flag; --i, ++left);
	for (i = row + 1, right = 0; i<SIZE && chessFlag == chess[i][col].flag; ++i, ++right);

	if (1 == left + right)
	{
		for (i = row - left - 1, num1 = 0; i >= 0 && SPACE == chess[i][col].flag; --i, ++num1);
		for (i = row + right + 1, num2 = 0; i<SIZE && SPACE == chess[i][col].flag; ++i, ++num2);
		if (num1 && num2 && num1 + num2 >= 4)
			++lian2;
	}
	if (2 == left + right)
	{
		flag = true;

		if (flag)
		{
			for (i = row - left - 1, num1 = 0; i >= 0 && SPACE == chess[i][col].flag; --i, ++num1);
			for (i = row + right + 1, num2 = 0; i<SIZE && SPACE == chess[i][col].flag; ++i, ++num2);
			if (num1 && num2 && num1 + num2 >= 3)
				++lian3;
		}
	}

	// ' \ '
	for (i = row - 1, j = col - 1, left = 0; i >= 0 && j >= 0 && chessFlag == chess[i][j].flag; --i, --j, ++left);
	for (i = row + 1, j = col + 1, right = 0; i<SIZE && j<SIZE && chessFlag == chess[i][j].flag; ++i, ++j, ++right);

	if (1 == left + right)
	{
		for (i = row - left - 1, j = col - left - 1, num1 = 0; i >= 0 && j >= 0 && SPACE == chess[i][j].flag; --i, --j, ++num1);
		for (i = row + right + 1, j = col + right + 1, num2 = 0; i<SIZE && j<SIZE && SPACE == chess[i][j].flag; ++i, ++j, ++num2);
		if (num1 && num2 && num1 + num2 >= 4)
			++lian2;
	}
	if (2 == left + right)
	{
		flag = true;

		if (flag)
		{
			for (i = row - left - 1, j = col - left - 1, num1 = 0; i >= 0 && j >= 0 && SPACE == chess[i][j].flag; --i, --j, ++num1);
			for (i = row + right + 1, j = col + right + 1, num2 = 0; i<SIZE && j<SIZE && SPACE == chess[i][j].flag; ++i, ++j, ++num2);
			if (num1 && num2 && num1 + num2 >= 3)
				++lian3;
		}
	}

	// ' / '
	for (i = row - 1, j = col + 1, left = 0; i >= 0 && j<SIZE && chessFlag == chess[i][j].flag; --i, ++j, ++left);
	for (i = row + 1, j = col - 1, right = 0; i<SIZE && j >= 0 && chessFlag == chess[i][j].flag; ++i, --j, ++right);

	if (1 == left + right)
	{
		for (i = row - left - 1, j = col + left + 1, num1 = 0; i >= 0 && j<SIZE && SPACE == chess[i][j].flag; --i, ++j, ++num1);
		for (i = row + right + 1, j = col - right - 1, num2 = 0; i<SIZE && j >= 0 && SPACE == chess[i][j].flag; ++i, --j, ++num2);
		if (num1 && num2 && num1 + num2 >= 4)
			++lian2;
	}
	if (2 == left + right)
	{
		flag = true;

		if (flag)
		{
			for (i = row - left - 1, j = col + left + 1, num1 = 0; i >= 0 && j<SIZE && SPACE == chess[i][j].flag; --i, ++j, ++num1);
			for (i = row + right + 1, j = col - right - 1, num2 = 0; i<SIZE && j >= 0 && SPACE == chess[i][j].flag; ++i, --j, ++num2);
			if (num1 && num2 && num1 + num2 >= 3)
				++lian3;
		}
	}

	return pair<int, int>(lian2, lian3);
}
pair<int, int> Game::GetTiao2Tiao3(int row, int col, char chessFlag)
{
	// 假设在chess[row][col].flag 落子后，返回构成跳2和跳3的数量 
	// 严格定义 "跳三"，因为禁手规则需要，跳二的话没必要非常严格。
	int tiao2 = 0, tiao3 = 0, i, j, num1, num2;
	int left1, left2, right1, right2;  // 这里和 GetChong3Chong4() 中的含义 相同 
	bool flag;

	// 横
	num1 = num2 = 0;
	left1 = left2 = right1 = right2 = 0;

	for (i = col - 1; i >= 0; --i)
	{
		if (SPACE == chess[row][i].flag)
		{
			++num1;
			if (num1 >= 2)
				break;
			if (i - 1 >= 0 && SPACE == chess[row][i - 1].flag)
				break;
		}
		else if (chessFlag == chess[row][i].flag)
			num1 ? ++left2 : ++left1;
		else
			break;
	}
	// 继续搜索另一边 
	for (i = col + 1; i<SIZE; ++i)
	{
		if (SPACE == chess[row][i].flag)
		{
			++num2;
			if (num2 >= 2)
				break;
			if (i + 1 < SIZE && SPACE == chess[row][i + 1].flag)
				break;
		}
		else if (chessFlag == chess[row][i].flag)
			num2 ? ++right2 : ++right1;
		else
			break;
	}

	if (1 == left1 + left2 + right1 && 2 == num1 && col - left1 - left2 - 2 >= 0 && col + right1 + 1 < SIZE
		&& SPACE == chess[row][col - left1 - left2 - 2].flag && SPACE == chess[row][col + right1 + 1].flag)
		++tiao2;
	if (1 == right1 + right2 + left1 && 2 == num2 && col - left1 - 1 >= 0 && col + right1 + right2 + 2 < SIZE
		&& SPACE == chess[row][col - left1 - 1].flag && SPACE == chess[row][col + right1 + right2 + 2].flag)
		++tiao2;

	if (2 == left1 + left2 + right1 && 2 == num1 && col - left1 - left2 - 2 >= 0 && col + right1 + 1 < SIZE
		&& SPACE == chess[row][col - left1 - left2 - 2].flag && SPACE == chess[row][col + right1 + 1].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (col - left1 - left2 - 3 >= 0 && chessFlag == chess[row][col - left1 - left2 - 3].flag)
				flag = false;
			if (col + right1 + 2 < SIZE && chessFlag == chess[row][col + right1 + 2].flag)
				flag = false;
		}
		if (flag)
			++tiao3;
	}
	if (2 == right1 + right2 + left1 && 2 == num2 && col - left1 - 1 >= 0 && col + right1 + right2 + 2 < SIZE
		&& SPACE == chess[row][col - left1 - 1].flag && SPACE == chess[row][col + right1 + right2 + 2].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (col - left1 - 2 >= 0 && chessFlag == chess[row][col - left1 - 2].flag)
				flag = false;
			if (col + right1 + right2 + 3 < SIZE && chessFlag == chess[row][col + right1 + right2 + 3].flag)
				flag = false;
		}
		if (flag)
			++tiao3;
	}

	// 竖 
	num1 = num2 = 0;
	left1 = left2 = right1 = right2 = 0;
	for (i = row - 1; i >= 0; --i)
	{
		if (SPACE == chess[i][col].flag)
		{
			++num1;
			if (num1 >= 2)
				break;
			if (i - 1 >= 0 && SPACE == chess[i - 1][col].flag)
				break;
		}
		else if (chessFlag == chess[i][col].flag)
			num1 ? ++left2 : ++left1;
		else
			break;
	}
	for (i = row + 1; i<SIZE; ++i)
	{
		if (SPACE == chess[i][col].flag)
		{
			++num2;
			if (num2 >= 2)
				break;
			if (i + 1 < SIZE && SPACE == chess[i + 1][col].flag)
				break;
		}
		else if (chessFlag == chess[i][col].flag)
			num2 ? ++right2 : ++right1;
		else
			break;
	}

	if (1 == left1 + left2 + right1 && 2 == num1 && row - left1 - left2 - 2 >= 0 && row + right1 + 1 < SIZE
		&& SPACE == chess[row - left1 - left2 - 2][col].flag && SPACE == chess[row + right1 + 1][col].flag)
		++tiao2;
	if (1 == right1 + right2 + left1 && 2 == num2 && row - left1 - 1 >= 0 && row + right1 + right2 + 2 < SIZE
		&& SPACE == chess[row - left1 - 1][col].flag && SPACE == chess[row + right1 + right2 + 2][col].flag)
		++tiao2;

	if (2 == left1 + left2 + right1 && 2 == num1 && row - left1 - left2 - 2 >= 0 && row + right1 + 1 < SIZE
		&& SPACE == chess[row - left1 - left2 - 2][col].flag && SPACE == chess[row + right1 + 1][col].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (row - left1 - left2 - 3 >= 0 && chessFlag == chess[row - left1 - left2 - 3][col].flag)
				flag = false;
			if (row + right1 + 2 < SIZE && chessFlag == chess[row + right1 + 2][col].flag)
				flag = false;
		}
		if (flag)
			++tiao3;
	}
	if (2 == right1 + right2 + left1 && 2 == num2 && row - left1 - 1 >= 0 && row + right1 + right2 + 2 < SIZE
		&& SPACE == chess[row - left1 - 1][col].flag && SPACE == chess[row + right1 + right2 + 2][col].flag)

	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (row - left1 - 2 >= 0 && chessFlag == chess[row - left1 - 2][col].flag)
				flag = false;
			if (row + right1 + right2 + 3 < SIZE && chessFlag == chess[row + right1 + right2 + 3][col].flag)
				flag = false;
		}
		if (flag)
			++tiao3;
	}

	// ' \ '
	num1 = num2 = 0;
	left1 = left2 = right1 = right2 = 0;
	for (i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
	{
		if (SPACE == chess[i][j].flag)
		{
			++num1;
			if (num1 >= 2)
				break;
			if (i - 1 >= 0 && j - 1 >= 0 && SPACE == chess[i - 1][j - 1].flag)
				break;
		}
		else if (chessFlag == chess[i][j].flag)
			num1 ? ++left2 : ++left1;
		else
			break;
	}
	for (i = row + 1, j = col + 1; i<SIZE && j<SIZE; ++i, ++j)
	{
		if (SPACE == chess[i][j].flag)
		{
			++num2;
			if (num2 >= 2)
				break;
			if (i + 1 < SIZE && j + 1 < SIZE && SPACE == chess[i + 1][j + 1].flag)
				break;
		}
		else if (chessFlag == chess[i][j].flag)
			num2 ? ++right2 : ++right1;
		else
			break;
	}

	if (1 == left1 + left2 + right1 && 2 == num1 && row - left1 - left2 - 2 >= 0 && row + right1 + 1 < SIZE
		&& col - left1 - left2 - 2 >= 0 && col + right1 + 1 < SIZE
		&& SPACE == chess[row - left1 - left2 - 2][col - left1 - left2 - 2].flag
		&& SPACE == chess[row + right1 + 1][col + right1 + 1].flag)
		++tiao2;
	if (1 == right1 + right2 + left1 && 2 == num2 && row - left1 - 1 >= 0 && row + right1 + right2 + 2 < SIZE
		&& col - left1 - 1 >= 0 && col + right1 + right2 + 2 < SIZE
		&& SPACE == chess[row - left1 - 1][col - left1 - 1].flag
		&& SPACE == chess[row + right1 + right2 + 2][col + right1 + right2 + 2].flag)
		++tiao2;

	if (2 == left1 + left2 + right1 && 2 == num1 && row - left1 - left2 - 2 >= 0 && row + right1 + 1 < SIZE
		&& col - left1 - left2 - 2 >= 0 && col + right1 + 1 < SIZE
		&& SPACE == chess[row - left1 - left2 - 2][col - left1 - left2 - 2].flag
		&& SPACE == chess[row + right1 + 1][col + right1 + 1].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (row - left1 - left2 - 3 >= 0 && col - left1 - left2 - 3 >= 0 && chessFlag == chess[row - left1 - left2 - 3][col - left1 - left2 - 3].flag)
				flag = false;
			if (row + right1 + 2 < SIZE && col + right1 + 2 < SIZE && chessFlag == chess[row + right1 + 2][col + right1 + 2].flag)
				flag = false;
		}
		if (flag)
			++tiao3;
	}
	if (2 == right1 + right2 + left1 && 2 == num2 && row - left1 - 1 >= 0 && row + right1 + right2 + 2 < SIZE
		&& col - left1 - 1 >= 0 && col + right1 + right2 + 2 < SIZE
		&& SPACE == chess[row - left1 - 1][col - left1 - 1].flag
		&& SPACE == chess[row + right1 + right2 + 2][col + right1 + right2 + 2].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (row - left1 - 2 >= 0 && col - left1 - 2 >= 0 && chessFlag == chess[row - left1 - 2][col - left1 - 2].flag)
				flag = false;
			if (row + right1 + right2 + 3 < SIZE && col + right1 + right2 + 3 < SIZE && chessFlag == chess[row + right1 + right2 + 3][col + right1 + right2 + 3].flag)
				flag = false;
		}
		if (flag)
			++tiao3;
	}

	// ' / '
	num1 = num2 = 0;
	left1 = left2 = right1 = right2 = 0;
	for (i = row - 1, j = col + 1; i >= 0 && j<SIZE; --i, ++j)
	{
		if (SPACE == chess[i][j].flag)
		{
			++num1;
			if (num1 >= 2)
				break;
			if (i - 1 >= 0 && j + 1 < SIZE && SPACE == chess[i - 1][j + 1].flag)
				break;
		}
		else if (chessFlag == chess[i][j].flag)
			num1 ? ++left2 : ++left1;
		else
			break;
	}
	for (i = row + 1, j = col - 1; i<SIZE && j >= 0; ++i, --j)
	{
		if (SPACE == chess[i][j].flag)
		{
			++num2;
			if (num2 >= 2)
				break;
			if (i + 1 < SIZE && j - 1 >= 0 && SPACE == chess[i + 1][j - 1].flag)
				break;
		}
		else if (chessFlag == chess[i][j].flag)
			num2 ? ++right2 : ++right1;
		else
			break;
	}

	if (1 == left1 + left2 + right1 && 2 == num1 && row - left1 - left2 - 2 >= 0 && col + left1 + left2 + 2 < SIZE
		&& row + right1 + 1 < SIZE && col - right1 - 1 >= 0
		&& SPACE == chess[row - left1 - left2 - 2][col + left1 + left2 + 2].flag
		&& SPACE == chess[row + right1 + 1][col - right1 - 1].flag)
		++tiao2;
	if (1 == right1 + right2 + left1 && 2 == num2 && row - left1 - 1 >= 0 && col + left1 + 1 < SIZE
		&& row + right1 + right2 + 2 < SIZE && col - right1 - right2 - 2 >= 0
		&& SPACE == chess[row - left1 - 1][col + left1 + 1].flag
		&& SPACE == chess[row + right1 + right2 + 2][col - right1 - right2 - 2].flag)
		++tiao2;

	if (2 == left1 + left2 + right1 && 2 == num1 && row - left1 - left2 - 2 >= 0 && col + left1 + left2 + 2 < SIZE
		&& row + right1 + 1 < SIZE && col - right1 - 1 >= 0
		&& SPACE == chess[row - left1 - left2 - 2][col + left1 + left2 + 2].flag
		&& SPACE == chess[row + right1 + 1][col - right1 - 1].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (row - left1 - left2 - 3 >= 0 && col + left1 + left2 + 3 < SIZE && chessFlag == chess[row - left1 - left2 - 3][col + left1 + left2 + 3].flag)
				flag = false;
			if (row + right1 + 2 < SIZE && col - right1 - 2 >= 0 && chessFlag == chess[row + right1 + 2][col - right1 - 2].flag)
				flag = false;
		}
		if (flag)
			++tiao3;
	}
	if (2 == right1 + right2 + left1 && 2 == num2 && row - left1 - 1 >= 0 && col + left1 + 1 < SIZE
		&& row + right1 + right2 + 2 < SIZE && col - right1 - right2 - 2 >= 0
		&& SPACE == chess[row - left1 - 1][col + left1 + 1].flag
		&& SPACE == chess[row + right1 + right2 + 2][col - right1 - right2 - 2].flag)
	{
		flag = true;
		if (BLACK_CHESS == chessFlag)
		{
			if (row - left1 - 2 >= 0 && col + left1 + 2 < SIZE && chessFlag == chess[row - left1 - 2][col + left1 + 2].flag)
				flag = false;
			if (row + right1 + right2 + 3 < SIZE && col - right1 - right2 - 3 >= 0 && chessFlag == chess[row + right1 + right2 + 3][col - right1 - right2 - 3].flag)
				flag = false;
		}
		if (flag)
			++tiao3;
	}
	return pair<int, int>(tiao2, tiao3);
}
int Game::GetCheng5ChangLian(int row, int col, char chessFlag)
{
	// 假设在chess[row][col].flag 落子后,是否成5（或长连),返回1表示五连，返回2表示长连,否则返回0 
	int left, right, i, j;
	// 横 
	for (i = col - 1, left = 0; i >= 0 && chessFlag == chess[row][i].flag; --i, ++left);
	for (i = col + 1, right = 0; i<SIZE && chessFlag == chess[row][i].flag; ++i, ++right);

	if (4 == left + right)
		return 1;
	else if (left + right >= 5)
		return 2;

	// 竖
	for (i = row - 1, left = 0; i >= 0 && chessFlag == chess[i][col].flag; --i, ++left);
	for (i = row + 1, right = 0; i<SIZE && chessFlag == chess[i][col].flag; ++i, ++right);

	if (4 == left + right)
		return 1;
	else if (left + right >= 5)
		return 2;

	// ' \ '
	for (i = row - 1, j = col - 1, left = 0; i >= 0 && j >= 0 && chessFlag == chess[i][j].flag; --i, --j, ++left);
	for (i = row + 1, j = col + 1, right = 0; i<SIZE && j<SIZE && chessFlag == chess[i][j].flag; ++i, ++j, ++right);

	if (4 == left + right)
		return 1;
	else if (left + right >= 5)
		return 2;

	// ' / '
	for (i = row - 1, j = col + 1, left = 0; i >= 0 && j<SIZE && chessFlag == chess[i][j].flag; --i, ++j, ++left);
	for (i = row + 1, j = col - 1, right = 0; i<SIZE && j >= 0 && chessFlag == chess[i][j].flag; ++i, --j, ++right);

	if (4 == left + right)
		return 1;
	else if (left + right >= 5)
		return 2;

	return 0;
}
//void Game::Search(int row, int col, int chessFlag)
//{
//	//初始化
//	changlian = cheng5 = huo4 = chong4 = tiaochong4 = lian3 = tiao3 = chong3 = lian2 = tiao2 = 0;
//	int res;
//	pair<int, int> pi;
//	pair<int, pair<int, int> > pip;
//
//	// 五连，长连
//	res = GetCheng5ChangLian(row, col, chessFlag);
//	if (1 == res)
//		cheng5 = 1;
//	else if (2 == res)
//		changlian = 1;
//
//	// 活四
//	huo4 = GetHuo4(row, col, chessFlag);
//
//	// 冲三，冲四
//	pip = GetChong3Chong4(row, col, chessFlag);
//	chong3 = pip.first;
//	chong4 = pip.second.first;
//	tiaochong4 = pip.second.second;
//
//	// 活三： 包括 连三 和 跳三
//	// 活二： 包括 连二 和 跳二 ，（ 这里还是把跳二 和连二 分开了，开局时需要）
//	pi = GetLian2Lian3(row, col, chessFlag);
//	lian2 = pi.first;
//	lian3 = pi.second;
//
//	pi = GetTiao2Tiao3(row, col, chessFlag);
//	tiao2 = pi.first;
//	tiao3 = pi.second;
//}
int Game::AddScore(int row, int col, char chessFlag)
{
	// 通过给这个位置加分来实现 防守对方的进攻方向
	// 原理：将分值与这个点周围有多少空格和对方的棋子挂钩
	int score = 0;
	int s = 0, y = 0, m = 0;
	char other = (BLACK_CHESS == chessFlag ? WHITE_CHESS : BLACK_CHESS);

	for (int i = max(0, row - 2); i <= min(SIZE - 1, row + 2); ++i)
	{
		for (int j = max(0, col - 2); j <= min(SIZE - 1, col + 2); ++j)
		{
			if (SPACE == chess[i][j].flag)
				++s;
			else if (other == chess[i][j].flag)
				++y;
			else
				++m;
		}
	}

	score = y * 30 + s * 10 + m * 10;
	return score;
}
int Game::GetScore(int row, int col, char chessFlag, char flag)
{
	int score = 10;

	if (chessFlag == flag) // 对 自己而言
	{
		if (BLACK_CHESS == chessFlag && IsKinjite(row, col)) //是自己的禁手点 
			return -1;
		Search(row, col, chessFlag); //
		if (changlian || cheng5)
			score += 5000000;
		if (huo4)
			score += 250000;
		if (chong4 + tiaochong4 >= 2)
			score += 250000;
		if ((lian3 + tiao3) && (chong4 + tiaochong4))
			score += 200000;
		if (lian3 + tiao3 >= 2)
			score += 8000;

		score += chong4 * 230;
		score += tiaochong4 * 110;
		score += lian3 * 320;
		score += tiao3 * 150; //tiao3必定多加了一个tiao2的分
		score += lian2 * 160;
		score += tiao2 * 150;

		if ((chong4 + tiaochong4 + huo4) && (lian2 + tiao2 >= 2))
			score += 220;
		if ((lian3 + tiao3) && (lian2 + tiao2 >= 2))
			score += 200;
		if (chong3 && chong4)
			score += 100;
		if (chong3 >= 2 && tiaochong4)
			score += 100;
		if (chong3 >= 2)
			score += 100;
		if (chong3 && (lian2 + tiao2))
			score += 50;

		score += chong3 * 40;
		score += chong1 * 20;
		score += huo1 * 10;
		score += chong2 * 20;
	}
	else    // 对 对方而言
	{
		if (BLACK_CHESS == chessFlag && IsKinjite(row, col)) // 是对方的禁手点
			return -1;
		Search(row, col, chessFlag); //
		if (changlian || cheng5)
			score += 1000000;
		if (huo4)
			score += 45000;
		if (chong4 + tiaochong4 >= 2)
			score += 45000;
		if ((lian3 + tiao3) && (chong4 + tiaochong4))
			score += 40000;
		if (lian3 + tiao3 >= 2)
			score += 1900;

		score += chong4 * 230;
		score += tiaochong4 * 110;
		score += lian3 * 320;
		score += tiao3 * 150; //tiao3必定多加了一个tiao2的分
		score += lian2 * 160;
		score += tiao2 * 150;

		if ((chong4 + tiaochong4 + huo4) && (lian2 + tiao2 >= 2))
			score += 220;
		if ((lian3 + tiao3) && (lian2 + tiao2 >= 2))
			score += 200;
		if (chong3 && chong4)
			score += 100;
		if (chong3 >= 2 && tiaochong4)
			score += 100;
		if (chong3 >= 2)
			score += 100;
		if (chong3 && (lian2 + tiao2))
			score += 50;

		score += chong3 * 40;
		score += chong1 * 20;
		score += huo1 * 10;
		score += chong2 * 20;
	}

	if (score >= 1900 || isDefend)
		score += AddScore(row, col, chessFlag); //
	return score;
}
int Game::GetScoreForComputer(int row, int col, char chessFlag)
{
	return GetScore(row, col, chessFlag, cComputer);
}
int Game::GetScoreForPeople(int row, int col, char chessFlag)
{
	return GetScore(row, col, chessFlag, cPeople);
}
//int Game::Evaluate(int left1, int right1, int top1, int bottom1)
//{
//	int cScore = 0, pScore = 0;
//	cScore = Evaluate_Value(cComputer, cComputer, left1, right1, top1, bottom1);
//	/*+ Evaluate_Value(cPeople, cComputer, left1, right1, top1, bottom1);*/
//	pScore = /*Evaluate_Value(cComputer, cPeople, left1, right1, top1, bottom1);*/
//		Evaluate_Value(cPeople, cPeople, left1, right1, top1, bottom1);
//	return cScore - pScore;
//
//}
int Game::Evaluate_Value(int chessFlag, int left1, int right1, int top1, int bottom1)
{
	int changlian_C, cheng5_C, huo4_C, chong4_C, tiaochong4_C, lian3_C, tiao3_C, chong3_C, lian2_C, tiao2_C, chong2_C, chong1_C, huo1_C, dbchong4_C, chong4huo3_C, dbhuo3_C;
	changlian_C = cheng5_C = huo4_C = chong4_C = tiaochong4_C = lian3_C = tiao3_C = chong3_C = lian2_C = tiao2_C = chong2_C = chong1_C = huo1_C = dbchong4_C = chong4huo3_C = dbhuo3_C = 0;
	//针对计算机棋型评估

	int changlian_P, cheng5_P, huo4_P, chong4_P, tiaochong4_P, lian3_P, tiao3_P, chong3_P, lian2_P, tiao2_P, chong2_P, chong1_P, huo1_P, dbchong4_P, chong4huo3_P, dbhuo3_P;
	changlian_P = cheng5_P = huo4_P = chong4_P = tiaochong4_P = lian3_P = tiao3_P = chong3_P = lian2_P = tiao2_P = chong2_P = chong1_P = huo1_P = dbchong4_P = chong4huo3_P = dbhuo3_P = 0;

	//针对人棋型评估
	for (int i = top1; i <= bottom1; i++)
	{
		for (int j = left1; j <= right1; j++)
		{
			if (chess[i][j].flag != SPACE && chess[i][j].flag == cComputer)
			{
				Search(i, j, cComputer);
				changlian_C += changlian;
				cheng5_C += cheng5;
				huo4_C += huo4;
				chong4_C += chong4;
				tiaochong4_C += tiaochong4;
				lian3_C += lian3;
				tiao3_C += tiao3;
				chong3_C += chong3;
				lian2_C += lian2;
				chong2_C += chong2;
				tiao2_C += tiao2;
				if (chong4 + tiaochong4 >= 2)
				{
					dbchong4_C++;
				}
				if ((lian3 + tiao3) && (chong4 + tiaochong4))
				{
					chong4huo3_C++;
				}
				if (lian3 + tiao3 >= 2)
				{
					dbhuo3_C++;
				}
			}
			if (chess[i][j].flag != SPACE && chess[i][j].flag == cPeople)
			{
				Search(i, j, cPeople);
				changlian_P += changlian;
				cheng5_P += cheng5;
				huo4_P += huo4;
				chong4_P += chong4;
				tiaochong4_P += tiaochong4;
				lian3_P += lian3;
				tiao3_P += tiao3;
				chong3_P += chong3;
				lian2_P += lian2;
				chong2_P += chong2;
				tiao2_P += tiao2;
				if (chong4 + tiaochong4 >= 2)
				{
					dbchong4_P++;
				}
				if ((lian3 + tiao3) && (chong4 + tiaochong4))
				{
					chong4huo3_P++;
				}
				if (lian3 + tiao3 >= 2)
				{
					dbhuo3_P++;
				}
			}


		}
	}
	//统计电脑棋型
	changlian_C = changlian_C / 6;
	cheng5_C = cheng5_C / 5;
	huo4_C = huo4_C / 4;
	chong4_C = chong4_C / 4;
	tiaochong4_C = tiaochong4_C / 4;
	lian3_C = lian3_C / 3;
	tiao3_C = tiao3_C / 3;
	chong3_C = chong3_C / 3;
	lian2_C = lian2_C / 2;
	tiao2_C = tiao2_C / 2;
	chong2_C = chong2_C / 2;
	//统计人棋型
	changlian_P = changlian_P / 6;
	cheng5_P = cheng5_P / 5;
	huo4_P = huo4_P / 4;
	chong4_P = chong4_P / 4;
	tiaochong4_P = tiaochong4_P / 4;
	lian3_P = lian3_P / 3;
	tiao3_P = tiao3_P / 3;
	chong3_P = chong3_P / 3;
	lian2_P = lian2_P / 2;
	tiao2_P = tiao2_P / 2;
	chong2_P = chong2_P / 2;
	int cScore = 10;
	int pScore = 10;

	if (chessFlag == cComputer)//最后一步棋是电脑下的棋，针对人下的棋的评分会更高
	{
		//电脑棋型加分
		if (changlian_C || cheng5_C)
			cScore += 500000;
		cScore += huo4_C * 60000;
		cScore += dbchong4_C * 55000;
		cScore += chong4huo3_C * 50000;
		cScore += dbhuo3_C * 800;
		cScore += chong4_C * 230;
		cScore += tiaochong4_C * 110;
		cScore += lian3_C * 320;
		cScore += tiao3_C * 150; //tiao3必定多加了一个tiao2的分
		cScore += lian2_C * 160;
		cScore += tiao2_C * 150;
		cScore += chong3_C * 40;
		cScore += chong1_C * 20;
		cScore += huo1_C * 10;
		cScore += chong2_C * 20;
		//人棋型加分
		if (changlian_P || cheng5_P)
			pScore += 500000;
		pScore += huo4_P * 200000;
		pScore += chong4_P * 200000;
		pScore += tiaochong4_P * 200000;
		cScore += dbhuo3_P * 500;
		pScore += lian3_P * 4000;
		pScore += tiao3_P * 4000; //tiao3必定多加了一个tiao2的分
		pScore += lian2_P * 260;
		pScore += tiao2_P * 250;
		pScore += chong3_P * 70;
		pScore += chong1_P * 20;
		pScore += huo1_P * 10;
		pScore += chong2_P * 30;

	}
	if (chessFlag == cPeople)//最后一步棋是人下的棋，针对电脑下的棋的评分会更高
	{
		//电脑棋型加分
		if (changlian_C || cheng5_C)
			cScore += 500000;
		cScore += huo4_C * 200000;
		cScore += chong4_C * 200000;
		cScore += tiaochong4_C * 200000;
		cScore += dbhuo3_C * 500;
		cScore += lian3_C * 4000;
		cScore += tiao3_C * 4000; //tiao3必定多加了一个tiao2的分
		cScore += lian2_C * 260;
		cScore += tiao2_C * 250;
		cScore += chong3_C * 70;
		cScore += chong1_C * 20;
		cScore += huo1_C * 10;
		cScore += chong2_C * 30;



		//人棋型加分
		if (changlian_P || cheng5_P)
			pScore += 500000;
		pScore += huo4_P * 60000;
		cScore += dbchong4_P * 55000;
		cScore += chong4huo3_P * 50000;
		cScore += dbhuo3_P * 800;
		pScore += chong4_P * 230;
		pScore += tiaochong4_P * 110;
		pScore += lian3_P * 320;
		pScore += tiao3_P * 150; //tiao3必定多加了一个tiao2的分
		pScore += lian2_P * 160;
		pScore += tiao2_P * 150;
		pScore += chong3_P * 40;
		pScore += chong1_P * 20;
		pScore += huo1_P * 10;
		pScore += chong2_P * 20;
	}

	/*int cScore = 10;*/

	//if (BLACK_CHESS == chessFlag && IsKinjite(i, j)) //是自己的禁手点 
	//	return -1;
	//if (changlian || cheng5)
	//	score += 5000000;
	//if (huo4)
	//	score += 250000;
	//if (chong4 + tiaochong4 >= 2)
	//	score += 250000;
	//if ((lian3 + tiao3) && (chong4 + tiaochong4))
	//	score += 200000;
	//if (lian3 + tiao3 >= 2)
	//	score += 8000;
	//if (changlian_C || cheng5_C)
	//	cScore += 500000;
	//cScore += huo4_C * 10000;
	//cScore += chong4_C * 230;
	//cScore += tiaochong4_C * 110;
	//cScore += lian3_C * 320;
	//cScore += tiao3_C * 150; //tiao3必定多加了一个tiao2的分
	//cScore += lian2_C * 160;
	//cScore += tiao2_C * 150;

	/*if ((chong4_1 + tiaochong4_1 + huo4_1) && (lian2_1 + tiao2_1 >= 2))
	score += 220;
	if ((lian3_1 + tiao3_1) && (lian2_1 + tiao2_1 >= 2))
	score += 200;
	if (chong3_1 && chong4_1)
	score += 100;
	if (chong3_1 >= 2 && tiaochong4_1)
	score += 100;
	if (chong3_1 >= 2)
	score += 100;
	if (chong3_1 && (lian2_1 + tiao2_1))
	score += 50;
	*/
	//cScore += chong3_C * 40;
	//cScore += chong1_C * 20;
	//cScore += huo1_C * 10;
	//cScore += chong2_C * 20;

	//int pScore = 10;
	//if (changlian_P || cheng5_P)
	//	cScore += 500000;
	//pScore += huo4_P * 10000;
	//pScore += chong4_P * 230;
	//pScore += tiaochong4_P * 110;
	//pScore += lian3_P * 320;
	//pScore += tiao3_P * 150; //tiao3必定多加了一个tiao2的分
	//pScore += lian2_P * 160;
	//pScore += tiao2_P * 150;
	//pScore += chong3_P * 40;
	//pScore += chong1_P * 20;
	//pScore += huo1_P * 10;
	//pScore += chong2_P * 20;

	//	else    // 对 对方而言
	//	{
	//		//if (BLACK_CHESS == chessFlag && IsKinjite(i,j)) // 是对方的禁手点
	//		//	return -1;
	//		//if (changlian || cheng5)
	//		//	score += 1000000;
	//		//if (huo4)
	//		//	score += 45000;
	//		//if (chong4 + tiaochong4 >= 2)
	//		//	score += 45000;
	//		//if ((lian3 + tiao3) && (chong4 + tiaochong4))
	//		//	score += 40000;
	//		//if (lian3 + tiao3 >= 2)
	//		//	score += 1900;
	//		if (changlian_1 || cheng5_1)
	//			score += 100000;
	//		score += huo4_1 * 8000;
	//		score += chong4_1 * 230;
	//		score += tiaochong4_1 * 110;
	//		score += lian3_1 * 320;
	//		score += tiao3_1 * 150; //tiao3必定多加了一个tiao2的分
	//		score += lian2_1 * 160;
	//		score += tiao2_1 * 150;
	//
	//	/*	if ((chong4_1 + tiaochong4_1 + huo4_1) && (lian2_1 + tiao2_1 >= 2))
	//			score += 220;
	//		if ((lian3_1 + tiao3_1) && (lian2_1 + tiao2_1 >= 2))
	//			score += 200;
	//		if (chong3_1 && chong4_1)
	//			score += 100;
	//		if (chong3_1 >= 2 && tiaochong4_1)
	//			score += 100;
	//		if (chong3_1 >= 2)
	//			score += 100;
	//		if (chong3_1 && (lian2_1 + tiao2_1))
	//			score += 50;
	//*/
	//		score += chong3_1 * 40;
	//		score += chong1_1 * 20;
	//		score += huo1_1 * 10;
	//		score += chong2_1 * 20;
	//
	//		//if (score >= 1900 || isDefend)
	//		//	score += AddScore(i, j, chessFlag); //
	//	}

	return cScore - pScore;
}


void Game::Search(int row, int col, int chessFlag)
{
	changlian = cheng5 = huo4 = chong4 = tiaochong4 = lian3 = tiao3 = chong3 = lian2 = tiao2 = 0;
	Count count[4];//分别代表四个方向的紧邻点数量
	memset(count, 0, sizeof(count));
	Findcount(row, col, chessFlag, count);
	int left[5], right[5];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			left[j] = chess[DirectionCount_New(row, col, -count[i].left - j - 1, i).x][DirectionCount_New(row, col, -count[i].left - j - 1, i).y].flag;
			right[j] = chess[DirectionCount_New(row, col, count[i].right + j + 1, i).x][DirectionCount_New(row, col, count[i].right + j + 1, i).y].flag;
		}
		GetCheng5_New(chessFlag, count[i]);
		if (left[0] == (chessFlag + 1) % 2 + 4 && right[0] == (chessFlag + 1) % 2 + 4 ||
			left[0] == 0 && right[0] == (chessFlag + 1) % 2 + 4 ||
			left[0] == (chessFlag + 1) % 2 + 4 && right[0] == 0)
			continue;
		if (count[i].left + count[i].right == 3)
			GetHuo4Chong4_New(row, col, i, count[i], chessFlag, left, right);
		else if (count[i].left + count[i].right == 2)
			GetLian3Chong3TiaoChong4_New(row, col, i, count[i], chessFlag, left, right);
		else if (count[i].left + count[i].right == 1)
			GetLian2Tiao3Chong3TiaoChong4_New(row, col, i, count[i], chessFlag, left, right);
		else if (count[i].left + count[i].right == 0)
			GetTiao2Tiao3Tiaochong4_New(row, col, i, count[i], chessFlag, left, right);
	}
}

void Game::GetTiao2Tiao3Tiaochong4_New(int row, int col, int n, Count count, int chessFlag, int left[5], int right[5])
{
	if (left[0] == left[1] == SPACE&&right[0] == right[1] == SPACE);
	else
	{
		if (left[0] == SPACE && left[1] == chessFlag && left[2] == chessFlag && left[3] == chessFlag && (chessFlag != BLACK_CHESS || left[4] != chessFlag))
			tiaochong4++;
		if (right[0] == SPACE && right[1] == chessFlag && right[2] == chessFlag && right[3] == chessFlag && (chessFlag != BLACK_CHESS || right[4] != chessFlag))
			tiaochong4++;
		if (left[0] == SPACE && left[1] == chessFlag && left[2] == chessFlag && left[3] == SPACE && right[0] == SPACE)
		{
			if (chessFlag != BLACK_CHESS)
				tiao3++;
			else if (left[4] != chessFlag && right[1] != chessFlag)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, -count.left - 1, n).x, DirectionCount_New(row, col, -count.left - 1, n).y))
					tiao3++;
				chess[row][col].flag = temp;
			}
		}
		else if (right[0] == SPACE && right[1] == chessFlag && right[2] == chessFlag && right[3] == SPACE && left[0] == SPACE)
		{
			if (chessFlag != BLACK_CHESS)
				tiao3++;
			else if (right[4] != chessFlag && left[1] != chessFlag)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, count.right + 1, n).x, DirectionCount_New(row, col, count.right + 1, n).y))
					tiao3++;
				chess[row][col].flag = temp;
			}
		}
		if (left[0] == SPACE && left[1] == chessFlag && left[2] == chessFlag)
		{
			if (left[3] != SPACE && left[3] != chessFlag && left[3] != 0 && right[0] == SPACE && (chessFlag != BLACK_CHESS || right[1] != chessFlag))
				chong3++;
			else if (left[3] = SPACE && right[0] != SPACE && right[0] != chessFlag && right[0] != 0 && (chessFlag != BLACK_CHESS || left[4] != chessFlag))
				chong3++;
		}
		else if (right[0] == SPACE && right[1] == chessFlag && right[2] == chessFlag)
		{
			if (right[3] != SPACE && right[3] != chessFlag && right[3] != 0 && left[0] == SPACE && (chessFlag != BLACK_CHESS || left[1] != chessFlag))
				chong3++;
			else if (right[3] = SPACE && left[0] != SPACE && left[0] != chessFlag && left[0] != 0 && (chessFlag != BLACK_CHESS || right[4] != chessFlag))
				chong3++;
		}
		if (left[0] == SPACE && left[1] == SPACE && left[2] == chessFlag && left[3] == chessFlag && (chessFlag != BLACK_CHESS || left[4] != chessFlag))
			chong3++;
		if (right[0] == SPACE && right[1] == SPACE && right[2] == chessFlag && right[3] == chessFlag && (chessFlag != BLACK_CHESS || right[4] != chessFlag))
			chong3++;
		if (left[0] == SPACE && left[1] == chessFlag && left[2] == SPACE && left[3] == chessFlag && (chessFlag != BLACK_CHESS || left[4] != chessFlag))
			chong3++;
		if (right[0] == SPACE && right[1] == chessFlag && right[2] == SPACE && right[3] == chessFlag && (chessFlag != BLACK_CHESS || right[4] != chessFlag))
			chong3++;
		if (left[0] == SPACE && left[1] == chessFlag && right[0] == SPACE && right[1] == chessFlag && (chessFlag != BLACK_CHESS || left[2] != chessFlag && right[4] != chessFlag))
			chong3++;
		if (left[0] == SPACE && left[1] == chessFlag && left[2] == SPACE && right[0] == SPACE)
		{
			if (left[3] == SPACE && (chessFlag != BLACK_CHESS || left[4] != chessFlag && right[1] != chessFlag))
				tiao2++;
			else if (right[1] == SPACE && (chessFlag != BLACK_CHESS || left[3] != chessFlag && right[2] != chessFlag))
				tiao2++;
		}
		if (right[0] == SPACE && right[1] == chessFlag && right[2] == SPACE && left[0] == SPACE)
		{
			if (right[3] == SPACE && (chessFlag != BLACK_CHESS || right[4] != chessFlag && left[1] != chessFlag))
				tiao2++;
			else if (left[1] == SPACE && (chessFlag != BLACK_CHESS || right[3] != chessFlag && left[2] != chessFlag))
				tiao2++;
		}
	}
}

void Game::GetLian2Tiao3Chong3TiaoChong4_New(int row, int col, int n, Count count, int chessFlag, int left[5], int right[5])
{
	if (left[0] == SPACE && right[0] == SPACE)
	{
		if (left[1] == SPACE && right[1] == SPACE && (chessFlag != BLACK_CHESS || (left[2] != BLACK_CHESS && right[2] != BLACK_CHESS)))
			lian2++;
		else if (left[1] == SPACE && left[2] == SPACE && (chessFlag != BLACK_CHESS || (left[3] != BLACK_CHESS && right[1] != BLACK_CHESS)))
			lian2++;
		else if (right[1] == SPACE && right[2] == SPACE && (chessFlag != BLACK_CHESS || (left[1] != BLACK_CHESS && right[3] != BLACK_CHESS)))
			lian2++;
		//THERE
		if (left[1] == SPACE && left[2] == chessFlag && (chessFlag != BLACK_CHESS || left[3] != chessFlag))
			chong3++;
		if (right[1] == SPACE && right[2] == chessFlag && (chessFlag != BLACK_CHESS || right[3] != chessFlag))
			chong3++;
		else if (left[1] == chessFlag && left[2] != chessFlag && left[2] != SPACE && (chessFlag != BLACK_CHESS || right[1] != chessFlag) ||
			right[1] == chessFlag && right[2] != chessFlag && right[2] != SPACE && (chessFlag != BLACK_CHESS || left[1] != chessFlag))
			chong3++;
		if (left[1] == chessFlag && left[2] == chessFlag && (chessFlag != BLACK_CHESS || left[3] != chessFlag))
			tiaochong4++;
		if (right[1] == chessFlag && right[2] == chessFlag && (chessFlag != BLACK_CHESS || right[3] != chessFlag))
			tiaochong4++;
		if (left[1] == chessFlag && left[2] == SPACE)
		{
			if (chessFlag != BLACK_CHESS)
				tiao3++;
			else if (left[3] != chessFlag && right[1] != chessFlag)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, -count.left - 1, n).x, DirectionCount_New(row, col, -count.left - 1, n).y))
					tiao3++;
				chess[row][col].flag = temp;
			}
		}
		if (right[1] == chessFlag && right[2] == SPACE)
		{
			if (chessFlag != BLACK_CHESS)
				tiao3++;
			else if (right[3] != chessFlag && left[1] != chessFlag)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, count.right + 1, n).x, DirectionCount_New(row, col, count.right + 1, n).y))
					tiao3++;
				chess[row][col].flag = temp;
			}
		}
	}
	else if (left[0] == SPACE)
	{
		if (left[1] != SPACE && left[1] != chessFlag && left[1] != 0 || left[2] != SPACE && left[2] != chessFlag && left[2] != 0);
		else if (chessFlag == BLACK_CHESS && left[3] == chessFlag);
		else if (left[1] == chessFlag && left[2] == chessFlag)
			tiaochong4++;
		else if (left[1] == chessFlag || left[2] == chessFlag)
			chong3++;
	}
	else if (right[0] == SPACE)
	{
		if (right[1] != SPACE && right[1] != chessFlag && right[1] != 0 || right[2] != SPACE && right[2] != chessFlag && right[2] != 0);
		else if (chessFlag == BLACK_CHESS && right[3] == chessFlag);
		else if (right[1] == chessFlag && right[2] == chessFlag)
			tiaochong4++;
		else if (right[1] == chessFlag || right[2] == chessFlag)
			chong3++;
	}
}

void Game::GetLian3Chong3TiaoChong4_New(int row, int col, int n, Count count, int chessFlag, int left[5], int right[5])
{
	if (left[0] == SPACE && right[0] == SPACE)
	{
		if (left[1] == SPACE)
		{
			if (chessFlag != BLACK_CHESS)
				lian3++;
			else if (left[2] = BLACK_CHESS && right[1] != BLACK_CHESS)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, -count.left - 1, n).x, DirectionCount_New(row, col, -count.left - 1, n).y))
					lian3++;
				chess[row][col].flag = temp;
			}
		}
		else if (right[1] == SPACE)
		{
			if (chessFlag != BLACK_CHESS)
				lian3++;
			else if (right[2] != BLACK_CHESS && left[1] != BLACK_CHESS)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, count.right + 1, n).x, DirectionCount_New(row, col, count.right + 1, n).y))
					lian3++;
				chess[row][col].flag = temp;
			}
		}
		else if (left[1] != chessFlag && left[1] != SPACE && right[1] != SPACE && right[1] != chessFlag)
			chong3++;
		if (right[1] == chessFlag)
		{
			if (chessFlag != BLACK_CHESS || right[2] != BLACK_CHESS)
				tiaochong4++;
		}
		if (left[1] == chessFlag)
		{
			if (chessFlag != BLACK_CHESS || left[2] != BLACK_CHESS)
				tiaochong4++;
		}
	}
	else if (right[0] == SPACE)
	{
		if (right[1] == SPACE)
		{
			if (chessFlag != BLACK_CHESS || right[2] != BLACK_CHESS)
				chong3++;
		}
		else if (right[1] == chessFlag)
			if (chessFlag != BLACK_CHESS || right[2] != BLACK_CHESS)
				tiaochong4++;
	}
	else if (left[0] == SPACE)
	{
		if (left[1] == SPACE)
		{
			if (chessFlag != BLACK_CHESS || left[2] != BLACK_CHESS)
				chong3++;
		}
		else if (left[1] == chessFlag)
			if (chessFlag != BLACK_CHESS || left[2] != BLACK_CHESS)
				tiaochong4++;
	}
}

void Game::GetHuo4Chong4_New(int row, int col, int n, Count count, int chessFlag, int left[5], int right[5])
{
	if ((left[0] == SPACE && right[0] == SPACE) && (chessFlag != BLACK_CHESS || left[1] != BLACK_CHESS && right[1] != BLACK_CHESS))
		huo4++;
	if ((left[0] != SPACE && right[0] == SPACE) && (chessFlag != BLACK_CHESS || right[1] != BLACK_CHESS))
		chong4++;
	if ((left[0] == SPACE && right[0] != SPACE) && (chessFlag != BLACK_CHESS || left[1] != BLACK_CHESS))
		chong4++;
}

void Game::Findcount(int row, int col, int chessFlag, Count count[4])
{
	bool leftFlag = false, rightFlag = false;
	//'-'
	for (int i = 1; i < 6; i++)
	{
		if (leftFlag && rightFlag)
			break;
		if (chess[row][col - i].flag != chessFlag)
			leftFlag = true;
		if (chess[row][col + i].flag != chessFlag)
			rightFlag = true;
		if (chess[row][col - i].flag == chessFlag && !leftFlag)
			count[0].left++;
		if (chess[row][col + i].flag == chessFlag && !rightFlag)
			count[0].right++;
	}

	leftFlag = false, rightFlag = false;
	//'|'
	for (int i = 1; i < 6; i++)
	{
		if (leftFlag && rightFlag)
			break;
		if (chess[row - i][col].flag != chessFlag)
			leftFlag = true;
		if (chess[row + i][col].flag != chessFlag)
			rightFlag = true;
		if (chess[row - i][col].flag == chessFlag && !leftFlag)
			count[1].left++;
		if (chess[row + i][col].flag == chessFlag && !rightFlag)
			count[1].right++;
	}

	leftFlag = false, rightFlag = false;
	//'\'
	for (int i = 1; i < 6; i++)
	{
		if (leftFlag && rightFlag)
			break;
		if (chess[row - i][col - i].flag != chessFlag)
			leftFlag = true;
		if (chess[row + i][col + i].flag != chessFlag)
			rightFlag = true;
		if (chess[row - i][col - i].flag == chessFlag && !leftFlag)
			count[2].left++;
		if (chess[row + i][col + i].flag == chessFlag && !rightFlag)
			count[2].right++;
	}

	leftFlag = false, rightFlag = false;
	//'/'
	for (int i = 1; i < 6; i++)
	{
		if (leftFlag && rightFlag)
			break;
		if (chess[row - i][col + i].flag != chessFlag)
			leftFlag = true;
		if (chess[row + i][col - i].flag != chessFlag)
			rightFlag = true;
		if (chess[row - i][col + i].flag == chessFlag && !leftFlag)
			count[3].left++;
		if (chess[row + i][col - i].flag == chessFlag && !rightFlag)
			count[3].right++;
	}
}

void Game::GetCheng5_New(int chessFlag, Count count)
{
	if (count.left + count.right >= 4)
		if (chessFlag != BLACK_CHESS || !Judge_IsChangLian_New(count))
			cheng5++;
}

bool Game::Judge_IsChangLian_New(Count count)
{
	if (count.left + count.right >= 5)
		return true;
	else
		return false;
}

int Game::Judge_IsDoubleThree_New(int row, int col, int n, Count count, int left[5], int right[5])
{
	if (count.left + count.right == 2)
		if (left[0] == SPACE && right[0] == SPACE)
		{
			if (left[1] == SPACE && left[2] != BLACK_CHESS && right[1] != BLACK_CHESS)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, -count.left - 1, n).x, DirectionCount_New(row, col, -count.left - 1, n).y))
				{
					chess[row][col].flag = temp;
					return 1;
				}
				chess[row][col].flag = temp;
			}
			if (right[1] == SPACE && right[2] != BLACK_CHESS && left[1] != BLACK_CHESS)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, count.right + 1, n).x, DirectionCount_New(row, col, count.right + 1, n).y))
				{
					chess[row][col].flag = temp;
					return 1;
				}
				chess[row][col].flag = temp;
			}
		}
	if (count.left + count.right == 1)
	{
		if (left[0] == SPACE && right[0] == SPACE)
		{
			if (left[1] == BLACK_CHESS && left[2] == SPACE && left[3] != BLACK_CHESS && right[1] != BLACK_CHESS)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, -count.left - 1, n).x, DirectionCount_New(row, col, -count.left - 1, n).y))
				{
					chess[row][col].flag = temp;
					return 1;
				}
				chess[row][col].flag = temp;
			}
			else if (right[1] == BLACK_CHESS && right[2] == SPACE && right[3] != BLACK_CHESS && left[1] != BLACK_CHESS)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, count.right + 1, n).x, DirectionCount_New(row, col, count.right + 1, n).y))
				{
					chess[row][col].flag = temp;
					return 1;
				}
				chess[row][col].flag = temp;
			}
		}
	}
	if (count.left + count.right == 0)
	{
		if (left[0] == SPACE && right[0] == SPACE)
		{
			if (left[1] == BLACK_CHESS && left[2] == BLACK_CHESS && left[3] == SPACE && left[4] != BLACK_CHESS && right[1] != BLACK_CHESS)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, -1, n).x, DirectionCount_New(row, col, -1, n).y))
				{
					chess[row][col].flag = temp;
					return 1;
				}
				chess[row][col].flag = temp;
			}
			else if (right[1] == BLACK_CHESS && right[2] == BLACK_CHESS && right[3] == SPACE && right[4] != BLACK_CHESS && left[1] != BLACK_CHESS)
			{
				int temp = chess[row][col].flag;
				chess[row][col].flag = BLACK_CHESS;
				if (!IsKinjite(DirectionCount_New(row, col, 1, n).x, DirectionCount_New(row, col, 1, n).y))
				{
					chess[row][col].flag = temp;
					return 1;
				}
				chess[row][col].flag = temp;
			}
		}
	}
	return 0;
}

int Game::Judge_IsDoubleFour_New(int row, int col, int n, Count count, int left[5], int right[5])
{
	int num = 0;
	if (count.left + count.right == 0)
	{
		if (left[0] == SPACE && left[1] == BLACK_CHESS && left[2] == BLACK_CHESS && left[3] == BLACK_CHESS && left[4] != BLACK_CHESS)
			num++;
		if (right[0] == SPACE && right[1] == BLACK_CHESS && right[2] == BLACK_CHESS && right[3] == BLACK_CHESS && right[4] != BLACK_CHESS)
			num++;
	}
	if (count.left + count.right == 1)
	{
		if (left[0] == SPACE && left[1] == BLACK_CHESS && left[2] == BLACK_CHESS && left[3] != BLACK_CHESS)
			num++;
		if (right[0] == SPACE && right[1] == BLACK_CHESS && right[2] == BLACK_CHESS && right[3] != BLACK_CHESS)
			num++;
	}
	if (count.left + count.right == 2)
	{
		if (left[0] == SPACE && left[1] == BLACK_CHESS && left[2] !=BLACK_CHESS)
			num++;
		if (right[0] == SPACE && right[1] == BLACK_CHESS && right[2] != BLACK_CHESS)
			num++;
	}
	if (count.left + count.right == 3)
		if (left[0] == SPACE && left[1] != BLACK_CHESS || right[0] == SPACE && right[1] != BLACK_CHESS)
			num++;
	return num;
}

bool Game::IsKinjite(int row, int col)
{
	Count count[4];//分别代表四个方向的紧邻点数量
	memset(count, 0, sizeof(count));
	Findcount(row, col, BLACK_CHESS, count);

	int three_Num = 0, four_Num = 0;
	int left[5], right[5];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			left[j] = chess[DirectionCount_New(row, col, -count[i].left - j - 1, i).x][DirectionCount_New(row, col, -count[i].left - j - 1, i).y].flag;
			right[j] = chess[DirectionCount_New(row, col, count[i].right + j + 1, i).x][DirectionCount_New(row, col, count[i].right + j + 1, i).y].flag;
		}
		if (count[i].left + count[i].right == 4)
			return false;
		three_Num += Judge_IsDoubleThree_New(row, col, i, count[i], left, right);
		four_Num += Judge_IsDoubleFour_New(row, col, i, count[i], left, right);
		if (Judge_IsChangLian_New(count[i]) || three_Num >= 2 || four_Num >= 2)
			return true;
	}
	return false;
}

bool Game::Judge_IsHuo4ShuangChong4(int row, int col, int chessFlag)
{
	Count count[4];//分别代表四个方向的紧邻点数量
	memset(count, 0, sizeof(count));
	Findcount(row, col, chessFlag, count);
	int  four_Num = 0;
	int left[5], right[5];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			left[j] = chess[DirectionCount_New(row, col, -count[i].left - j - 1, i).x][DirectionCount_New(row, col, -count[i].left - j - 1, i).y].flag;
			right[j] = chess[DirectionCount_New(row, col, count[i].right + j + 1, i).x][DirectionCount_New(row, col, count[i].right + j + 1, i).y].flag;
		}
		if (GetHuo4ShuangChong4(row, col, chessFlag, count[i], left, right))
			return true;
	}
	return false;
}

bool Game::GetHuo4ShuangChong4(int row, int col, int chessFlag,Count count, int left[5], int right[5])
{
	int num = 0;
	if (count.left + count.right == 3)
	{
		if (left[0] == SPACE&&right[0] == SPACE)
		{
			if (chessFlag != BLACK_CHESS)
				return true;
			else if (left[1] != BLACK_CHESS&&right[1] != BLACK_CHESS)
				return true;
		}
		else if (left[0] == SPACE&&left[1] == SPACE)
		{
			if (chessFlag != BLACK_CHESS || left[2] != BLACK_CHESS)
				num++;
		}
		else if (right[0] == SPACE&&right[1] == SPACE)
		{
			if (chessFlag != BLACK_CHESS || right[2] != BLACK_CHESS)
				num++;
		}
	}
	else if (count.left + count.right == 2)
	{
		if (right[0] == SPACE&&right[1] == chessFlag)
			if (chessFlag != BLACK_CHESS || right[2] != BLACK_CHESS)
				num++;
		if (left[0] == SPACE&&left[1] == chessFlag)
			if (chessFlag != BLACK_CHESS || left[2] != BLACK_CHESS)
				num++;
	}
	else if (count.left + count.right == 1)
	{
		if (right[0] == SPACE&&right[1] == chessFlag&&right[2] == chessFlag)
			if (chessFlag != BLACK_CHESS || right[3] != BLACK_CHESS)
				num++;
		if (left[0] == SPACE&&left[1] == chessFlag&&left[2] == chessFlag)
			if (chessFlag != BLACK_CHESS || left[3] != BLACK_CHESS)
				num++;
	}
	else if (count.left + count.right == 0)
	{
		if (right[0] == SPACE&&right[1] == chessFlag&&right[2] == chessFlag&&right[3] == chessFlag)
			if (chessFlag != BLACK_CHESS || right[4] != BLACK_CHESS)
				num++;
		if (left[0] == SPACE&&left[1] == chessFlag&&left[2] == chessFlag&&left[3] == chessFlag)
			if (chessFlag != BLACK_CHESS || left[4] != BLACK_CHESS)
				num++;
	}
	if (num >= 2)
		return true;
	else
		return false;
}

poinT Game::DirectionCount_New(int x, int y, int offset, int n)
{
	poinT point;
	switch (n)
	{
	case 0:point.x = x; point.y = y + offset; break;
	case 1:point.x = x + offset; point.y = y; break;
	case 2:point.x = x + offset; point.y = y + offset; break;
	case 3:point.x = x + offset; point.y = y - offset; break;
	}
	return point;
}