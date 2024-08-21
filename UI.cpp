#include"UI.h"
Ui::Ui()
{
    // ********** フォントのロード **********
    LPCSTR font_path = "UI/001Shirokuma-Regular.otf"; // 読み込むフォントファイルのパス
    if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
    }
    else {
        // フォント読込エラー処理
        MessageBox(NULL, "フォント読込失敗", "", MB_OK);
    }
    //// フォントの変更
    ChangeFont("しろくまフォント", DX_CHARSET_DEFAULT);
    smallUIHandle = LoadGraph("UI/UI_Base(small).png");
    bigUIHandle = LoadGraph("UI/UI_Base(big).png");
    HiScore = 0;
    SetBackgroundColor(64,162,227);
    blinkFrameCounter = 0;
    isBlinking = false;

    limitblinkFrameCounter = 0;
    islimitBlinking = false;

    blinkFrameCounter2 = 0;
    isBlinking2 = false;
    //リザルトを初回に呼び出した際に、ランキングにスコアを保存する。
    ResultInstall = false;

    HiScoreNotificationX = 900;
    GameCountDown = 90;//ゲーム中のカウントダウン設定
    Ranking[0] = 70;
    Ranking[1] = 50;
    Ranking[2] = 45;
    Ranking[3] = 20;
    Ranking[4] = 0;
    playnowSoundflg = false;
    lastNoticePlayed = false;
    nikukyuHandle = LoadGraph("UI/肉球.png");
    frameCount = 0;
}

Ui::~Ui()
{
    //処理なし
}

void Ui::Load()
{
    displayOnceFlag = false;
    displayOnceFlag2 = false;
    limitflg = false;
    HiScoreNotificationX = 900;
    if (GameCountDown > 11&& playnowSoundflg == false)
    {
        sound->MainthemaSound(false);
        sound->MainthemaSound(true);
        playnowSoundflg = true;
    }
    // バブルソート
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4 - i; ++j) {
            if (Ranking[j] < Ranking[j + 1]) {
                // 隣接する要素の値を交換
                int temp = Ranking[j];
                Ranking[j] = Ranking[j + 1];
                Ranking[j + 1] = temp;
            }
        }
    }
}
void Ui::DrawHighScore()
{
    DrawRotaGraph(445, 20, 3.5, 0, smallUIHandle, TRUE);
    SetFontSize(30);
    DrawFormatString(300, 15, GetColor(109, 41, 50), "ハイスコア");
    if (Ranking[0] > 99)
    {
        DrawFormatString(517, 15, GetColor(109, 41, 50), "%d", Ranking[0]);
    }
    else
    {
        DrawFormatString(537, 15, GetColor(109, 41, 50), "%d", Ranking[0]);
    }
}
void Ui::isDrawStamina(float staminaCountdown)
{
    // ゲームカウントダウンが0以下の時に点滅フラグを設定
    if (limitflg == true)
    {
        islimitBlinking = true;
    }
    else
    {
        islimitBlinking = false;
        limitblinkFrameCounter = 0; // 点滅していないときはフレームカウンタをリセット
    }

    // スタミナが一定以下になったら点滅開始
    if (staminaCountdown <= 3|| limitflg == true) // 閾値を設定 (ここでは3)
    {
        isBlinking = true;
    }
    else
    {
        isBlinking = false;
        blinkFrameCounter = 0; // 点滅していないときはフレームカウンタをリセット
    }

    // スタミナバーの点滅効果の実装
    if (isBlinking)
    {
        blinkFrameCounter++;
        // 30フレームごとに色を交互に変更
        if ((blinkFrameCounter / 15) % 2 == 0)
        {
            DrawBox(415, 100, 415 + staminaCountdown * 30, 120, GetColor(255, 246, 233), TRUE);
        }
        else
        {
            // 点滅時の色 (ここでは赤)
            DrawBox(415, 100, 415 + staminaCountdown * 30, 120, GetColor(255, 0, 0), TRUE);
        }
    }
    else
    {
        // 通常時の色
        DrawBox(415, 100, 415 + staminaCountdown * 30, 120, GetColor(255, 246, 233), TRUE);
    }

    // スタミナの文字を点滅させる処理
    if (islimitBlinking)
    {
        limitblinkFrameCounter++;
        // 30フレームごとに色を交互に変更
        if ((limitblinkFrameCounter / 15) % 2 == 0)
        {
            SetFontSize(20);
            DrawFormatString(308, 98, GetColor(255, 246, 233), "スタミナ");
        }
        else
        {
            SetFontSize(20);
            DrawFormatString(308, 98, GetColor(255, 0, 0), "スタミナ");
        }
    }
    else
    {
        SetFontSize(20);
        DrawFormatString(308, 98, GetColor(255, 246, 233), "スタミナ");
    }
}
void Ui::DrawFloorString(int x, int Displayfloor, unsigned int color)
{
    DrawFormatString(x, 300, color, "%d", Displayfloor);
}

