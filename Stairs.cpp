#include"Stairs.h"
#include "Player.h"

Stairs::Stairs()
{
    StairsGraph = LoadGraph("UI/Greenscaffold.png");
}

Stairs::~Stairs()
{
    //処理なし
}


void Stairs::Load()
{
    // 最下段の階段の座標を設定（プレイヤーの足元を中心とする）
    VECTOR playerFootPos = VGet(0, 0, 0);
    titleVertexLeft = VGet(-3, -1.5, 0);//左
    titleVertexRight = VGet(3, -1.5, 0);//右
    vertex[0][0] = VAdd(playerFootPos, VGet(-1.0f, 0.0f, 0.0f)); // 左
    vertex[0][1] = VAdd(playerFootPos, VGet(1.0f, 0.0f, 0.0f));  // 右
    for (int i = 1; i < isNumberofStages; ++i)
    {
        isStairsRandPattern = GetRand(1);
        if (isStairsRandPattern == 0)//右に階段が出るパターン
        {
            vertex[i][0] = VAdd(vertex[i - 1][1], VGet(2.0f, 2.0f, 0.0f));  // 左
            vertex[i][1] = VAdd(vertex[i - 1][0], VGet(2.0f, 2.0f, 0.0f));  // 右
        }
        else//左に階段が出るパターン
        {
            vertex[i][0] = VAdd(vertex[i - 1][1], VGet(-2.0f, 2.0f, 0.0f));  // 左
            vertex[i][1] = VAdd(vertex[i - 1][0], VGet(-2.0f, 2.0f, 0.0f));  // 右
        }
    }
}


void Stairs::DrawStairs()
{
    // 階段の描画
    for (int i = 0; i < isNumberofStages; ++i)
    {
        // 階段の左端と右端の座標を取得
        VECTOR leftVertex = vertex[i][0];
        VECTOR rightVertex = vertex[i][1];

        // 左端と右端の中間点を計算
        VECTOR middleVertex = VAdd(leftVertex, VScale(VSub(rightVertex, leftVertex), 0.5f));

        // 階段の線を描画
       /* DrawLine3D(leftVertex, rightVertex, GetColor(0, 0, 255));*/

        // 中間点に画像を描画
        DrawBillboard3D(middleVertex, 0.5f, 0.5f, 2, 0, StairsGraph, TRUE);
    }
}

// プレイヤーの落下チェック
bool Stairs::CheckForFall(const Player& player, int& Displayfloor)
{
    bool isDeadjudgeflg = false;
    // 現在のフロアの階段の座標を取得
    VECTOR leftVertex = vertex[Displayfloor][0];
    VECTOR rightVertex = vertex[Displayfloor][1];

    // 最小値と最大値を手動で計算
    float minX = (leftVertex.x < rightVertex.x) ? leftVertex.x : rightVertex.x;
    float maxX = (leftVertex.x > rightVertex.x) ? leftVertex.x : rightVertex.x;
    float minY = (leftVertex.y < rightVertex.y) ? leftVertex.y : rightVertex.y;
    float maxY = (leftVertex.y > rightVertex.y) ? leftVertex.y : rightVertex.y;

    // プレイヤーが階段の範囲内にいるかチェック
    if (player.GetPos().x < minX || player.GetPos().x > maxX || player.GetPos().y < minY || player.GetPos().y > maxY)
    {
        /*SetFontSize(70);
        DrawFormatString(930, 800, GetColor(255, 0, 0), "落下中");*/ //デバッグ用
        isDeadjudgeflg = true;
    }
   
    return isDeadjudgeflg;
}

void Stairs::DrawTitle()
{
    // 左端と右端の中間点を計算
    VECTOR titlemiddleVertex = VAdd(titleVertexLeft, VScale(VSub(titleVertexRight, titleVertexLeft), 0.5f));
    // 中間点に画像を描画
    DrawBillboard3D(titlemiddleVertex, 0.5f, 0.5f, 6, 0, StairsGraph, TRUE);
}