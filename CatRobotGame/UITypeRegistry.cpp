/* ========================================
	DX22Base/
	------------------------------------
	UI��ޓo�^�pcpp
	------------------------------------
	UITypeRegistry.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "UITypeRegistry.h"


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
	UI�N���X�o�^�֐�
	-------------------------------------
	���e�FUI�N���X���}�b�v�ɓo�^����
	-------------------------------------
	����1�FUI�N���X��
	����2�FUI�����֐�
=========================================== */
void UITypeRegistry::Register(const std::string& sClassName, CreateFunction* func)
{
	m_UITypeMap[sClassName] = func;
}

/* ========================================
	UI�����֐�
	-------------------------------------
	���e�F�N���X�������񂩂�UI�𐶐�����
	-------------------------------------
	�����FUI�N���X��
	-------------------------------------
	�ߒl�FUI�|�C���^
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
	�Q�b�^�[(UI�}�b�v)�֐�
	-------------------------------------
	�ߒl�Funordered_map<std::string, CreateFunction*>& UI�}�b�v
=========================================== */
std::unordered_map<std::string, UITypeRegistry::CreateFunction*>& UITypeRegistry::GetUITypeMap()
{
	return m_UITypeMap;
}
