#pragma once

#include "Table.h"

class Game
{
protected:
	Table *table;
public:
	Game();
	~Game();
	void Init();
	void Blind();
};

