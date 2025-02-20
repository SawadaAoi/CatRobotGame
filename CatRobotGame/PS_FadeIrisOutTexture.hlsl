/* ========================================
	DX22Base/
	------------------------------------
	UI画像用ピクセルシェーダー
	------------------------------------
	説明：UIの画像を描画するためのピクセルシェーダー
	------------------------------------
	PS_Sprite.hlsl
========================================== */

// ピクセル入力構造体
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
    float2 center;  // 縮小の基準となる中心 (通常は0.5, 0.5)
    float scale;    // 縮小率 (1.0 で等倍, 0.5 で50%縮小)
}

float4 main(PS_IN pin) : SV_TARGET
{	
	// UV座標を中心基準に変換
    float2 newUV = (pin.uv - center) * scale + center;
    
    // テクスチャの外に出る場合は透明にする
    if (newUV.x < 0 || newUV.x > 1 || newUV.y < 0 || newUV.y > 1)
    {
        return float4(0, 0, 0, 1); // 完全な透明
    }
    
    // テクスチャをサンプリング
    return float4(pin.color.x, pin.color.y, pin.color.z, 1.0f - tex.Sample(samp, newUV).w);
}