/* ========================================
	DX22Base/
	------------------------------------
	UI�摜�p�s�N�Z���V�F�[�_�[
	------------------------------------
	�����FUI�̉摜��`�悷�邽�߂̃s�N�Z���V�F�[�_�[
	------------------------------------
	PS_Sprite.hlsl
========================================== */

// �s�N�Z�����͍\����
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

cbuffer IrisOutData : register(b0)
{
    float2 center; // �A�C���X�̒��S���W (0.5, 0.5) ����{
    float radius; // ���݂̉~�̔��a�i���Ԍo�߂ŏk���j
}

float4 main(PS_IN pin) : SV_TARGET
{
    float aspectRatio = 1280.0 / 720.0; // ��ʂ̃A�X�y�N�g��i�����j
    
    // �A�X�y�N�g���␳����UV���W���쐬
    float2 correctedUV = float2((pin.uv.x - center.x) * aspectRatio, pin.uv.y - center.y);


    // �������v�Z�i�␳���UV���g���j
    float dist = length(correctedUV);
    
    // ���������݂̔��a���O�Ȃ獕�A����ȊO�͒ʏ�`��
    if (dist > radius)
    {
        return float4(0, 0, 0, 1); // ���Ńt�F�[�h�A�E�g
    }
    else
    {
        return float4(0, 0, 0, 0); // ���Ńt�F�[�h�A�E�g
    }
}
