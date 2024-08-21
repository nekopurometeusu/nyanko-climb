#include<vector>
#include "Map.h"
#include "DxLib.h"
#include "WorldSprite.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map()
{
	//�h�[���̃n���h��
	domeHandle = MV1LoadModel("data/Dome_X501.mv1");
	// �����Ȃ�
	domeZ = 0;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{
	//�����Ȃ�
}

/// <summary>
/// ���[�h
/// </summary>
void Map::Load()
{
	
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(domeHandle, VGet(0,0,domeZ));
	rotationDomeY = 0;
}

/// <summary>
/// �X�V
/// </summary>
void Map::Update()
{
	// �h�[���̉�]
	rotationDomeY+= 0.0001f;
}

/// <summary>
/// �`��
/// </summary>
void Map::Draw()
{
	MV1SetPosition(domeHandle, VGet(0, 0, 0));
	MV1SetRotationXYZ(domeHandle, VGet(0, rotationDomeY, 0));
	MV1DrawModel(domeHandle);
}


