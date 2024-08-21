#include"UI.h"
Ui::Ui()
{
    // ********** �t�H���g�̃��[�h **********
    LPCSTR font_path = "UI/001Shirokuma-Regular.otf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
    if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
    }
    else {
        // �t�H���g�Ǎ��G���[����
        MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
    }
    //// �t�H���g�̕ύX
    ChangeFont("���낭�܃t�H���g", DX_CHARSET_DEFAULT);
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
    //���U���g������ɌĂяo�����ۂɁA�����L���O�ɃX�R�A��ۑ�����B
    ResultInstall = false;

    HiScoreNotificationX = 900;
    GameCountDown = 90;//�Q�[�����̃J�E���g�_�E���ݒ�
    Ranking[0] = 70;
    Ranking[1] = 50;
    Ranking[2] = 45;
    Ranking[3] = 20;
    Ranking[4] = 0;
    playnowSoundflg = false;
    lastNoticePlayed = false;
    nikukyuHandle = LoadGraph("UI/����.png");
    frameCount = 0;
}

Ui::~Ui()
{
    //�����Ȃ�
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
    // �o�u���\�[�g
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4 - i; ++j) {
            if (Ranking[j] < Ranking[j + 1]) {
                // �אڂ���v�f�̒l������
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
    DrawFormatString(300, 15, GetColor(109, 41, 50), "�n�C�X�R�A");
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
    // �Q�[���J�E���g�_�E����0�ȉ��̎��ɓ_�Ńt���O��ݒ�
    if (limitflg == true)
    {
        islimitBlinking = true;
    }
    else
    {
        islimitBlinking = false;
        limitblinkFrameCounter = 0; // �_�ł��Ă��Ȃ��Ƃ��̓t���[���J�E���^�����Z�b�g
    }

    // �X�^�~�i�����ȉ��ɂȂ�����_�ŊJ�n
    if (staminaCountdown <= 3|| limitflg == true) // 臒l��ݒ� (�����ł�3)
    {
        isBlinking = true;
    }
    else
    {
        isBlinking = false;
        blinkFrameCounter = 0; // �_�ł��Ă��Ȃ��Ƃ��̓t���[���J�E���^�����Z�b�g
    }

    // �X�^�~�i�o�[�̓_�Ō��ʂ̎���
    if (isBlinking)
    {
        blinkFrameCounter++;
        // 30�t���[�����ƂɐF�����݂ɕύX
        if ((blinkFrameCounter / 15) % 2 == 0)
        {
            DrawBox(415, 100, 415 + staminaCountdown * 30, 120, GetColor(255, 246, 233), TRUE);
        }
        else
        {
            // �_�Ŏ��̐F (�����ł͐�)
            DrawBox(415, 100, 415 + staminaCountdown * 30, 120, GetColor(255, 0, 0), TRUE);
        }
    }
    else
    {
        // �ʏ펞�̐F
        DrawBox(415, 100, 415 + staminaCountdown * 30, 120, GetColor(255, 246, 233), TRUE);
    }

    // �X�^�~�i�̕�����_�ł����鏈��
    if (islimitBlinking)
    {
        limitblinkFrameCounter++;
        // 30�t���[�����ƂɐF�����݂ɕύX
        if ((limitblinkFrameCounter / 15) % 2 == 0)
        {
            SetFontSize(20);
            DrawFormatString(308, 98, GetColor(255, 246, 233), "�X�^�~�i");
        }
        else
        {
            SetFontSize(20);
            DrawFormatString(308, 98, GetColor(255, 0, 0), "�X�^�~�i");
        }
    }
    else
    {
        SetFontSize(20);
        DrawFormatString(308, 98, GetColor(255, 246, 233), "�X�^�~�i");
    }
}
void Ui::DrawFloorString(int x, int Displayfloor, unsigned int color)
{
    DrawFormatString(x, 300, color, "%d", Displayfloor);
}

void Ui::isDrawUi(int& Displayfloor)
{
  

    // 2�b�i120�t���[���j�ԓ_�ł���悤�ɂ���
    const int BLINK_DURATION_FRAMES = 80;

    // 50�i���ƂŃt���[���J�E���^���J�n
    if (Displayfloor % 50 == 0 && blinkFrameCounter2 == 0 && Displayfloor != 0)
    {
        isBlinking2 = true;
        blinkFrameCounter2 = 1; // �J�E���^��1����X�^�[�g
        sound->StartSound();
    }

    // �t���[���J�E���^��0�łȂ���΁A�_�ł̏�Ԃ𑱂���
    if (blinkFrameCounter2 > 0)
    {
        blinkFrameCounter2++;
        // �_�ł��I�������t���[���J�E���^�����Z�b�g
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
        // 30�t���[�����ƂɐF�����݂ɕύX
        //���F
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
        //��
        SetFontSize(70);
        color = GetColor(255, 246, 233);
        DrawFloorString(x, Displayfloor, color);
    }


}

void Ui::underLine()
{
    // XYZ��
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
    DrawFormatString(210, 77, GetColor(109, 41, 50), "�ɂ�񂱁@���炢��");
    DrawRotaGraph(467, 100, 0.4, 0, nikukyuHandle, TRUE);
    // ��F�����x50%�̔��F�̎l�p�`��`�悷��
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(0, 600, 900, 700, GetColor(0, 0, 0), TRUE);
    // �`�惂�[�h�����ɖ߂�
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    SetFontSize(50);
    DrawFormatString(135, 620, GetColor(255, 246, 233), "ENTER�L�[�������Ă�!");
    HiScore = 0;
    GameCountDown = 90;//�Q�[�����̃J�E���g�_�E���ݒ�
    ResultInstall = false;
    sound->LastspurtSound(false);
    SetFontSize(30);
    DrawFormatString(200, 1030, GetColor(255, 246, 233), "�yBGM: IchinoseSound �l�z");
}

void Ui::HiScoreNotification(int Displayfloor)
{
    if (Displayfloor > 0 && displayOnceFlag == false)
    {
        if (Ranking[0] < Displayfloor)
        {
            HiScoreNotificationX-= 5;
            // ��F�����x50%�̔��F�̎l�p�`��`�悷��
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawBox(0, 600, 900, 700, GetColor(0, 0, 0), TRUE);
            // �`�惂�[�h�����ɖ߂�
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            SetFontSize(50);
            DrawFormatString(HiScoreNotificationX, 625, GetColor(255, 246, 233), "�n�C�X�R�A�X�V!");
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
        // ��F�����x50%�̔��F�̎l�p�`��`�悷��  
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawBox(0, 0, 900, 1800, GetColor(0, 0, 0), TRUE);
        // �`�惂�[�h�����ɖ߂�
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawRotaGraph(440, 400, 15, 0, smallUIHandle, TRUE);
        SetFontSize(30);
        DrawFormatString(150, 240, GetColor(109, 41, 50), "~������@~");
        DrawFormatString(230, 280, GetColor(109, 41, 50), "SPACE:��i�o��");
        DrawFormatString(230, 320, GetColor(109, 41, 50), "Ctrl:���񂵂Ĉ�i�o��");
        DrawFormatString(100, 380, GetColor(109, 41, 50), "���ڎw���ĂЂ�����K�i��o�낤!");
        DrawFormatString(235, 420, GetColor(109, 41, 50), "�X�^�~�i���Ȃ��Ȃ�Ɨ��������Ⴄ��!");
        DrawFormatString(330, 460, GetColor(109, 41, 50), "�������Ԃ�90�b!");
        DrawFormatString(235, 520, GetColor(109, 41, 50), "~ENTER�������ăX�^�[�g~");
    }

}
bool Ui::CountDown()
{
    //�_�Ō��ʂ̊Ǘ�
    isBlinking4 = false;
    //�P�b(1000�~���b�ȏ�)�o�߂������H
    mNowTime = GetNowCount();
    if (mNowTime - mTime > 1000)
    {
        GameCountDown--;

        //�J�E���g�_�E��0�ȉ��ɂȂ�����0�ɖ߂��B
        if (GameCountDown < 0)
        {
            GameCountDown = 0;
        }

        //�v��������݂ɃZ�b�g
        mTime = mNowTime;
    }
    if (GameCountDown == 10 && !lastNoticePlayed) // �ύX: �t���O���`�F�b�N
    {
        sound->LastnoticeSound();
        sound->MainthemaSound(false);
        sound->LastspurtSound(true);
        lastNoticePlayed = true; // �t���O��ݒ�
    }
    if (GameCountDown < 10)
    {
        isBlinking4 = true;
    }
    //1�b�ȉ��`�����_���ʂ܂ł̕b�����Z�o
    mMiliSec = (mNowTime - mTime) / 10;

    if (isBlinking4) {
        blinkFrameCounter3++;
    }
    SetFontSize(30);
    DrawFormatString(48, 18, GetColor(255, 246, 233), "�c�莞��");
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
        // ��F�����x50%�̔��F�̎l�p�`��`�悷��
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawBox(0, 600, 900, 700, GetColor(0, 0, 0), TRUE);
        // �`�惂�[�h�����ɖ߂�
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        SetFontSize(50);
        DrawFormatString(HiScoreNotificationX, 625, GetColor(255, 246, 233), "���X�g�`�����X!(�X�^�~�i�ቺ��)");
        if (HiScoreNotificationX < -850)
        {
            HiScoreNotificationX = 900;
            displayOnceFlag2 = true;
        }
    }

    // �_�Ō��ʂ̎���
    else if (isBlinking4)
    {
        // 30�t���[�����ƂɐF�����݂ɕύX
        if ((blinkFrameCounter3 / 15) % 2 == 0) {
            DrawFormatString(x, 40, GetColor(255, 246, 233), "%d", GameCountDown);
        }
        else {
            // �_�Ŏ��̐F (�����ł͐�)
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
    // ��F�����x50%�̔��F�̎l�p�`��`�悷��  
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(0, 0, 900, 1800, GetColor(0, 0, 0), TRUE);
    // �`�惂�[�h�����ɖ߂�
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    if (ResultInstall == false)
    {
        Ranking[4] = HiScore;
        ResultInstall = true;
    }
    // �o�u���\�[�g
    for (int i = 0; i < 4; ++i) { 
        for (int j = 0; j < 4 - i; ++j) {
            if (Ranking[j] < Ranking[j + 1]) {
                // �אڂ���v�f�̒l������
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
        // �F����ς��ē��F������
        float hue = (frameCount % 360);
        unsigned int color = HSVtoRGB(hue, 1.0f, 1.0f);

        // �e�L�X�g�̕`��
        SetFontSize(50);
        DrawString(210, 235, "No.1SCORE!", color);

        frameCount++;
    }
    else
    {
        DrawString(210, 220, "TIMEOVER", GetColor(255, 128, 128));
    }
    SetFontSize(55);
    DrawString(220, 350, "�n�C�X�R�A", GetColor(109, 41, 50));
    DrawFormatString(590, 350, GetColor(109, 41, 50), "%d", HiScore);
    SetFontSize(40);

    // �_�Ō��ʂ̊Ǘ�
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

    // �n�C�X�R�A��\��
    for (int i = 0; i < 5; ++i) {
        int y = 410 + i * 50;

        // �_�Ō��ʂ̎���
        if (Ranking[i] == HiScore && isBlinking3) {
            // 30�t���[�����ƂɐF�����݂ɕύX
            if ((blinkFrameCounter3 / 15) % 2 == 0) {
                DrawFormatString(280, y, GetColor(255, 255, 255), "%d", i + 1);
                DrawFormatString(560, y, GetColor(255, 255, 255), "%d", Ranking[i]);
            }
            else {
                // �_�Ŏ��̐F (�����ł͐�)
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
    //�e��t���O������
    playnowSoundflg = false;
    GameCountDown = 90;//�^�C�}�[���Z�b�g
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

///���X�g�`�����X�ʒm�A�c�莞�ԃ^�C�}�[���L;120