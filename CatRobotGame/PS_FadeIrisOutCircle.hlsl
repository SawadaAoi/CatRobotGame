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
    float2 center; // アイリスの中心座標 (0.5, 0.5) が基本
    float radius; // 現在の円の半径（時間経過で縮小）
}

float4 main(PS_IN pin) : SV_TARGET
{
    float aspectRatio = 1280.0 / 720.0; // 画面のアスペクト比（横長）
    
    // アスペクト比を補正したUV座標を作成
    float2 correctedUV = float2((pin.uv.x - center.x) * aspectRatio, pin.uv.y - center.y);


    // 距離を計算（補正後のUVを使う）
    float dist = length(correctedUV);
    
    // 距離が現在の半径より外なら黒、それ以外は通常描画
    if (dist > radius)
    {
        return float4(0, 0, 0, 1); // 黒でフェードアウト
    }
    else
    {
        return float4(0, 0, 0, 0); // 黒でフェードアウト
    }
}
