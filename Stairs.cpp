#include"Stairs.h"
#include "Player.h"

Stairs::Stairs()
{
    StairsGraph = LoadGraph("UI/Greenscaffold.png");
}

Stairs::~Stairs()
{
    //�����Ȃ�
}


void Stairs::Load()
{
    // �ŉ��i�̊K�i�̍��W��ݒ�i�v���C���[�̑����𒆐S�Ƃ���j
    VECTOR playerFootPos = VGet(0, 0, 0);
    titleVertexLeft = VGet(-3, -1.5, 0);//��
    titleVertexRight = VGet(3, -1.5, 0);//�E
    vertex[0][0] = VAdd(playerFootPos, VGet(-1.0f, 0.0f, 0.0f)); // ��
    vertex[0][1] = VAdd(playerFootPos, VGet(1.0f, 0.0f, 0.0f));  // �E
    for (int i = 1; i < isNumberofStages; ++i)
    {
        isStairsRandPattern = GetRand(1);
        if (isStairsRandPattern == 0)//�E�ɊK�i���o��p�^�[��
        {
            vertex[i][0] = VAdd(vertex[i - 1][1], VGet(2.0f, 2.0f, 0.0f));  // ��
            vertex[i][1] = VAdd(vertex[i - 1][0], VGet(2.0f, 2.0f, 0.0f));  // �E
        }
        else//���ɊK�i���o��p�^�[��
        {
            vertex[i][0] = VAdd(vertex[i - 1][1], VGet(-2.0f, 2.0f, 0.0f));  // ��
            vertex[i][1] = VAdd(vertex[i - 1][0], VGet(-2.0f, 2.0f, 0.0f));  // �E
        }
    }
}


void Stairs::DrawStairs()
{
    // �K�i�̕`��
    for (int i = 0; i < isNumberofStages; ++i)
    {
        // �K�i�̍��[�ƉE�[�̍��W���擾
        VECTOR leftVertex = vertex[i][0];
        VECTOR rightVertex = vertex[i][1];

        // ���[�ƉE�[�̒��ԓ_���v�Z
        VECTOR middleVertex = VAdd(leftVertex, VScale(VSub(rightVertex, leftVertex), 0.5f));

        // �K�i�̐���`��
       /* DrawLine3D(leftVertex, rightVertex, GetColor(0, 0, 255));*/

        // ���ԓ_�ɉ摜��`��
        DrawBillboard3D(middleVertex, 0.5f, 0.5f, 2, 0, StairsGraph, TRUE);
    }
}

// �v���C���[�̗����`�F�b�N
bool Stairs::CheckForFall(const Player& player, int& Displayfloor)
{
    bool isDeadjudgeflg = false;
    // ���݂̃t���A�̊K�i�̍��W���擾
    VECTOR leftVertex = vertex[Displayfloor][0];
    VECTOR rightVertex = vertex[Displayfloor][1];

    // �ŏ��l�ƍő�l���蓮�Ōv�Z
    float minX = (leftVertex.x < rightVertex.x) ? leftVertex.x : rightVertex.x;
    float maxX = (leftVertex.x > rightVertex.x) ? leftVertex.x : rightVertex.x;
    float minY = (leftVertex.y < rightVertex.y) ? leftVertex.y : rightVertex.y;
    float maxY = (leftVertex.y > rightVertex.y) ? leftVertex.y : rightVertex.y;

    // �v���C���[���K�i�͈͓̔��ɂ��邩�`�F�b�N
    if (player.GetPos().x < minX || player.GetPos().x > maxX || player.GetPos().y < minY || player.GetPos().y > maxY)
    {
        /*SetFontSize(70);
        DrawFormatString(930, 800, GetColor(255, 0, 0), "������");*/ //�f�o�b�O�p
        isDeadjudgeflg = true;
    }
   
    return isDeadjudgeflg;
}

void Stairs::DrawTitle()
{
    // ���[�ƉE�[�̒��ԓ_���v�Z
    VECTOR titlemiddleVertex = VAdd(titleVertexLeft, VScale(VSub(titleVertexRight, titleVertexLeft), 0.5f));
    // ���ԓ_�ɉ摜��`��
    DrawBillboard3D(titlemiddleVertex, 0.5f, 0.5f, 6, 0, StairsGraph, TRUE);
}