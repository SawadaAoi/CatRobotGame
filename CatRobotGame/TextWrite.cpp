/* ========================================
	DX22/Dropin
	------------------------------------
	�����`��pcpp
	------------------------------------
	TextWrite.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "TextWrite.h"
#include "DirectXManager.h"
#include <DirectXMath.h>
#include "WindowAPI.h"

// =============== �萔 ===================
const float					DEFAULT_FONT_SIZE	= 50.0f;										// �f�t�H���g�t�H���g�T�C�Y
const FontType				DEFAULT_FONT		= FontType::IPAexMin;						// �f�t�H���g�t�H���g
const D2D1::ColorF			DEFAULT_COLOR		= D2D1::ColorF(D2D1::ColorF::Black);			// �f�t�H���g�J���[
const DWRITE_FONT_WEIGHT	DEFAULT_FONT_WEIGHT = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN;	// �f�t�H���g�t�H���g�̑���

const float OUT_SCREEN_ADJUST = 0.2f;			// ��ʊO�ɏo�����̒����l

const float DOUBLE_BYTE_TEXT_MULTIPLE = 1.0f;	// �S�p�����̉����{��
const float SINGLE_BYTE_TEXT_MULTIPLE = 0.5f;	// ���p�����̉����{��
const float TEXT_HEIGHT_MULTIPLE = 1.3f;		// �����̍����{��


/* ========================================
	�C���X�^���X(�V���O���g��)�擾�֐�
	-------------------------------------
	���e�FCTextWrite�N���X�̃C���X�^���X���擾
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�FCTextWrite�N���X�̃C���X�^���X
=========================================== */
TextWrite& TextWrite::GetInstance()
{
	static TextWrite instance;
	return instance;
}

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F����
=========================================== */
TextWrite::TextWrite()
{
	// DirectWrite�p�R���|�[�l���g�쐬
	m_pWriteObj = std::make_unique<DirectWriteCustomFont>(&m_pFontData);

	// ������
	m_pWriteObj->Init(DirectXManager::GetSwapChain());

	// �t�H���g�f�[�^������
	m_pFontData.fontSize		= DEFAULT_FONT_SIZE;							// �t�H���g�T�C�Y
	m_pFontData.fontWeight		= DEFAULT_FONT_WEIGHT;							// �t�H���g�̑���		
	m_pFontData.Color			= D2D1::ColorF(DEFAULT_COLOR);					// �t�H���g�̐F
	m_pFontData.font			= m_pWriteObj->GetFontName(DEFAULT_FONT);		// �t�H���g��
	m_pFontData.shadowColor		= D2D1::ColorF(D2D1::ColorF::White);			// �e�̐F	
	m_pFontData.shadowOffset	= D2D1::Point2F(5.0f, -5.0f);					// �e�̃I�t�Z�b�g	

	// �t�H���g���Z�b�g
	m_pWriteObj->SetFont(m_pFontData);
}

/* ========================================
	�����`��֐�
	-------------------------------------
	���e�F������`�悷��
	-------------------------------------
	����1�F�`�悷�镶����
	����2�F�`��ʒu
	����3�F���S�ʒu
	����4�F��ʊO�`�F�b�N
=========================================== */
void TextWrite::DrawWriteText(const std::string text, Vector2<float> pos, E_Pivot pivot, bool bScreenOutCheck)
{
	Vector2<float> fAdjustPos;
	fAdjustPos = AdjustPivot(pos, pivot, text);	// �s�{�b�g����

	// ��ʊO����
	if(bScreenOutCheck)	fAdjustPos = ScreenOutCheck(fAdjustPos, text);		

	fAdjustPos = AdjustPosOriginCenter(fAdjustPos);		// ���_����ʒ����ɒ���

	m_pWriteObj->DrawString(text, fAdjustPos, D2D1_DRAW_TEXT_OPTIONS_NONE);
}


/* ========================================
	���_���������֐�
	-------------------------------------
	���e�F���_����ʒ����ɒ���
	-------------------------------------
	����1�F�ʒu
	-------------------------------------
	�ߒl�F������̈ʒu
=========================================== */
Vector2<float> TextWrite::AdjustPosOriginCenter(Vector2<float> pos)
{
	Vector2<float> rePos = {	// ���_����ʒ����ɂȂ�悤�ɒ���
		pos.x + (WINDOW_INST.GetScreenSize().nWidth / 2),
		-pos.y + (WINDOW_INST.GetScreenSize().nHeight / 2)
	};
	return rePos;
}