void Ui::isDrawUi(int& Displayfloor)
{
  

    // 2秒（120フレーム）間点滅するようにする
    const int BLINK_DURATION_FRAMES = 80;

    // 50段ごとでフレームカウンタを開始
    if (Displayfloor % 50 == 0 && blinkFrameCounter2 == 0 && Displayfloor != 0)
    {
        isBlinking2 = true;
        blinkFrameCounter2 = 1; // カウンタを1からスタート
        sound->StartSound();
    }

    // フレームカウンタが0でなければ、点滅の状態を続ける
    if (blinkFrameCounter2 > 0)
    {
        blinkFrameCounter2++;
        // 点滅が終わったらフレームカウンタをリセット
        if (blinkFrameCounter2 > BLINK_DURATION_FRAMES)
        {
            isBlinking2 = false;
            blinkFrameCounter2 = 0;
        }
    }

    SetFontSize(70);

    int x;
    if (Displayfloor > 99)
    {
        x = 355;
    }
    else if (Displayfloor > 9)
    {
        x = 390;
    }
    else
    {
        x = 425;
    }
    unsigned int color;
    if (isBlinking2)
    {
        // 30フレームごとに色を交互に変更
        //黄色
        color = ((blinkFrameCounter2 / 15) % 2 == 0) ? GetColor(255, 255, 0) : GetColor(255, 246, 233);
        if ((blinkFrameCounter2 / 15) % 2 == 0)
        {
            SetFontSize(80);
            DrawFloorString(x - 15, Displayfloor, color);
        }
        else
        {
            SetFontSize(70);
            DrawFloorString(x, Displayfloor, color);
        }
    }
    else
    {
        //白
        SetFontSize(70);
        color = GetColor(255, 246, 233);
        DrawFloorString(x, Displayfloor, color);
    }


}

void Ui::underLine()
{
    // XYZ軸
    DrawLine3D(VGet(-WorldlineSize, 0, 0), VGet(WorldlineSize, 0, 0), GetColor(255, 0, 0));
    DrawLine3D(VGet(0, -WorldlineSize, 0), VGet(0, WorldlineSize, 0), GetColor(0, 255, 0));
    DrawLine3D(VGet(0, 0, -WorldlineSize), VGet(0, 0, WorldlineSize), GetColor(0, 0, 255));
}

void Ui::SaveHiScore(int Displayfloor)
{
    if (HiScore < Displayfloor)
    {
        HiScore = Displayfloor;
    }
}

void Ui::DrawTitle()
{

    DrawRotaGraph(445, 100, 5.5, 0, smallUIHandle, TRUE);
    SetFontSize(55);
    DrawFormatString(210, 77, GetColor(109, 41, 50), "にゃんこ　くらいむ");
    DrawRotaGraph(467, 100, 0.4, 0, nikukyuHandle, TRUE);
    // 例：透明度50%の白色の四角形を描画する
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(0, 600, 900, 700, GetColor(0, 0, 0), TRUE);
    // 描画モードを元に戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    SetFontSize(50);
    DrawFormatString(135, 620, GetColor(255, 246, 233), "ENTERキーを押してね!");
    HiScore = 0;
    GameCountDown = 90;//ゲーム中のカウントダウン設定
    ResultInstall = false;
    sound->LastspurtSound(false);
    SetFontSize(30);
    DrawFormatString(200, 1030, GetColor(255, 246, 233), "【BGM: IchinoseSound 様】");
}

void Ui::HiScoreNotification(int Displayfloor)
{
    if (Displayfloor > 0 && displayOnceFlag == false)
    {
        if (Ranking[0] < Displayfloor)
        {
            HiScoreNotificationX-= 5;
            // 例：透明度50%の白色の四角形を描画する
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawBox(0, 600, 900, 700, GetColor(0, 0, 0), TRUE);
            // 描画モードを元に戻す
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            SetFontSize(50);
            DrawFormatString(HiScoreNotificationX, 625, GetColor(255, 246, 233), "ハイスコア更新!");
            if (HiScoreNotificationX < -500)
            {
                HiScoreNotificationX = 900;
                displayOnceFlag = true;
            }
        }
    }
}

