/* ========================================
	DX22Base/
	------------------------------------
	ファイル処理管理用ヘッダ
	------------------------------------
	説明：ファイルの読み書き処理を行うクラス
	------------------------------------
	FileManager.h
========================================== */
#pragma once

// =============== インクルード ===================
#include <string>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"

// =============== 定数定義 =======================
const int MAX_TEXT_SIZE = 256;


// =============== クラス定義 ===================
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

