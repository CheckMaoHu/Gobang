#include "GameThread.h"

void GameThread::run()
{
	bool backAI = false;
	T_game->waitThread = true;
	if (T_game->player == 3)
	{
		poinT point1 = T_game->aspect_count(T_game->chessType[T_game->kaijun].w[0], T_game->chessType[T_game->kaijun].w[1]);
		T_game->comX = point1.x;
		T_game->comY = point1.y;
		QPoint point = T_game->computerPutdown(T_game->comX, T_game->comY);
		T_game->currentX = point.x();
		T_game->currentY = point.y();
	}
	else if (T_game->player == 4)
		for (int i = 0; i < T_game->dadiann; i++)
		{
			T_game->dadianN--;
			T_game->Nda();
			QPoint point = T_game->computerPutdown(T_game->comX, T_game->comY);
			T_game->chess[T_game->comX][T_game->comY].seq = 255;
		}
	else
	{
		backAI = true; 
		if (T_game->player <= 7)
		{
			T_game->Hashtable[4] = new HASHE[1024 * 1024]();
			T_game->Hashtable[5] = new HASHE[1024 * 1024]();
		}
		T_game->CalculateInitHashKey();
		T_game->AI();
		T_game->_CTranspositionTable();
		T_game->Hashtable[4] = new HASHE[1024 * 1024]();
		T_game->Hashtable[5] = new HASHE[1024 * 1024]();
		QPoint point = T_game->computerPutdown(T_game->comX, T_game->comY);
		T_game->currentX = point.x();
		T_game->currentY = point.y();
	}
	/*memcpy(T_game->chess_B, T_game->chess, sizeof(T_game->chess_B));*/
	emit goon();/*
	if (backAI)
		T_game->BackstageAI();*/
	T_game->waitThread = false;
}

