/* ========================================
	CatRobotGame/
	------------------------------------
	UI�^�C�v�o�^�pcpp
	------------------------------------
	RegisterUITypeMap.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "UITypeRegistry.h"

// UI
#include "UIObjectBase.h"
#include "UIObjectText.h"
#include "UIObjectPlayerHP.h"

/* ========================================
	�SUI�o�^�֐�
	-------------------------------------
	���e�F�S�Ă�UI��o�^����
=========================================== */
void UITypeRegistry::RegisterAllUITypes()
{
	REGISTER_UI_TYPE(UIObjectBase);
	REGISTER_UI_TYPE(UIObjectText);
	REGISTER_UI_TYPE(UIObjectPlayerHP);

}