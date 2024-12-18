/* ========================================
	DX22/Dropin
	------------------------------------
	�����`��p�w�b�_
	------------------------------------
	����:��������ʂɕ`�悷�邽�߂̃N���X
	------------------------------------
	TextWrite.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include <memory>
#include "DirectWriteCustomFont.h"
#include <string>
#include "Vector2.h"
#include "WindowAPI.h"
#include "SettingWindowAPI.h"

// =============== �萔��` =======================
#define TEXT_WRITE TextWrite::GetInstance() 

namespace SCREEN_POS	// �ʒu
{
	const float RIGHT	=  WindowConfig::SCREEN_WIDTH  / 2;	// �E
	const float LEFT	= -WindowConfig::SCREEN_WIDTH  / 2;	// ��
	const float TOP		=  WindowConfig::SCREEN_HEIGHT / 2;	// ��
	const float BOTTOM	= -WindowConfig::SCREEN_HEIGHT / 2;	// ��

	// ��ʈʒu(XY���W)
	const Vector2<float> LEFT_TOP		= { LEFT ,	TOP };		// ��ʍ���
	const Vector2<float> RIGHT_TOP		= { RIGHT , TOP };		// ��ʉE��
	const Vector2<float> LEFT_BOTTOM	= { LEFT ,	BOTTOM };	// ��ʍ���
	const Vector2<float> RIGHT_BOTTOM	= { RIGHT , BOTTOM };	// ��ʉE��
	const Vector2<float> CENTER			= { 0.0f, 0.0f };		// ��ʒ���
}

// =============== �񋓑̒�` =====================
enum E_Pivot
{
	LEFT_TOP,
	LEFT_BOTTOM,
	RIGHT_TOP,
	RIGHT_BOTTOM,
	CENTER,
	LEFT_CENTER,
	RIGHT_CENTER,
};

// =============== �N���X��` =====================
class TextWrite
{
public:
	static TextWrite& GetInstance();
    void DrawWriteText(const std::string text = "���͖���", 
		Vector2<float> pos = {0.0f,0.0f}, E_Pivot pivot = E_Pivot::LEFT_TOP, bool bScreenOutCheck = true);

	void SetFontType(FontType type);
	void SetFontColor(D2D1::ColorF color);
	void SetFontWeight(DWRITE_FONT_WEIGHT weight);
	void SetFontSize(float size);
	
private:
    TextWrite();
    TextWrite(const TextWrite&) = delete;

	void operator=(const TextWrite&) = delete;

	Vector2<float> AdjustPosOriginCenter(Vector2<float> pos);
	Vector2<float> ScreenOutCheck(Vector2<float> pos, std::string text);
	Vector2<float> AdjustPivot(Vector2<float> pos, E_Pivot pivot, std::string text);

	float GetTextWidth(std::string text);

    static inline std::unique_ptr<DirectWriteCustomFont> m_pWriteObj;
	static inline FontData m_pFontData;
};
