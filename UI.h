#pragma once
#include "DxLib.h"
#include"Sound.h"
#include <vector>
#include <cmath>

class Ui
{
public:
		Ui();							// �R���X�g���N�^.
	~Ui();							// �f�X�g���N�^.

	void Load();
	void DrawHighScore();
	void isDrawUi(int& Displayfloor);
	void underLine();
	//�n�C�X�R�A�ۑ��֐�
	void SaveHiScore(int Displayfloor);
	void isDrawStamina(float staminaCountdown);
	void DrawTitle();//�^�C�g���`��p
	void HiScoreNotification(int Displayfloor);//�n�C�X�R�A�ʒm
	void tutorial();
	void DrawFloorString(int x, int Displayfloor, unsigned int color);
	bool CountDown();
	void ResultUi();
	unsigned int HSVtoRGB(float h, float s, float v);
	bool getGameCountDown()const 
	{
		return limitflg;
	}
private:
	const float WorldlineSize = 500.0f;
	const float UnderlineSize = 2.0f;
	int HiScore;
	int Ranking[5];
	int smallUIHandle;//������UI���n
	int bigUIHandle;
	int nikukyuHandle;
	int blinkFrameCounter; // �t���[���J�E���^(�X�^�~�i�p
	bool isBlinking;       // �_�Ńt���O(�X�^�~�i�p
	int limitblinkFrameCounter;//�t���[���J�E���^(���X�g�`�����X�X�^�~�i�p
	bool islimitBlinking;       // �_�Ńt���O(���X�g�`�����X�X�^�~�i�p
	int blinkFrameCounter2; // �t���[���J�E���^(�X�R�A�ʒm�p
	bool isBlinking2;       // �_�Ńt���O(�X�R�A�ʒm�p
	bool isBlinking3;	//�_�Ńt���O(���U���g��ʗp
	int blinkFrameCounter3;//�t���[���J�E���^�i���U���g��ʗp
	bool isBlinking4;	//�_�Ńt���O(�c�莞�ԗp
	int blinkFrameCounter4;//�t���[���J�E���^�i�c�莞�ԗp�p
	bool displayOnceFlag;//�n�C�X�R�A�ʒm�p�t���O
	bool displayOnceFlag2;//���X�g�`�����X�ʒm�p�t���O
	int HiScoreNotificationX;
	int GameCountDown;
	bool ResultInstall;
	bool playnowSoundflg;
	//���ԗp
	int mMiliSec;    // �P�b�ȉ��̕b�����v�Z�i�����_���ʂ܂Łj
	bool lastNoticePlayed; // �x�����Đ��t���O
	DWORD mTime;
	DWORD mNowTime;
	Sound* sound = new Sound();
	int frameCount = 0;
	bool limitflg;
};
