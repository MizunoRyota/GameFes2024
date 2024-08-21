#include"skydome.h"

#include<DxLib.h>

Skydome::Skydome()
{
    // �R�c���f���̓ǂݍ���
    SkydomeModel = MV1LoadModel("data/model/Skydome/Sunny/Dome_X501.pmx");
    pos = VGet(0, 0, -50);
}

Skydome::~Skydome()
{
}

void Skydome::SkydomeUpdate()
{
    
    // �L�[���͎擾
    Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    if (Key & PAD_INPUT_RIGHT)
    {
        pos.y -= 0.001;
    }
    else if (Key & PAD_INPUT_LEFT)
    {
        pos.y += 0.001;

    }

    MV1SetRotationXYZ(SkydomeModel, VGet(0.0f, pos.y, 0.0f));

    MV1SetPosition(SkydomeModel, pos);
}

void Skydome::SkydomeTitle()
{
    pos.y -= 0.001;
    MV1SetRotationXYZ(SkydomeModel, VGet(0.0f, pos.y,0.0f));
}

void Skydome::SkydomeDraw()
{
    // �R�c���f���̕`��
    MV1DrawModel(SkydomeModel);
}