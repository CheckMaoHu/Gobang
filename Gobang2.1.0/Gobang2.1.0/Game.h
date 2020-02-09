#ifndef GAME_H
#define GAME_H
#include <QVector>
#include <utility>
using namespace std;

#define WHITE_CHESS 5
#define BLACK_CHESS 4
#define SPACE 3
#define SIZE 15
#define VCDEPTH 4  // AI 进行 VC 攻击的开始深度
#define VCDEPTH_END 8  // AI 进行VC攻击的最高深度
#define VCDEPTH_DIS 2  // AI 进行 VC 攻击的深度 递增值

#define VCDE_DEPTH 4  // AI 进行 VC 防御的开始深度
#define VCDE_DEPTH_END 8 // AI 进行 VC 防御的最高深度
#define VCDE_DEPTH_DIS 2 // AI 进行 VC 防御的深度 递增值

typedef struct
{
	int x, y, l, r;
}value;

typedef struct
{
	int flag;  //颜色
	int seq;//次序
}Chess;

typedef struct 
{
	int type[4];
	int dotN;
	int n;
	int w[2];    //白四最强防守
	int p[40][2];
}ChessType;

typedef struct
{
	int x;
	int y;
	int score;
}poinT;

typedef struct Message
{
	int type;
	int depth;
	int cnt;
	int score;
}Message;

typedef struct
{
	int left;
	int right;
}Count;

//置换表
typedef struct tagHASHE {
	_int64 key;
	int depth;
	int flags;//棋子颜色
	int value;
} HASHE;
struct VCPoint  // VC攻击时的攻击点,由活4,冲4,跳冲4,连3,跳3,组成,优先级依次递减
{
	int row;
	int col;
	int pri;  // 优先级
	friend bool operator < (const VCPoint &a, const VCPoint &b)
	{
		return a.pri > b.pri;
	}
	void init(int _r, int _c, int _p)
	{
		row = _r, col = _c, pri = _p;
	}
};
class Game
{
public:
	Game();
	Chess chess[15][15];
	Chess chess_B[15][15];   //备份

	ChessType chessType[26];

	Message message;

	int *times;
	int timeo;
	int player;
	int dadianN;
	int dadiann;
	bool dafou;      //判断是否选择了打点
	bool judge(int x, int y);
	bool ifWin(int x, int y);
	void backChess();
	int sta();
	int aspect;    //开局方向
	int kaijun;    //开局库次序
	int cComputer;  //电脑执棋颜色
	int cPeople;
	void initiChessType();
	HASHE*Hashtable[6];
	unsigned int m_nHashKey32[6][15][15];          //32位随机树组，用以生成32位哈希值
	unsigned __int64 m_ulHashKey64[6][15][15];//64位随机树组，用以生成64位哈希值
	unsigned int m_HashKey32;          //32位哈希值
	_int64 m_HashKey64;
	QPoint peoplePutdown(int x, int y);
	QPoint computerPutdown(int x, int y);
	QVector<QPoint> chessPoint;
	bool AIkongzhi;
	bool waitThread;

private:


	//ai系统   第一次全面升级
public:
	void AI();
	int isDefend; //判断是否防守 VC攻击时使用
				  /* 攻击状态
				  0 : 正常行棋
				  1 ：表示VCF攻击
				  2 ：表示阻止VCF攻击
				  3 ：表示VCF和VCT联合攻击
				  */
	int AIState;  // 在 VC攻击时得值
	int comX, comY;
	int depthMM; // 深度控制

	void LayOut();//开局
	void ComputerPlay();
	void PeoplePlay();
	int currentX, currentY;
	bool change();
	void Nda();    //给N个打点
	void daN();    //从N个打点中 选择一个
	int kaiju(int i1, int j1, int i2, int j2, int n);
	void judge_Aspect(int i1, int j1, int i2, int j2);
	bool judge_Neighbored(int x, int y);
	poinT aspect_count(int i, int j);
	int heuristic(int left1, int right1, int top1, int bottom1, int flag, poinT result[11]);  //启发式搜索

	//黑方在落下的关键的第五子即形成五连的同时,又形成禁手,此时禁手失效,黑棋胜
	//返回1说明这点是黑棋的长连禁手,返回2说明是三三或四四禁手,否则不是禁手
	/*int IsKinjite(int row, int col);*/
	void UpdateLimit();//更新棋面限制框
	void Chang_UpddateLimit(int &left_temp, int& right_temp, int &top_temp, int &bottom_temp, int X, int Y);
	bool judge_IsKinjite(int row, int col);

	//新棋型判断
	void Search(int row, int col, int chessFlag);
	void Findcount(int row, int col, int chessFlag, Count count[4]);
	void GetCheng5_New(int chessFlag, Count count);
	void GetHuo4Chong4_New(int row, int col, int n, Count count, int chessFlag, int left[5], int right[5]);
	void GetLian3Chong3TiaoChong4_New(int row, int col, int n, Count count, int chessFlag, int left[5], int right[5]);
	void GetLian2Tiao3Chong3TiaoChong4_New(int row, int col, int n, Count count, int chessFlag, int left[5], int right[5]);
	void GetTiao2Tiao3Tiaochong4_New(int row, int col, int n, Count count, int chessFlag, int left[5], int right[5]);
	poinT DirectionCount_New(int x, int y, int offset, int n);


	bool Judge_IsChangLian_New(Count count);
	int Judge_IsDoubleThree_New(int row, int col, int n, Count count, int left[5], int right[5]);
	int Judge_IsDoubleFour_New(int row, int col, int n, Count count, int left[5], int right[5]);
	bool IsKinjite(int row, int col);
	bool Judge_IsHuo4ShuangChong4(int row, int col, int chessFlag);
	bool GetHuo4ShuangChong4(int row, int col, int chessFlag, Count count, int left[5], int right[5]);