//void GameThread::AI()
//{
//	T_game->isDefend = false;
//	T_game->AIState = 0;
//
//	T_game->ComputerPlay();
//	int tempX = T_game->comX, tempY = T_game->comY; //
//
//	if (1 == T_game->mustWin)  //有成五点
//		return;
//
//	if (T_game->VCAttack()) // 可以进行 VC 攻击
//		return;
//
//	T_game->ControlDepth(); // 设置递归深度
//
//	int row, col, depthRecord = 999, maxScore = -999;
//
//	// 若找到一个必赢点，便将其置为 true，否则需要检查人是否存在赢的情况，例如：
//	// 这种情况：计算机落子后构成一个冲4和一个活3，然后人在挡冲4的时候形成了活4，这样人就先赢了
//	// 所以不能单纯依赖于最大值去判断
//	bool safeFlag = false;
//
//	for (row = T_game->top; row <= T_game->bottom; ++row)
//	{
//		for (col = T_game->left; col <= T_game->right; ++col)
//		{
//			if (T_game->chess[row][col].flag != SPACE)
//				continue;
//			if (BLACK_CHESS == T_game->cComputer && T_game->IsKinjite(row, col))  //计算机执黑，且这点为禁手点
//				continue;
//
//			bool flag = false, stop = false;
//			int depthC = 999, depthP = 999;
//
//			T_game->InitGameTree(row, col, flag, 0, depthC, depthP, stop, depthRecord);
//
//			//由于是单叉树，那么depthC和depthP至少有一个是不变的，
//			//depthP<=depthC则说明若按这条路径下计算机不能先赢
//			if (depthP <= depthC)
//				continue;
//
//			// 上面是在计算机的进攻蓝图中，下面这个函数模拟人进攻，看谁先赢，人先赢，则返回true
//			// 注意参数导入
//			if (T_game->PeopleAttack(row, col, depthC)) //// 有了一步，防御能力大大提高
//				continue;
//
//			if (flag)  //计算机有必赢点，便将这点保存起来
//			{
//				// 需要考虑禁手情况,主要原因是因为三三禁手
//				bool ff = false;
//				if (BLACK_CHESS == T_game->cComputer && depthC >= 2)
//				{
//					T_game->chess[row][col].flag = T_game->cComputer;  //假设下了这点
//					for (int i = T_game->top; i <= T_game->bottom; ++i)
//					{
//						for (int j = T_game->left; j <= T_game->right; ++j)
//						{
//							if (T_game->IsKinjite(i, j)) // 产生了禁手点
//							{
//								ff = true;
//								i = T_game->bottom + 1;
//								j = T_game->right + 1;
//							}
//						}
//					}
//					T_game->chess[row][col].flag = SPACE; //恢复
//				}
//				if (ff)
//					continue;
//
//				if (depthC < depthRecord)  //选取深度小的
//				{
//					maxScore = T_game->GetScoreForComputer(row, col, T_game->cComputer);
//					depthRecord = depthC;
//					tempX = row;
//					tempY = col;
//				}
//				else if (depthC == depthRecord) //深度一样时选取权值大的
//				{
//					int res = T_game->GetScoreForComputer(row, col, T_game->cComputer);
//					if (res > maxScore)
//					{
//						maxScore = res;
//						tempX = row;
//						tempY = col;
//					}
//				}
//				safeFlag = true; ///
//			}
//		}
//	}
//}
//
//
//bool GameThread::VCAttack()
//{
//	// 判断是否有可以进行 VC 攻击的点
//	// 先判断计算机能否 VCF攻击取胜，再判断人是否通过VCF攻击取胜，然后再判断计算机是否通过VCF和VCT联合
//	//攻击取胜，也判断人的VCF和VCT联合攻击(虽然慢一点).
//	// 为了提高 棋力， 不断的尝试各个深度，先从小的深度开始搜素，这样就能保证以最小的步数赢棋，
//	// 一旦找到必赢点，立即返回
//	// 目前仍然有bug，很难在速度和棋力之间权衡
//
//	// VC 攻击，活4，冲4(冲4和跳冲4)，活3（连3和跳3），优先级依次降低
//
//	int row, col;
//	VCPoint vcPoint[100]; //
//	int cnt;
//	int tempDepth; //深度控制
//
//	VCPoint dePoint[100]; //用于 VC 防守，在下面的模拟人的攻击中保存攻击点
//	int num = 0; //
//
//	int tempX, tempY, depthRecord = 9999, maxScore = -9999;
//	bool ff = false;
//	int left1 = T_game->left, right1 = T_game->right, bottom1 = T_game->bottom, top1 = T_game->top;
//	// 先判断计算机是否可进行 VCF 攻击,  可以则返回
//
//	cnt = 0;
//
//	for (row = T_game->top; row <= T_game->bottom; ++row)
//	{
//		for (col = T_game->left; col <= T_game->right; ++col)
//		{
//			if (T_game->chess[row][col].flag != SPACE)
//				continue;
//			if (BLACK_CHESS == T_game->cComputer && T_game->IsKinjite(row, col)) // 计算机的禁手点
//				continue;
//
//			int res = T_game->IsCombForVC(row, col, T_game->cComputer);
//
//			if (res<3) // VCF攻击
//				continue;
//
//			vcPoint[cnt++].init(row, col, res);	//是进攻点则先保存
//
//			if (cnt >= 100)
//			{
//				row = T_game->bottom + 1;
//				col = T_game->right + 1;
//			}
//		}
//	}
//
//	sort(vcPoint, vcPoint + cnt); //
//
//	for (tempDepth = VCDEPTH; tempDepth <= VCDEPTH_END; tempDepth += VCDEPTH_DIS)//深度不断递增
//	{
//		T_game->depthMM = tempDepth; //
//		for (int i = 0; i<cnt; ++i)
//		{
//			bool flag = false;
//			int ansDepth = 9999;
//			T_game->VCAttackTree(1, vcPoint[i].row, vcPoint[i].col, T_game->cComputer, T_game->cPeople, 0, flag, ansDepth, depthRecord, left1, right1, top1, bottom1);
//
//			if (flag) // 找到一个必赢攻击点
//			{
//				ff = true; //
//				if (ansDepth<depthRecord) //选取最快能赢的
//				{
//					depthRecord = ansDepth;
//					tempX = vcPoint[i].row;
//					tempY = vcPoint[i].col;
//					maxScore = T_game->GetScoreForComputer(tempX, tempY, T_game->cComputer);
//					maxScore += T_game->GetScoreForComputer(tempX, tempY, T_game->cPeople);
//				}
//				else if (ansDepth == depthRecord) //深度一样时选取权值大的
//				{
//					int res = T_game->GetScoreForComputer(vcPoint[i].row, vcPoint[i].col, T_game->cComputer);
//					res += T_game->GetScoreForComputer(vcPoint[i].row, vcPoint[i].col, T_game->cPeople);
//					if (res > maxScore)
//					{
//						maxScore = res;
//						tempX = vcPoint[i].row;
//						tempY = vcPoint[i].col;
//					}
//				}
//			}
//		}
//		if (ff)
//		{
//			T_game->comX = tempX;
//			T_game->comY = tempY;
//			T_game->AIState = 1; //
//			return true;
//		}
//
//	}
//
//	// 再判断人是否通过 VCF攻击取胜，若可以，则计算机不进行 VCF和VCT的联合攻击，因为会先输
//	// 但还要继续判断 人是否还可以 通过 VCF和VCT的联合攻击取胜，这关系到计算机的落子
//	int peoIsVCF = false;
//	//////////////////////////////////////////////////////////////////////////
//	cnt = 0;
//
//	for (row = T_game->top; row <= T_game->bottom; ++row)
//	{
//		for (col = T_game->left; col <= T_game->right; ++col)
//		{
//			if (T_game->chess[row][col].flag != SPACE)
//				continue;
//			if (BLACK_CHESS == T_game->cPeople && T_game->IsKinjite(row, col)) // 人的禁手点
//				continue;
//
//			int res = T_game->IsCombForVC(row, col, T_game->cPeople);
//
//			if (res<3) // VCF攻击
//				continue;
//
//			vcPoint[cnt++].init(row, col, res);	//是进攻点则先保存
//
//			if (cnt >= 100)
//			{
//				row = T_game->bottom + 1;
//				col = T_game->right + 1;
//			}
//		}
//	}
//
//	sort(vcPoint, vcPoint + cnt); //
//
//
//	for (tempDepth = VCDE_DEPTH; tempDepth <= VCDE_DEPTH_END; tempDepth += VCDE_DEPTH_DIS)//深度不断递增
//	{
//		T_game->depthMM = tempDepth; //
//		for (int i = 0; i<cnt; ++i)
//		{
//			bool flag = false;
//			int ansDepth = 9999;
//
//			T_game->VCAttackTree(1, vcPoint[i].row, vcPoint[i].col, T_game->cPeople, T_game->cComputer, 0, flag, ansDepth, depthRecord, left1, right1, top1, bottom1);
//
//			if (flag) // 找到一个必赢攻击点
//			{
//				ff = true; //
//				i = cnt;
//				tempDepth = VCDE_DEPTH_END + 1;
//			}
//		}
//	}
//	if (ff)
//	{
//		peoIsVCF = true;
//		T_game->AIState = 2;
//	}
//
//	ff = false;
//
//	//判断计算机能否通过 VCF和VCT联合攻击取胜,  前提是人不能进行 VCF攻击
//	//////////////////////////////////////////////////////////////////////////
//	if (!peoIsVCF)
//	{
//		cnt = 0;
//
//		for (row = T_game->top; row <= T_game->bottom; ++row)
//		{
//			for (col = T_game->left; col <= T_game->right; ++col)
//			{
//				if (T_game->chess[row][col].flag != SPACE)
//					continue;
//				if (BLACK_CHESS == T_game->cComputer && T_game->IsKinjite(row, col)) // 计算机的禁手点
//					continue;
//
//				int res = T_game->IsCombForVC(row, col, T_game->cComputer);
//
//				if (!res) // VCF和VCT联合攻击
//					continue;
//
//				vcPoint[cnt++].init(row, col, res);	//是进攻点则先保存
//
//				if (cnt >= 100)
//				{
//					row = T_game->bottom + 1;
//					col = T_game->right + 1;
//				}
//			}
//		}
//		sort(vcPoint, vcPoint + cnt); //
//
//		for (tempDepth = VCDEPTH; tempDepth <= VCDEPTH_END; tempDepth += VCDEPTH_DIS)//深度不断递增
//		{
//			T_game->depthMM = tempDepth; //
//			for (int i = 0; i<cnt; ++i)
//			{
//				bool flag = false;
//				int ansDepth = 9999;
//				T_game->VCAttackTree(2, vcPoint[i].row, vcPoint[i].col, T_game->cComputer, T_game->cPeople, 0, flag, ansDepth, depthRecord, left1, right1, top1, bottom1);
//
//				if (flag) //找到一个必赢攻击点
//				{
//					ff = true; //
//					if (ansDepth<depthRecord) //选取最快能赢的
//					{
//						depthRecord = ansDepth;
//						tempX = vcPoint[i].row;
//						tempY = vcPoint[i].col;
//						maxScore = T_game->GetScoreForComputer(tempX, tempY, T_game->cComputer);
//						maxScore += T_game->GetScoreForComputer(tempX, tempY, T_game->cPeople);
//					}
//					else if (ansDepth == depthRecord) //深度一样时选取权值大的
//					{
//						int res = T_game->GetScoreForComputer(vcPoint[i].row, vcPoint[i].col, T_game->cComputer);
//						res += T_game->GetScoreForComputer(vcPoint[i].row, vcPoint[i].col, T_game->cPeople);
//						if (res > maxScore)
//						{
//							maxScore = res;
//							tempX = vcPoint[i].row;
//							tempY = vcPoint[i].col;
//						}
//					}
//
//				}
//			}
//			if (ff)
//			{
//				T_game->comX = tempX;
//				T_game->comY = tempY;
//				T_game->AIState = 3;
//				return true;
//			}
//		}
//	}
//
//	//判断人能否通过 VCF和VCT联合攻击取胜，  VC 防御
//	//////////////////////////////////////////////////////////////////////////
//	cnt = 0;
//	depthRecord = 9999;
//
//	for (row = T_game->top; row <= T_game->bottom; ++row)
//	{
//		for (col = T_game->left; col <= right; ++col)
//		{
//			if (chess[row][col].flag != SPACE)
//				continue;
//			if (BLACK_CHESS == cPeople && IsKinjite(row, col)) // 自己的禁手点
//				continue;
//
//			int res = IsCombForVC(row, col, cPeople);
//
//			if (!res) // VCF和VCT联合攻击
//				continue;
//
//			vcPoint[cnt++].init(row, col, res);	//是进攻点则先保存
//
//			if (cnt >= 100)
//			{
//				row = bottom + 1;
//				col = right + 1;
//			}
//		}
//	}
//
//	sort(vcPoint, vcPoint + cnt); //
//
//	for (tempDepth = VCDE_DEPTH; tempDepth <= VCDE_DEPTH_END; tempDepth += VCDE_DEPTH_DIS)//深度不断递增
//	{
//		depthMM = tempDepth; //
//		for (int i = 0; i<cnt; ++i)
//		{
//			bool flag = false;
//			int ansDepth = 9999;
//			isDefend = false;
//
//			VCAttackTree(2, vcPoint[i].row, vcPoint[i].col, cPeople, cComputer, 0, flag, ansDepth, depthRecord, left1, right1, top1, bottom1);
//
//			if (flag) // 找到一个必赢攻击点
//			{
//				isDefend = true; //防守，主要是为了 防在对方进攻的方向
//				ff = true; //		
//				if (ansDepth<depthRecord) //选取最快能赢的
//				{
//					depthRecord = ansDepth;
//					tempX = vcPoint[i].row;
//					tempY = vcPoint[i].col;
//					maxScore = GetScoreForComputer(tempX, tempY, cPeople);
//					maxScore += GetScoreForComputer(tempX, tempY, cComputer);
//				}
//				else if (ansDepth == depthRecord) //深度一样时选取权值大的
//				{
//					int res = GetScoreForComputer(vcPoint[i].row, vcPoint[i].col, cPeople);
//					res += GetScoreForComputer(vcPoint[i].row, vcPoint[i].col, cComputer);
//					if (res > maxScore)
//					{
//						maxScore = res;
//						tempX = vcPoint[i].row;
//						tempY = vcPoint[i].col;
//					}
//				}
//			}
//		}
//		if (ff)
//		{
//			// 防守，计算机选择攻击位置落子，落子条件为下了该点后使人不会产生 VC 攻击点
//			//////////////////////////////////////////////////////////////////////////
//			for (row = top; row <= bottom; ++row)
//			{
//				for (col = left; col <= right; ++col)
//				{
//					if (chess[row][col].flag != SPACE)
//						continue;
//					if (BLACK_CHESS == cComputer && IsKinjite(row, col))
//						continue;
//
//					int res1 = IsCombForVC(row, col, cComputer);
//					int res2 = IsCombForVC(row, col, cPeople);
//
//					if (!res1 && !res2)
//						continue;
//					else if ((3 == res1 || 4 == res1) && !res2) //一般情况下不要下自己冲4和跳冲4
//						continue;
//
//					int res = GetScoreForComputer(row, col, cComputer);
//					res += GetScoreForComputer(row, col, cPeople);
//
//					dePoint[num++].init(row, col, res);
//				}
//			}
//
//			sort(dePoint, dePoint + num); //以权值排序
//
//			for (int p = 0; p<num; ++p)
//			{
//				bool noVC = true;
//
//				chess[dePoint[p].row][dePoint[p].col].flag = cComputer; //假设计算机在这落子
//
//																		// 下面依旧是模拟 人的 VC 攻击
//				cnt = 0;
//				depthRecord = 9999;
//
//				for (row = top; row <= bottom; ++row)
//				{
//					for (col = left; col <= right; ++col)
//					{
//						if (chess[row][col].flag != SPACE)
//							continue;
//						if (BLACK_CHESS == cPeople && IsKinjite(row, col)) // 人的禁手点
//							continue;
//
//						int res = IsCombForVC(row, col, cPeople);
//
//						if (!res) // VCF和VCT联合攻击
//							continue;
//
//						vcPoint[cnt++].init(row, col, res);	//是进攻点则先保存
//
//						if (cnt >= 100)
//						{
//							row = bottom + 1;
//							col = right + 1;
//						}
//					}
//				}
//
//				sort(vcPoint, vcPoint + cnt); //
//
//
//				for (tempDepth = VCDE_DEPTH; tempDepth <= VCDE_DEPTH_END; tempDepth += VCDE_DEPTH_DIS)//深度不断递增
//				{
//					depthMM = tempDepth; //
//					for (int i = 0; i<cnt; ++i)
//					{
//						bool flag = false;
//						int ansDepth = 9999;
//						VCAttackTree(2, vcPoint[i].row, vcPoint[i].col, cPeople, cComputer, 0, flag, ansDepth, depthRecord, left1, right1, top1, bottom1);
//
//						if (flag) // 找到便立即跳出
//						{
//							noVC = false;
//							i = cnt;
//							tempDepth = VCDE_DEPTH_END + 1;
//						}
//					}
//				}
//
//				chess[dePoint[p].row][dePoint[p].col].flag = SPACE; //恢复
//
//				if (noVC) //如果人没有 VC 攻击点
//				{
//					tempX = dePoint[p].row;
//					tempY = dePoint[p].col;
//					break;
//				}
//			}
//
//			//////////////////////////////////////////////////////////////////////////
//			comX = tempX;
//			comY = tempY;
//			AIState = 4;
//			return true;
//		}
//	}
//	return false;
//}