#include<vector>
#include "DxLib.h"
#include"Stairs.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"
#include"UI.h"
#include"Sound.h"
/// <summary>
/// ゲームの状態を保存する列挙体
/// </summary>
enum STATE
{
	STATE_TITLE,		// タイトル.
	STATE_GAME,			// ゲーム中.
	STATE_CLEAR,		// クリア.
	STATE_GAMEOVER,		// ゲームオーバー.
	STATE_INITIALIZATION,// 初期化
	STATE_TUTORIAL,//チュートリアル
	STATE_RESULT//リザルト画面
};
///ゲームの状態を保存する変数
int isGamestatus;
///死亡判定保存フラグ
bool isDeadflg;
///UIで使用するカウントダウン変数
float staminaCountdown;
//初回起動判定フラグ
bool bootflg;
//時間制限フラグ
bool isTimelimitflg;
/// <summary>
/// メイン関数
/// </summary>
///  //時間用
int mMiliSec;    // １秒以下の秒数を計算（小数点第二位まで）
DWORD mTime;
DWORD mNowTime;
//死亡演出用カウントダウン
int DeadCountdown;
//開始演出用カウントダウン
int StartCountdown = 4;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)		
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	ChangeWindowMode(TRUE);
	SetGraphMode(900, 1080, 16);

	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う
	isGamestatus = STATE_INITIALIZATION;
	isDeadflg = false;
	isTimelimitflg = false;
	// 生成
	Camera* camera = new Camera();
	Player* player = new Player();
	Map*	map	   = new Map();
	Stairs* stairs = new Stairs();
	Ui* ui = new Ui();
	Sound* sound = new Sound();
	//階数描画用の変数
	int Displayfloor = 0;
	// エスケープキーが押されるかウインドウが閉じられるまでループ
	LONGLONG frameTime = 0;
	bootflg = true;
	bool    moveTriggered = false; // 移動がトリガーされたかどうかを保持
	bool	pushStart = false;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (isGamestatus == STATE_TITLE)
		{
			// 裏画面の内容を表画面に反映させる
			/*ScreenFlip();*/
			frameTime = GetNowHiPerformanceCount();
			//// プレイヤー制御.
			//player->Update(Displayfloor);

			// TODO: 定数なのでいい感じの位置に移動したい
			// マップチップのサイズ

			/*map->Update();*/
			camera->Update(*player);

			// 画面を初期化する
			ClearDrawScreen();
			stairs->DrawTitle();
			player->DrawTitle();
			ui->DrawTitle();
			// 裏画面の内容を表画面に反映させる
			ScreenFlip();
			// 雑に60fps固定
			while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
			if ((CheckHitKey(KEY_INPUT_RETURN)) && !moveTriggered)
			{
				isGamestatus = STATE_TUTORIAL;
				player->Load(staminaCountdown);
				moveTriggered = true;
				sound->StartSound();
				pushStart = false;
			}
			if (!(CheckHitKey(KEY_INPUT_RETURN)) && !(CheckHitKey(KEY_INPUT_LCONTROL)))
			{
				moveTriggered = false; // キーが離されたらフラグをリセット
			}
		}
		else if (isGamestatus == STATE_INITIALIZATION)
		{
			//階数描画用の変数
			Displayfloor = 0;
			DeadCountdown = 4;
			StartCountdown = 4;
			/*map->Load();*/
			camera->Load();
			player->Load(staminaCountdown);
			stairs->Load();
			ui->Load();
			if (bootflg == true)
			{
				bootflg = false;
				isGamestatus = STATE_TITLE;
			}
			else
			{
				isGamestatus = STATE_GAME;
			}
		}
		else if (isGamestatus == STATE_TUTORIAL)
		{
			// 裏画面の内容を表画面に反映させる
			/*ScreenFlip();*/
			frameTime = GetNowHiPerformanceCount();

			// TODO: 定数なのでいい感じの位置に移動したい
			// マップチップのサイズ

			camera->Update(*player);
			player->tutorial();
			// 画面を初期化する
			ClearDrawScreen();

			// 描画
			/*map->Draw();    *///map非表示now
			player->Draw();
			stairs->DrawStairs();
			// デバッグ描画
			/*ui->underLine();*/
			//階数表示
			ui->DrawHighScore();
			ui->isDrawStamina(staminaCountdown);
			if (pushStart == false)
			{
				ui->tutorial();
			}
			else
			{
				//１秒(1000ミリ秒以上)経過したか？
				mNowTime = GetNowCount();
				if (mNowTime - mTime > 1000)
				{
					//タイマーを三秒減らす
					StartCountdown -= 1;


					//カウントダウン0以下になったら0に戻す。
					if (StartCountdown < 0)
					{
						StartCountdown = 0;
					}

					//計測基準を現在にセット
					mTime = mNowTime;
				}

				//1秒以下～小数点第二位までの秒数を算出
				mMiliSec = (mNowTime - mTime) / 10;
				// 例：透明度50%の白色の四角形を描画する  
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
				DrawBox(0, 0, 900, 1800, GetColor(0, 0, 0), TRUE);
				// 描画モードを元に戻す
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				SetFontSize(150);
				DrawFormatString(385, 430, GetColor(255, 246, 233), "%d",StartCountdown);

				if (StartCountdown == 0)
				{
					isGamestatus = STATE_GAME;
					player->Load(staminaCountdown);
					moveTriggered = true;
				}
			}
			// 裏画面の内容を表画面に反映させる
			ScreenFlip();
			// 雑に60fps固定
			while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
			if ((CheckHitKey(KEY_INPUT_RETURN)) && !moveTriggered)
			{
				pushStart = true;
			}
			if (!(CheckHitKey(KEY_INPUT_RETURN)) && !(CheckHitKey(KEY_INPUT_LCONTROL)))
			{
				moveTriggered = false; // キーが離されたらフラグをリセット
			}
		}
		else if (isGamestatus == STATE_GAME)
		{
			// 裏画面の内容を表画面に反映させる
			/*ScreenFlip();*/
			frameTime = GetNowHiPerformanceCount();
			// プレイヤー制御.
			player->Update(Displayfloor);

			// TODO: 定数なのでいい感じの位置に移動したい
			// マップチップのサイズ
			map->Update();
			camera->Update(*player);

			// 画面を初期化する
			ClearDrawScreen();

			// 描画
			/*map->Draw();  */  //map非表示now
			player->Draw();
			stairs->DrawStairs();
			// デバッグ描画
			/*ui->underLine();*/
			//階数表示
			ui->isDrawUi(Displayfloor);
			ui->DrawHighScore();
			ui->isDrawStamina(staminaCountdown);
			ui->HiScoreNotification(Displayfloor);
			isTimelimitflg = ui->CountDown();
			// プレイヤーの落下チェック
			isDeadflg = stairs->CheckForFall(*player, Displayfloor);
			if (isDeadflg == true)
			{
				isDeadflg = false;
				ui->SaveHiScore(Displayfloor);
				isGamestatus = STATE_GAMEOVER;
			}
			//　プレイヤーのスタミナチェック
			isDeadflg = player->StaminaManagement(Displayfloor,staminaCountdown,*ui);
			if (isDeadflg == true)
			{
				isDeadflg = false;
				ui->SaveHiScore(Displayfloor);
				isGamestatus = STATE_GAMEOVER;
			}
			// 裏画面の内容を表画面に反映させる
			ScreenFlip();
			// 雑に60fps固定
			while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
		}
		else if (isGamestatus == STATE_GAMEOVER)
		{
			// 裏画面の内容を表画面に反映させる
			/*ScreenFlip();*/
			frameTime = GetNowHiPerformanceCount();
			//// プレイヤー制御.
			//player->Update(Displayfloor);

			// TODO: 定数なのでいい感じの位置に移動したい
			// マップチップのサイズ
			player->UpdateMiss(DeadCountdown);
			map->Update();
			/*camera->Update(*player);*/

			// 画面を初期化する
			ClearDrawScreen();

			// 描画
			/*map->Draw();*/    //map非表示now
			player->Draw();
			stairs->DrawStairs();
			// デバッグ描画
			/*ui->underLine();*/
			//階数表示
			ui->isDrawUi(Displayfloor);
			ui->DrawHighScore();
			ui->isDrawStamina(staminaCountdown);
			isTimelimitflg = ui->CountDown();
			// 裏画面の内容を表画面に反映させる
			ScreenFlip();
			// 雑に60fps固定
			while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
			//１秒(1000ミリ秒以上)経過したか？
			mNowTime = GetNowCount();
			if (mNowTime - mTime > 1000)
			{

				
						//タイマーを三秒減らす
						DeadCountdown -= 1;
					

				//カウントダウン0以下になったら0に戻す。
				if (DeadCountdown < 0)
				{
					DeadCountdown =0;
				}

				//計測基準を現在にセット
				mTime = mNowTime;
			}

			//1秒以下～小数点第二位までの秒数を算出
			mMiliSec = (mNowTime - mTime) / 10;

			if (DeadCountdown == 0)
			{
				if (isTimelimitflg == true)
				{
					isGamestatus = STATE_RESULT;
					sound->ResultSound();
				}
				else
				{
					sound->ResultSound();
					isGamestatus = STATE_RESULT;
				}
			}
		}
		else if (STATE_RESULT)
		{
			// 裏画面の内容を表画面に反映させる
			/*ScreenFlip();*/
			frameTime = GetNowHiPerformanceCount();

			// TODO: 定数なのでいい感じの位置に移動したい
			// マップチップのサイズ

			camera->Update(*player);
			player->tutorial();
			// 画面を初期化する
			ClearDrawScreen();

			// 描画
			/*map->Draw(); */   //map非表示now
			player->Draw();
			stairs->DrawStairs();
			// デバッグ描画
			/*ui->underLine();*/
			//階数表示
			ui->isDrawUi(Displayfloor);
			ui->DrawHighScore();
			ui->ResultUi();
			// 裏画面の内容を表画面に反映させる
			ScreenFlip();
			// 雑に60fps固定
			while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
			if ((CheckHitKey(KEY_INPUT_RETURN)) && !moveTriggered)
			{
				isGamestatus = STATE_INITIALIZATION;
				player->Load(staminaCountdown);
				moveTriggered = true;
				bootflg = true;
			}
			if (!(CheckHitKey(KEY_INPUT_RETURN)) && !(CheckHitKey(KEY_INPUT_LCONTROL)))
			{
				moveTriggered = false; // キーが離されたらフラグをリセット
			}

		}
	}

	// 後始末
	delete(player);
	delete(camera);
	delete(map);
	delete(stairs);
	delete(ui);
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}

////音楽つける
///nyankocliimb
//スカイドーム試してみる