#pragma once
#include "DxLib.h"

class Sound
{
public:
	Sound();							// �R���X�g���N�^.
	~Sound();							// �f�X�g���N�^.

	void MainthemaSound(bool playORstopflg);
	void StartSound();
	void LastspurtSound(bool playORstopflg);
	void DeadSound(bool playORstopflg);
	void ResultSound();
	void UpSound();
	void LastnoticeSound();
private:
	int isMainthemaHandle;
	int isLastspurtHandle;
	int isLastnoticeHandle;
	int isUpsoundHandle;
	int isDownsoundHandle;
	int isCatvoiceHandle;//�X�^�[�g�T�E���h�p
	int isClapHandle;
};