void Ui::tutorial()
{
    if (HiScore == 0)
    {
        // 例：透明度50%の白色の四角形を描画する  
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawBox(0, 0, 900, 1800, GetColor(0, 0, 0), TRUE);
        // 描画モードを元に戻す
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawRotaGraph(440, 400, 15, 0, smallUIHandle, TRUE);
        SetFontSize(30);
        DrawFormatString(150, 240, GetColor(109, 41, 50), "~操作方法~");
        DrawFormatString(230, 280, GetColor(109, 41, 50), "SPACE:一段登る");
        DrawFormatString(230, 320, GetColor(109, 41, 50), "Ctrl:旋回して一段登る");
        DrawFormatString(100, 380, GetColor(109, 41, 50), "上を目指してひたすら階段を登ろう!");
        DrawFormatString(235, 420, GetColor(109, 41, 50), "スタミナがなくなると落下しちゃうよ!");
        DrawFormatString(330, 460, GetColor(109, 41, 50), "制限時間は90秒!");
        DrawFormatString(235, 520, GetColor(109, 41, 50), "~ENTERを押してスタート~");
    }

}
bool Ui::CountDown()
{
    //点滅効果の管理
    isBlinking4 = false;
    //１秒(1000ミリ秒以上)経過したか？
    mNowTime = GetNowCount();
    if (mNowTime - mTime > 1000)
    {
        GameCountDown--;

        //カウントダウン0以下になったら0に戻す。
        if (GameCountDown < 0)
        {
            GameCountDown = 0;
        }

        //計測基準を現在にセット
        mTime = mNowTime;
    }
    if (GameCountDown == 10 && !lastNoticePlayed) // 変更: フラグをチェック
    {
        sound->LastnoticeSound();
        sound->MainthemaSound(false);
        sound->LastspurtSound(true);
        lastNoticePlayed = true; // フラグを設定
    }
    if (GameCountDown < 10)
    {
        isBlinking4 = true;
    }
    //1秒以下～小数点第二位までの秒数を算出
    mMiliSec = (mNowTime - mTime) / 10;

    if (isBlinking4) {
        blinkFrameCounter3++;
    }
    SetFontSize(30);
    DrawFormatString(48, 18, GetColor(255, 246, 233), "残り時間");
    int x;
    if (GameCountDown > 99)
    {
        x =60;
    }
    else if (GameCountDown > 9)
    {
        x = 75;
    }
    else
    {
        x = 90;
    }
    if (GameCountDown == 0&&displayOnceFlag2 == false)
    {
        DrawFormatString(90, 40, GetColor(255, 0, 0), "0", GameCountDown);
        HiScoreNotificationX -= 5;
        // 例：透明度50%の白色の四角形を描画する
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawBox(0, 600, 900, 700, GetColor(0, 0, 0), TRUE);
        // 描画モードを元に戻す
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        SetFontSize(50);
        DrawFormatString(HiScoreNotificationX, 625, GetColor(255, 246, 233), "ラストチャンス!(スタミナ低下中)");
        if (HiScoreNotificationX < -850)
        {
            HiScoreNotificationX = 900;
            displayOnceFlag2 = true;
        }
    }

    // 点滅効果の実装
    else if (isBlinking4)
    {
        // 30フレームごとに色を交互に変更
        if ((blinkFrameCounter3 / 15) % 2 == 0) {
            DrawFormatString(x, 40, GetColor(255, 246, 233), "%d", GameCountDown);
        }
        else {
            // 点滅時の色 (ここでは赤)
            DrawFormatString(x, 40, GetColor(255, 0, 0), "%d", GameCountDown);
        }
    }
    else
    {
        DrawFormatString(x, 40, GetColor(255, 246, 233), "%d", GameCountDown);
    }
    if (GameCountDown == 0)
    {
        limitflg = true;
    }
    return limitflg;
}
void Ui::ResultUi()
{
    // 例：透明度50%の白色の四角形を描画する  
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(0, 0, 900, 1800, GetColor(0, 0, 0), TRUE);
    // 描画モードを元に戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    if (ResultInstall == false)
    {
        Ranking[4] = HiScore;
        ResultInstall = true;
    }
    // バブルソート
    for (int i = 0; i < 4; ++i) { 
        for (int j = 0; j < 4 - i; ++j) {
            if (Ranking[j] < Ranking[j + 1]) {
                // 隣接する要素の値を交換
                int temp = Ranking[j];
                Ranking[j] = Ranking[j + 1];
                Ranking[j + 1] = temp;
            }
        }
    }

    DrawRotaGraph(450, 522, 7, 0.0, bigUIHandle, TRUE);
    DrawRotaGraph(450, 252, 5, 0.0, smallUIHandle, TRUE);
    SetFontSize(60);
    if (Ranking[0] == HiScore)
    {
        // 色相を変えて虹色を実現
        float hue = (frameCount % 360);
        unsigned int color = HSVtoRGB(hue, 1.0f, 1.0f);

        // テキストの描画
        SetFontSize(50);
        DrawString(210, 235, "No.1SCORE!", color);

        frameCount++;
    }
    else
    {
        DrawString(210, 220, "TIMEOVER", GetColor(255, 128, 128));
    }
    SetFontSize(55);
    DrawString(220, 350, "ハイスコア", GetColor(109, 41, 50));
    DrawFormatString(590, 350, GetColor(109, 41, 50), "%d", HiScore);
    SetFontSize(40);

    // 点滅効果の管理
    isBlinking3 = false;
    for (int i = 0; i < 5; ++i) {
        if (Ranking[i] == HiScore) {
            isBlinking3 = true;
            break;
        }
    }

    if (isBlinking3) {
        blinkFrameCounter3++;
    }

    // ハイスコアを表示
    for (int i = 0; i < 5; ++i) {
        int y = 410 + i * 50;

        // 点滅効果の実装
        if (Ranking[i] == HiScore && isBlinking3) {
            // 30フレームごとに色を交互に変更
            if ((blinkFrameCounter3 / 15) % 2 == 0) {
                DrawFormatString(280, y, GetColor(255, 255, 255), "%d", i + 1);
                DrawFormatString(560, y, GetColor(255, 255, 255), "%d", Ranking[i]);
            }
            else {
                // 点滅時の色 (ここでは赤)
                DrawFormatString(280, y, GetColor(255, 0, 0), "%d", i + 1);
                DrawFormatString(560, y, GetColor(255, 0, 0), "%d", Ranking[i]);
            }
        }
        else {
            DrawFormatString(280, y, GetColor(109, 41, 50), "%d", i + 1);
            DrawFormatString(560, y, GetColor(109, 41, 50), "%d", Ranking[i]);
        }
    }

    SetFontSize(32);
    DrawString(115, 680, "RETRY PUSH(ENTER)KEY", GetColor(109, 41, 50));
    //各種フラグ初期化
    playnowSoundflg = false;
    GameCountDown = 90;//タイマーリセット
    lastNoticePlayed = false;
}

