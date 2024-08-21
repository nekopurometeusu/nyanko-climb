#include<vector>
#include "Map.h"
#include "DxLib.h"
#include "WorldSprite.h"


/// <summary>
/// コンストラクタ
/// </summary>
Map::Map()
{
	//ドームのハンドル
	domeHandle = MV1LoadModel("data/Dome_X501.mv1");
	// 処理なし
	domeZ = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	//処理なし
}

/// <summary>
/// ロード
/// </summary>
void Map::Load()
{
	
	// ３Dモデルのポジション設定
	MV1SetPosition(domeHandle, VGet(0,0,domeZ));
	rotationDomeY = 0;
}

/// <summary>
/// 更新
/// </summary>
void Map::Update()
{
	// ドームの回転
	rotationDomeY+= 0.0001f;
}

/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	MV1SetPosition(domeHandle, VGet(0, 0, 0));
	MV1SetRotationXYZ(domeHandle, VGet(0, rotationDomeY, 0));
	MV1DrawModel(domeHandle);
}


