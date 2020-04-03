#pragma once
#include "CComponent.h"




enum ObjectTag
{
	Start = 0,
	Untagged,
	Cursor,
	Map,
	Player,
	Floor,
	Fall,
	EnemyBullet,
	PlayerBullet,
	Enemy,
	Item,
	UI,
	Collider,
	End
}typedef Tag;


class CObject 
{
	friend class CObjectManager;
public:
	CObject();
	~CObject();

private:



	void Init();
	void Render();
	void Update();
	void Release();

protected:
	list<CComponent *>m_Components;
	
	BOOL m_bDestroy = FALSE; // �ش� ������Ʈ�� �ı�ȣ��Ǿ�����
	ObjectTag m_Tag;
	bool m_bIsStatic = FALSE;
	string m_Name;
	INT m_iDepth;


public:
	CObject * m_pParent = NULL;
	list<CObject * > m_listChild;


public:
	CObject * AddChild(CObject * _pObj)
	{
		m_listChild.push_back(_pObj);
		_pObj->m_pParent = this;
	}
	void DestroyChild(CObject * _pObj)
	{
		m_listChild.remove(_pObj);
		_pObj->m_pParent = nullptr;
	}
	CTransform * Transform = NULL;

	
public:
	void		SetObjectTag(ObjectTag _Tag) { m_Tag = _Tag; }
	ObjectTag	GetObjectTag() { return m_Tag; }
	bool		GetIsStatic() { return m_bIsStatic; }
	void		SetIsStatic(bool _bIsStatic) { m_bIsStatic = _bIsStatic; }
	void		Destroy() {
		for (auto iter : m_listChild) { iter->Destroy(); }m_bDestroy = TRUE;
}
	string GetName()
	{
		return m_Name;
	}

	void SetName(CRString _Name)
	{
		m_Name = _Name;
	}
public:

	list<CComponent *>& GetComponents() { return m_Components; }

	template <typename T>
	T*  GetComponent()
	{
	
		if(TRUE == std::is_base_of<CComponent, T>::value)
		{
			for (auto iter : m_Components)
			{
				T * cp = dynamic_cast<T*>(iter);
				if (cp != nullptr) return cp;
			}
		}
		return nullptr;
	}

	template <typename T>
	T* GetComponentInParent()
	{
		if (m_pParent == NULL) return nullptr;
		if (TRUE == std::is_base_of<CComponent, T>::value)
		{
			for (auto iter : m_pParent->GetComponents())
			{
				T * cp = dynamic_cast<T*>(iter);
				if (cp != nullptr) return cp;
			}
		}
		return nullptr;
	}

	template <typename T>
	T* GetComponentInChild()
	{
		if (m_listChild.empty() == TRUE) return nullptr;
		if (TRUE == std::is_base_of<CComponent, T>::value)
		{
			for (auto iter : m_listChild)
			{
				auto Comp = iter->GetComponent<T>();
				if (Comp == NULL) continue;
				else
				{
					return Comp;
				}
			}
		}
		return nullptr;
	}

	template <typename T>
	list<T*> GetComponentsInChild()
	{
		if (m_listChild.empty() == TRUE) return nullptr;

		list<CComponent *> listComponent;
		if (TRUE == std::is_base_of<CComponent, T>::value)
		{
			for (auto iter : m_listChild)
			{
				auto Comp = iter->GetComponent<T>();
				if (Comp == NULL) continue;
				else
				{
					listComponent.push_back(Comp);
				}
			}
		}
		return listComponent;
	}

	template <typename T>
	T* AddComponent()
	{
		//������Ʈ�� ��ӹ��� �ʾҴٸ� ����
		if (FALSE == std::is_base_of<CComponent, T>::value)
			return nullptr;

		

		//�̹� �������ִ� ������Ʈ�� �� �߰��Ϸ��� ����
		if (nullptr != this->GetComponent<T>())
			return this->GetComponent<T>();

		T * pComponent = new T();

		pComponent->m_pObject = this;
		
		pComponent->Transform = this->Transform;

		pComponent->Awake();

		pComponent->m_bIsEnable = true;

		m_Components.push_back(pComponent);

		return pComponent;
	}
};