unsigned int Ui::HSVtoRGB(float h, float s, float v)
{
    int i;
    float f, p, q, t;
    int r, g, b;

    if (s == 0) {
        r = g = b = (int)(v * 255.0f);
    }
    else {
        h /= 60.0f;
        i = (int)floor(h);
        f = h - i;
        p = v * (1.0f - s);
        q = v * (1.0f - s * f);
        t = v * (1.0f - s * (1.0f - f));
        switch (i) {
        case 0:
            r = (int)(v * 255.0f);
            g = (int)(t * 255.0f);
            b = (int)(p * 255.0f);
            break;
        case 1:
            r = (int)(q * 255.0f);
            g = (int)(v * 255.0f);
            b = (int)(p * 255.0f);
            break;
        case 2:
            r = (int)(p * 255.0f);
            g = (int)(v * 255.0f);
            b = (int)(t * 255.0f);
            break;
        case 3:
            r = (int)(p * 255.0f);
            g = (int)(q * 255.0f);
            b = (int)(v * 255.0f);
            break;
        case 4:
            r = (int)(t * 255.0f);
            g = (int)(p * 255.0f);
            b = (int)(v * 255.0f);
            break;
        default:
            r = (int)(v * 255.0f);
            g = (int)(p * 255.0f);
            b = (int)(q * 255.0f);
            break;
        }
    }
    return GetColor(r, g, b);
}

///ラストチャンス通知、残り時間タイマー明記;120