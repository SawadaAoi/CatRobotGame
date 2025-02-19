/* ========================================
	DX22Base/
	------------------------------------
	�t�@�C�������Ǘ��p�w�b�_
	------------------------------------
	�����F�t�@�C���̓ǂݏ����������s���N���X
	------------------------------------
	FileManager.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include <string>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"

// =============== �萔��` =======================
const int MAX_TEXT_SIZE = 256;


// =============== �N���X��` ===================
class FileManager
{
public:

	struct S_SaveDataObject
	{
		char			cClassType[MAX_TEXT_SIZE];
		Vector3<float>	vPos;
		Quaternion		qRot;
		Vector3<float>	vScale;
		char			cObjectName[MAX_TEXT_SIZE];
		char			cParentName[MAX_TEXT_SIZE];
	};

	struct S_SaveDataUI
	{
		char			cClassType[MAX_TEXT_SIZE];
		Vector2<float>	vPos;
		float			fRot;
		Vector2<float>	vScale;
		int				nTextureID;
		bool			bIsVisible;
		int				nDrawPriority;
		char			cUIName[MAX_TEXT_SIZE];
		char			cParentName[MAX_TEXT_SIZE];
	};

public:
	FileManager() {};
	~FileManager() {};

	static void StageObjectOutput(std::string sPath);
	static void StageObjectInput(std::string sPath);

	static void UIOutput(std::string sPath);
	static void UIInput(std::string sPath);
};