/* ========================================
	�X�N���[���A�E�g�`�F�b�N�֐�
	-------------------------------------
	���e�F��ʊO�ɏo�����`�F�b�N
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
Vector2<float> TextWrite::ScreenOutCheck(Vector2<float> pos, std::string text)
{
	// �e�L�X�g�̏I�_�ʒu
	Vector2<float> textEndPos = {
		pos.x + GetTextWidth(text),
		pos.y - m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE	// �����̒�ӂ̍��W
	};

	// ��ʊO�ɏo���璲��
	// �E�[
	if (textEndPos.x > SCREEN_POS::RIGHT)
	{
		pos.x -= textEndPos.x - SCREEN_POS::RIGHT;			// �E�ɂ͂ݏo�����A���ɖ߂�
	}
	// ���
	if (textEndPos.y < SCREEN_POS::BOTTOM)
	{
		pos.y += -(WINDOW_INST.GetScreenSize().nHeight / 2) - textEndPos.y;
	}

	return pos;
}


/* ========================================
	�s�{�b�g�����֐�
	-------------------------------------
	���e�F�s�{�b�g�𒲐�
	-------------------------------------
	����1�F�ʒu
	����2�F�s�{�b�g
	����3�F������
	-------------------------------------
	�ߒl�F������̈ʒu
=========================================== */
Vector2<float> TextWrite::AdjustPivot(Vector2<float> pos, E_Pivot pivot, std::string text)
{
	Vector2<float> fAdjustPos = pos;	// ������̈ʒu

	switch (pivot)
	{
	case LEFT_TOP:
		// ������Ԃ�����Ȃ̂Œ����Ȃ�
		break;
	case LEFT_BOTTOM:
		fAdjustPos.y += m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE;	// ���S�ʒuY���W�𕶎��̒�ӂɂ���ׂɕ����̍��W����ɂ��炷
		break;
	case RIGHT_TOP:
		fAdjustPos.x -= GetTextWidth(text);	// ���S�ʒuX���W�𕶎��̉E�[�ɂ���ׂɕ����̍��W����(������)�ɂ��炷
		break;
	case RIGHT_BOTTOM:
		fAdjustPos.x -= GetTextWidth(text);		
		fAdjustPos.y += m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE;	
		break;
	case CENTER:
		fAdjustPos.x -= GetTextWidth(text) / 2;								// �����̉����̔������ɂ��炷
		fAdjustPos.y += (m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE) / 2;	// �����̍����̔�����ɂ��炷
		break;
	case LEFT_CENTER:
		fAdjustPos.y += (m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE) / 2;	// �����̍����̔�����ɂ��炷
		break;
	case RIGHT_CENTER:
		fAdjustPos.x -= GetTextWidth(text);									// �����̉��������ɂ��炷
		fAdjustPos.y += (m_pFontData.fontSize * TEXT_HEIGHT_MULTIPLE) / 2;	// �����̍����̔�����ɂ��炷
		break;
	}

	return fAdjustPos;
}

/* ========================================
	�������擾�֐�
	-------------------------------------
	���e�F�����̉������擾
	-------------------------------------
	����1�F������
	-------------------------------------
	�ߒl�F�����̉���
=========================================== */
float TextWrite::GetTextWidth(std::string text)
{
	float fReWidth = 0.0f;	// �����̉���

	// �S�Ă̕�����
	while (!text.empty())
	{
		if (IsDBCSLeadByte(text[0]) == 0)	// 1�o�C�g����(���p)
		{
			fReWidth += m_pFontData.fontSize * SINGLE_BYTE_TEXT_MULTIPLE;
			text.erase(0, 1);	// 1�����i�߂�
		}
		else // 2�o�C�g����(�S�p)
		{
			fReWidth += m_pFontData.fontSize * DOUBLE_BYTE_TEXT_MULTIPLE;
			text.erase(0, 2);	// 2�����i�߂�
		}
	}

	return fReWidth;
}


/* ========================================
	�t�H���g�ύX�֐�
	-------------------------------------
	���e�F�t�H���g��ύX����
	-------------------------------------
	����1�F�t�H���g�f�[�^
	-------------------------------------
	�ߒl�F����
=========================================== */
void TextWrite::SetFontType(FontType type)
{
	m_pFontData.font = m_pWriteObj->GetFontName(type);
	m_pWriteObj->SetFont(m_pFontData);
}

/* ========================================
	�t�H���g�J���[�ύX�֐�
	-------------------------------------
	���e�F�t�H���g�J���[��ύX����
	-------------------------------------
	����1�F�J���[
	-------------------------------------
	�ߒl�F����
=========================================== */
void TextWrite::SetFontColor(D2D1::ColorF color)
{
	m_pFontData.Color = color;
	m_pWriteObj->SetFont(m_pFontData);
}

/* ========================================
	�t�H���g�����ύX�֐�
	-------------------------------------
	���e�F�t�H���g�̑�����ύX����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void TextWrite::SetFontWeight(DWRITE_FONT_WEIGHT weight)
{
	m_pFontData.fontWeight = weight;
	m_pWriteObj->SetFont(m_pFontData);
}

/* ========================================
	�t�H���g�T�C�Y�ύX�֐�
	-------------------------------------
	���e�F�t�H���g�T�C�Y��ύX����
	-------------------------------------
	����1�F�T�C�Y
	-------------------------------------
	�ߒl�F����
=========================================== */
void TextWrite::SetFontSize(float size)
{
	m_pFontData.fontSize = size;
	m_pWriteObj->SetFont(m_pFontData);
}
