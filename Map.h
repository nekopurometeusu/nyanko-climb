#pragma once
#include <vector>

class WorldSprite;

/// <summary>
/// 2D�̔w�i�}�b�v
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Load();
	void Update();
	void Draw();
private:
	int domeHandle;
	int domeZ;
	float rotationDomeY;
};

