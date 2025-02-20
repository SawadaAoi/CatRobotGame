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
    float2 center;  // �k���̊�ƂȂ钆�S (�ʏ��0.5, 0.5)
    float scale;    // �k���� (1.0 �œ��{, 0.5 ��50%�k��)
}

float4 main(PS_IN pin) : SV_TARGET
{	
	// UV���W�𒆐S��ɕϊ�
    float2 newUV = (pin.uv - center) * scale + center;
    
    // �e�N�X�`���̊O�ɏo��ꍇ�͓����ɂ���
    if (newUV.x < 0 || newUV.x > 1 || newUV.y < 0 || newUV.y > 1)
    {
        return float4(0, 0, 0, 1); // ���S�ȓ���
    }
    
    // �e�N�X�`�����T���v�����O
    return float4(pin.color.x, pin.color.y, pin.color.z, 1.0f - tex.Sample(samp, newUV).w);
}