#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include "Game.h"
#include <memory>
#include <QThread>

class GameThread :public QThread
{
	Q_OBJECT

public:
	GameThread(Game &game)
	{
		T_game = &game;
	}


public:
	Game * T_game;

private:
	bool stooped;

protected:
	void run();

signals:
	void goon();
};

#endif // GAMETHREAD_H