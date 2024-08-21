#pragma once
#include "DxLib.h"
#include "Player.h"
#include <vector>

class Stairs
{
public:
	Stairs();							// コンストラクタ.
	~Stairs();							// デストラクタ.

	void Load();
	void DrawTitle();
	void DrawStairs();
	// プレイヤーの落下チェック
	bool CheckForFall(const Player& player, int& Displayfloor);

private:
	int isStairsRandPattern;
	const int isNumberofStages = 999;
	VECTOR vertex[1000][2]; // 階段の座標
	VECTOR titleVertexLeft;
	VECTOR titleVertexRight;
	int StairsGraph;
};
