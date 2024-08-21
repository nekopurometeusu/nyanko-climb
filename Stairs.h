#pragma once
#include "DxLib.h"
#include "Player.h"
#include <vector>

class Stairs
{
public:
	Stairs();							// �R���X�g���N�^.
	~Stairs();							// �f�X�g���N�^.

	void Load();
	void DrawTitle();
	void DrawStairs();
	// �v���C���[�̗����`�F�b�N
	bool CheckForFall(const Player& player, int& Displayfloor);

private:
	int isStairsRandPattern;
	const int isNumberofStages = 999;
	VECTOR vertex[1000][2]; // �K�i�̍��W
	VECTOR titleVertexLeft;
	VECTOR titleVertexRight;
	int StairsGraph;
};