	//哈希表
	void _CTranspositionTable();
	void CTranspositionTable();
	void CalculateInitHashKey();



	QPoint ceshizhuanyong(int x, int y);
	void BackstageAI();
	bool huiqijudge;
	bool depthkongzhi;

private:
	pair<int, int> GetCurrentMaxPoint(int chessFlag);//得到并返回当前价值最大点 chessFlag 代表不同角度
	int mustWin;   //记录是否有必赢点
	int winPeople, winComputer;  //同样是记录必赢点,记录是谁的必赢点
	int peoX, peoY;
	int computer[SIZE][SIZE], people[SIZE][SIZE];//记录未下过的点对于计算机和人的价值
	bool VCAttack(); // 判断是否可以进行VC攻击
	void ControlDepth(); //判断局势设置深度


	void InitGameTree(int row, int col, bool& flag, int depth, int& depthC, int& depthP, bool& stop, int depthRecord);
	// GameTree的参数中,flag分别表示计算机是否找到必赢点,
	// 若有必赢点,则depthC,depthP表示(计算机,人)必赢点的最小深度
	// 这个函数只是初步筛选
	// InitGameTree（） 和 AgainGameTree（) 的函数体差不多,一个用于计算机的,一个用于人的。
	int Evaluate(int left1, int right1, int top1, int bottom1);
	void MaxMin(int depth);//极大极小搜索树
	int Max(int left1, int right1, int top1, int bottom1, int row, int col, int depth, int alpha, int beta);//极大层
	int Min(int left1, int right1, int top1, int bottom1, int row, int col, int depth, int alpha, int beta);//极小层
	int Evaluate_Value(int chessFlag,int left1, int right1, int top1, int bottom1);//判断局势值
	void InitializeHashKey();
	void EnterHashTable(int flag, int eval, int  depth, int chessFlag);
	int LookUpHashTable(int alpha, int beta, int depth, int flag);
	void Hash_MakeMove(int row, int col, int chessFlag);
	void Hash_UnMakeMove(int row, int col, int chessFlag);
	
	//haxi
	__int64 rand64();
	long rand32();
	int left, right, top, bottom;
	//	根据五子棋的特点,可以产生一个棋面限制框,记录当前棋面所有棋子的最左、
	//	最右、最上、最下点构成的矩形,而且基本可以认为下一步棋的位置不会脱离这个框3步以上.

	bool PeopleAttack(int r, int c, int depthCFromIGT); //模拟人攻击

														//得到 chessMap[row][col] 这点对于 chessFlag 色的棋的价值
	int GetScoreForComputer(int row, int col, char chessFlag);
	int GetScoreForPeople(int row, int col, char chessFlag);

	int IsCombForAllVC(int row, int col, int oneself, int oppsite); // 是否构成可以VC攻击
	int IsCombForOneselfVc(int row, int col, int oneself);
	void VCAttackTree(int type, int row, int col, char cOneself, char cOpposite, int depth, bool& flag, int& ansDepth, int depthRecord, int left1, int right1, int top1, int bottom1); // VC 攻击树
	/*bool Max_Vc(int left1, int right1, int top1, int bottom1, int row, int col, int depth, int oneself, int oppsite, int max, int last);
	bool Min_Vc(int left1, int right1, int top1, int bottom1, int row, int col, int depth, int oneself, int oppsite, int max, int last);*/
	int FindVcPoint(int left1, int right1, int top1, int bottom1, int oneself, int oppsite, VCPoint p[]);
	int FindVcOneselfPoint(int left1, int right1, int top1, int bottom1, int oneself, VCPoint p[]);
	int FindVc(VCPoint p[], VCPoint opp[], int num, int numopp, int last, VCPoint all[], int oneself, int oppsite);
	bool MaxMin_Vc(int depth);
	bool Iteration();

	int Game::IsCombForVC(int row, int col, char chessFlag);
	bool Game::Max_Vc(int left1, int right1, int top1, int bottom1, int row, int col, int depth, int oneself, int oppsite, int max);
	bool Game::Min_Vc(int left1, int right1, int top1, int bottom1, int row, int col, int depth, int oneself, int oppsite, int max);
	int DEPTH; // 由 AI 动态控制 InitGameTree 的搜索深度
	//void Search(int row, int col, char chessFlag);//搜索 chessMap[row][col] 这点能够针对 chessFlag 色的棋能够构成哪些棋型
	void AgainGameTree(int row, int col, int depth, int& depthC, int& depthP, bool& stop, int& depthRecord);
	int GetScore(int row, int col, char chessFlag, char flag);
	int AddScore(int row, int col, char chessFlag);

	//判断棋形
	pair<int, pair<int, int> > GetChong3Chong4(int row, int col, char chessFlag);// 假设在chessMap[row][col] 落子后,返回构成冲3和冲4(chong4和tiaochong4)的数量 
	pair<int, int> GetLian2Lian3(int row, int col, char chessFlag);// 假设在chessMap[row][col] 落子后,返回构成连2和连3的数量 
	pair<int, int> GetTiao2Tiao3(int row, int col, char chessFlag);// 假设在chessMap[row][col] 落子后,返回构成跳2和跳3的数量 
	int GetCheng5ChangLian(int row, int col, char chessFlag);// 假设在chessMap[row][col] 落子后,是否成5（或长连),返回1表示五连,返回2表示长连,否则返回0 
	int GetHuo4(int row, int col, char chessFlag);//假设在chessMap[row][col] 落子后,返回构成活4的数量 

	int changlian, cheng5, huo4, chong4, tiaochong4, lian3, tiao3, chong3, lian2, tiao2;
	int chong2 = 0, huo1 = 0, chong1 = 0;

};



#endif // GAME_H









