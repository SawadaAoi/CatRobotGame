/* ========================================
	DX22Base/
	------------------------------------
	�I�u�W�F�N�g��ޓo�^�pcpp
	------------------------------------
	UITypeRegistry.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "UITypeRegistry.h"

// �I�u�W�F�N�g
#include "UIObjectBase.h"
#include "UIObjectText.h"

/* ========================================
	�C���X�^���X�擾�֐�
	-------------------------------------
	���e�F�C���X�^���X���擾����
	-------------------------------------
	�ߒl�F�C���X�^���X
=========================================== */
UITypeRegistry& UITypeRegistry::GetInstance()
{
	static UITypeRegistry instance;
	return instance;
}

/* ========================================
	�I�u�W�F�N�g�N���X�o�^�֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g�N���X���}�b�v�ɓo�^����
	-------------------------------------
	����1�F�I�u�W�F�N�g�N���X��
	����2�F�I�u�W�F�N�g�����֐�
=========================================== */
void UITypeRegistry::Register(const std::string& sClassName, CreateFunction* func)
{
	m_UITypeMap[sClassName] = func;
}

/* ========================================
	�I�u�W�F�N�g�����֐�
	-------------------------------------
	���e�F�N���X�������񂩂�I�u�W�F�N�g�𐶐�����
	-------------------------------------
	�����F�I�u�W�F�N�g�N���X��
	-------------------------------------
	�ߒl�F�I�u�W�F�N�g
=========================================== */
UIObjectBase* UITypeRegistry::CreateUI(const std::string& sClassName)
{
	// �N���X�����o�^����Ă��邩�m�F
	if (m_UITypeMap.find(sClassName) != m_UITypeMap.end())
	{
		return m_UITypeMap.at(sClassName)();
	}
	return nullptr;
}

/* ========================================
	�S�I�u�W�F�N�g�o�^�֐�
	-------------------------------------
	���e�F�S�ẴI�u�W�F�N�g��o�^����
=========================================== */
void UITypeRegistry::RegisterAllUITypes()
{
	REGISTER_UI_TYPE(UIObjectBase);
	REGISTER_UI_TYPE(UIObjectText);

}
