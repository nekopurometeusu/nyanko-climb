#pragma once
#include "DxLib.h"
#include"Sound.h"
#include <vector>
#include <cmath>

class Ui
{
public:
		Ui();							// コンストラクタ.
	~Ui();							// デストラクタ.

	void Load();
	void DrawHighScore();
	void isDrawUi(int& Displayfloor);
	void underLine();
	//ハイスコア保存関数
	void SaveHiScore(int Displayfloor);
	void isDrawStamina(float staminaCountdown);
	void DrawTitle();//タイトル描画用
	void HiScoreNotification(int Displayfloor);//ハイスコア通知
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
	int smallUIHandle;//小さいUI下地
	int bigUIHandle;
	int nikukyuHandle;
	int blinkFrameCounter; // フレームカウンタ(スタミナ用
	bool isBlinking;       // 点滅フラグ(スタミナ用
	int limitblinkFrameCounter;//フレームカウンタ(ラストチャンススタミナ用
	bool islimitBlinking;       // 点滅フラグ(ラストチャンススタミナ用
	int blinkFrameCounter2; // フレームカウンタ(スコア通知用
	bool isBlinking2;       // 点滅フラグ(スコア通知用
	bool isBlinking3;	//点滅フラグ(リザルト画面用
	int blinkFrameCounter3;//フレームカウンタ（リザルト画面用
	bool isBlinking4;	//点滅フラグ(残り時間用
	int blinkFrameCounter4;//フレームカウンタ（残り時間用用
	bool displayOnceFlag;//ハイスコア通知用フラグ
	bool displayOnceFlag2;//ラストチャンス通知用フラグ
	int HiScoreNotificationX;
	int GameCountDown;
	bool ResultInstall;
	bool playnowSoundflg;
	//時間用
	int mMiliSec;    // １秒以下の秒数を計算（小数点第二位まで）
	bool lastNoticePlayed; // 警告音再生フラグ
	DWORD mTime;
	DWORD mNowTime;
	Sound* sound = new Sound();
	int frameCount = 0;
	bool limitflg;
};
