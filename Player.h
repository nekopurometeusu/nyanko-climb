#pragma once
#include "DxLib.h"
#include"Sound.h"
#include"UI.h"
#include <vector>
class Ui;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player final
{
public:
    Player();                // コンストラクタ.
    ~Player();               // デストラクタ.

    void Load(float& mCountdown); // 更新
    void Update(int& Displayfloor);    // 更新.
    void Draw();            // 描画.
    void DrawTitle();//タイトル描画用
    void UpdateMiss(int DeadCountdown);//ミス演出用
    void tutorial();
    bool StaminaManagement(int Displayfloor,float& staminaCountdown,const Ui&ui);
    // モデルハンドルの取得.
    int GetModelHandle() const { return modelHandle; }

    const VECTOR& GetPos() const { return pos; }
    const VECTOR& GetDir() const { return dir; }

private:

    int     modelHandle;    // モデルハンドル.
    int     BackgroundModelHandle[6];//6体分のハンドル
    VECTOR  Backgroundpos[6];            // ポジション.
    VECTOR  pos;            // ポジション.
    VECTOR  titlepos;       // タイトルプレイヤーポジション
    VECTOR  velocity;       // 移動力.
    VECTOR  dir;            // 回転方向.
    bool    Rightmoveflg = 0;
    bool    Leftmoveflg = 0;
    int     previousKeyState = 0;
    bool    moveTriggered = false; // 移動がトリガーされたかどうかを保持
    bool    moveChange = true;
    // モデルの回転角度を保存する変数
    float rotationAngleX[6];
    float rotationAngleY[6];
    // 静的定数.
    static const float Speed;
    static const float Scale;
    static const float titleScale;
    int nowFloor = 0;
    //スタミナの初期値
    int initialStamina = 4;
    //時間用
    int mMiliSec;    // １秒以下の秒数を計算（小数点第二位まで）

    DWORD mTime;
    DWORD mNowTime;
    Sound* sound = new Sound();
};