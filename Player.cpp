#include "Player.h"
#include "DxLib.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Player::Speed = static_cast<float>(100000.0 / 60.0 / 60.0 / 60.0);
const float Player::Scale = 0.0004f;        // スケール
const float Player::titleScale = 0.0010f;
const int catnumber = 6;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
    : modelHandle(-1)
{
    //// ３Ｄモデルの読み込み
    //modelHandle = MV1LoadModel("data/バスティオンsan.mv1");
    //neko.mv1

     // ３Ｄモデルの読み込み
    modelHandle = MV1LoadModel("data/neko3.mv1");
    for (int i = 0; i < catnumber; i++)
    {
        BackgroundModelHandle[i] = MV1DuplicateModel(modelHandle);
        rotationAngleX[i] = GetRand(360) * DX_PI_F / 180.0f; // 0から360度のランダムな回転（ラジアン）
        rotationAngleY[i] = GetRand(360) * DX_PI_F / 180.0f; // 0から360度のランダムな回転（ラジアン）
    }
    for (int i = 0; i < catnumber; i++)
    {
        int randomValueX = GetRand(8) - 4;
        int randomValueY = GetRand(9) + 6;
        int randomValueZ = GetRand(8) - 4;
        Backgroundpos[i] = VGet(randomValueX, randomValueY, randomValueZ);
    }
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
    // モデルのアンロード.
    MV1DeleteModel(modelHandle);

    for (int i = 0; i < catnumber; i++)
    {
        MV1DeleteModel(BackgroundModelHandle[i]);
    }
}
/// <summary>
/// ロード
/// </summary>
void Player::Load(float& mCountdown)
{
    titlepos = VGet(0, -1, 0);
    pos = VGet(0, 0, 0);
    velocity = VGet(0, 0, 0);
    dir = VGet(0, 0, 0);

    moveChange = true;
    MV1SetRotationXYZ(modelHandle, VGet(0.0f, 80.0f, 0.0f));
    //スタミナの最大値
    initialStamina = 6;
    mCountdown = initialStamina;
}
/// <summary>
/// 更新
/// </summary>
void Player::Update(int& Displayfloor)
{
    // 現在のキー入力状態を取得
    int currentKeyState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // 単純に方向転換
    dir = VGet(0, 0, 0);

    // 右キーが押された瞬間を検出
    if ((CheckHitKey(KEY_INPUT_SPACE)) && !(previousKeyState & KEY_INPUT_SPACE) && !moveTriggered)
    {
        if (moveChange == true)
        {
            Rightmoveflg = true;
        }
        else
        {
            Leftmoveflg = true;
        }

        moveTriggered = true;
    }
    // コントロールキーが押された瞬間を検出
    if ((CheckHitKey(KEY_INPUT_LCONTROL)) && !(previousKeyState & KEY_INPUT_LCONTROL) && !moveTriggered)
    {
        if (moveChange == false)
        {
            moveChange = true;
        }
        else
        {
            moveChange = false;
        }
        if (moveChange == true)
        {
            Rightmoveflg = true;
        }
        else
        {
            Leftmoveflg = true;
        }
        moveTriggered = true;
    }

    if (!(CheckHitKey(KEY_INPUT_SPACE)) && !(CheckHitKey(KEY_INPUT_LCONTROL)))
    {
        moveTriggered = false; // キーが離されたらフラグをリセット
    }

    if (Rightmoveflg == true)
    {
        MV1SetRotationXYZ(modelHandle, VGet(0.0f, 80.0f, 0.0f));
        dir = VAdd(dir, VGet(2.0f, 2.0f, 0.0f)); // 右
        Displayfloor++;
        Rightmoveflg = false;
        if (sound != nullptr)
        {
            sound->UpSound();
        }
    }
    else if (Leftmoveflg == true)
    {
        MV1SetRotationXYZ(modelHandle, VGet(0.0f, -80.2f, 0.0f));
        dir = VAdd(dir, VGet(-2.0f, 2.0f, 0.0f)); // 左
        Displayfloor++;
        Leftmoveflg = false;
        if (sound != nullptr)
        {
            sound->UpSound();
        }
    }

    // ポジションを更新
    pos = VAdd(pos, dir);

    // 3Dモデルのスケール決定
    MV1SetScale(modelHandle, VGet(Scale, Scale, Scale));

    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, pos);

    // 現在のキー入力状態を次回のために保存
    previousKeyState = currentKeyState;
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
    // ３Ｄモデルの描画
    MV1DrawModel(modelHandle);
}
/// <summary>
/// スタミナ管理関数
/// </summary>
bool Player::StaminaManagement(int Displayfloor, float& staminaCountdown, const Ui& ui)
{
    bool isDeadjudgeflg = false;
    bool Timelimit = ui.getGameCountDown();
    // フレームレートを定義 (例: 60 FPS)
    const int FPS = 60;
    const float decrementPerFrame = 1.0f / FPS; // 毎秒1減少するための基準

    // タイムリミットに基づくスタミナ減少量の設定
    float staminaDecrement = 0;
    if (!moveTriggered) // moveTriggeredがfalseの時
    {
        if (Displayfloor != 0)
        {
            if (Timelimit == true)
            {
                staminaDecrement = 2 * decrementPerFrame; // 毎秒2減少
            }
            else if (Displayfloor > 100)
            {
                staminaDecrement = 1.5f * decrementPerFrame; // 毎秒1.5減少
            }
            else if (Displayfloor > 50)
            {
                staminaDecrement = 1 * decrementPerFrame; // 毎秒1減少
            }
            else
            {
                staminaDecrement = 0.5f * decrementPerFrame; // 毎秒0.5減少
            }
        }

        // スタミナをフレームごとに減少させる
        staminaCountdown -= staminaDecrement;

        // カウントダウン0以下になったら0に戻す。
        if (staminaCountdown < 0)
        {
            staminaCountdown = 0;
        }
    }
    else
    {
        staminaCountdown = initialStamina;
    }

    // スタミナが0の場合、死亡フラグを立てる
    if (staminaCountdown == 0)
    {
        isDeadjudgeflg = true;
    }

    return isDeadjudgeflg;
}
/// <summary>
/// タイトルの描画
/// </summary>
void Player::DrawTitle()
{
    for (int i = 0; i < catnumber; i++)
    {
        // 単純に方向転換
        dir = VGet(0, 0, 0);

        dir = VAdd(dir, VGet(0.0f, -0.1f, 0.0f));

        // ポジションを更新
        Backgroundpos[i] = VAdd(Backgroundpos[i], dir);

        if (Backgroundpos[i].y < -8.0f)
        {
            int randomValueX = GetRand(8) - 4;
            int randomValueY = GetRand(9) + 6;
            int randomValueZ = GetRand(8) - 4;
            Backgroundpos[i] = VGet(randomValueX, randomValueY, randomValueZ);
        }

        // 回転角度を少しずつ増加させる
        rotationAngleX[i] += 0.01f; // X軸の回転速度を調整
        rotationAngleY[i] += 0.02f; // Y軸の回転速度を調整

        // モデルの回転を設定
        MV1SetRotationXYZ(BackgroundModelHandle[i], VGet(rotationAngleX[i], rotationAngleY[i], 0.0f));
        // 3D背景モデルのスケール決定
        MV1SetScale(BackgroundModelHandle[i], VGet(Scale, Scale,Scale));
        // ３D背景モデルのポジション設定
        MV1SetPosition(BackgroundModelHandle[i], Backgroundpos[i]);
        // ３Ｄ背景モデルの描画
        MV1DrawModel(BackgroundModelHandle[i]);
    }


    MV1SetRotationXYZ(modelHandle, VGet(0.0f, 0.0f, 0.0f));
    // 3Dモデルのスケール決定
    MV1SetScale(modelHandle, VGet(titleScale, titleScale, titleScale));
    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, titlepos);
    // ３Ｄモデルの描画
    MV1DrawModel(modelHandle);
}
/// <summary>
/// ミス時の描画
/// </summary>
void Player::UpdateMiss(int DeadCountdown)
{
    // 単純に方向転換
    dir = VGet(0, 0, 0);
    if (DeadCountdown < 3)
    {
        dir = VAdd(dir, VGet(0.0f, -0.1f, 0.0f)); // 右
    }
    if (DeadCountdown == 3)
    {
        sound->DeadSound(true);
    }
    if (DeadCountdown == 0)
    {
        sound->DeadSound(false);
    }
    // ポジションを更新
    pos = VAdd(pos, dir);

    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, pos);
}

void Player::tutorial()
{
    // 3Dモデルのスケール決定
    MV1SetScale(modelHandle, VGet(Scale, Scale, Scale));

    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, pos);
}

