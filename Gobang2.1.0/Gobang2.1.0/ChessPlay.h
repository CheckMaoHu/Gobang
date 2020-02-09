#ifndef CHESSPLAY_H
#define CHESSPLAY_H

#include <QMainWindow>
#include <QMouseEvent>
#include "Game.h"
#include <QThread>
#include <iostream>
#include "GameThread.h"
//#define METHOD_PROLOGUE(theClass, localClass) \
//		theClass* pThis = ((theClass*)((char*)(this) - \
//		offsetof(theClass, m_x##localClass))); \
//
////内部类调用外部类的成员变量  
////大佬文章https://www.cnblogs.com/qzhforthelife/archive/2013/07/31/3226885.html
using namespace std;

//class myThread : public QThread
//{
//	Q_OBJECT
//public:
//	void run();
//signals:
//	void mySignal();
//}m_xmyThread;

namespace Ui {
class ChessPlay;
}

class ChessPlay : public QMainWindow
{
	Q_OBJECT

		/*friend class myThread;*/

public:
    explicit ChessPlay(QWidget *parent = 0);
    ~ChessPlay();
    virtual void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void judgeWhoFirst();
	void putinAdversaryName();
	void Nda(int x, int y);
	void peopleExchange();
	bool computerExchange();
	void judgeN();
    void peopleFirst();
    void computerFirst();
	void timeUpdate();
	void judgeWin();
	void judgeKinjite(int x, int y);
	void computerPlaychess();
	bool peoplePlaychess(int x, int y);
	void tiaoshizhuanyong(int x, int y);
	bool JudgeIsExist(int x, int y);

	QString adversaryName;
	QTimer* wtimerId;
	QTimer* btimerId;
	GameThread* gameThread;
	/*myThread* gameThread;*/
private slots:
	void btimerUpdate();

    void wtimerUpdate();

    void on_actionBack_triggered();

    void on_actionQuit_2_triggered();

    void on_actionHome_triggered();

    void on_actionScreenshot_triggered();

    void on_actionGame_triggered();

	void computerPlaychessGoon();

	/*void AISlot();*/
private:
	Ui::ChessPlay *ui;
	Game game;
    int moveX;
    int moveY;
    bool mouseflag;
	int whiteTimes;
	int blackTimes;
	//myThread AIthread;
};

#endif // CHESSPLAY_H
