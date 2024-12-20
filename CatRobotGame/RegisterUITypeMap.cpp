/* ========================================
	CatRobotGame/
	------------------------------------
	UIタイプ登録用cpp
	------------------------------------
	RegisterUITypeMap.cpp
========================================== */

// =============== インクルード ===================
#include "UITypeRegistry.h"

// UI
#include "UIObjectBase.h"
#include "UIObjectText.h"
#include "UIObjectPlayerHP.h"

/* ========================================
	全UI登録関数
	-------------------------------------
	内容：全てのUIを登録する
=========================================== */
void UITypeRegistry::RegisterAllUITypes()
{
	REGISTER_UI_TYPE(UIObjectBase);
	REGISTER_UI_TYPE(UIObjectText);
	REGISTER_UI_TYPE(UIObjectPlayerHP);

}