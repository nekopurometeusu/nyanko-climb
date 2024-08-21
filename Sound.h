#pragma once
#include "DxLib.h"

class Sound
{
public:
	Sound();							// コンストラクタ.
	~Sound();							// デストラクタ.

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
	int isCatvoiceHandle;//スタートサウンド用
	int isClapHandle;
};
