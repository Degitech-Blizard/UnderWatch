#pragma once
#include "CObject.h"

class CTransform;
class CObject;
class CComponent abstract
{
	friend class CObject;
	friend class CObjectManager;

public:
	CComponent();
	virtual ~CComponent();

private:
	virtual void Awake()								PURE;
	virtual void Start()								PURE;
	virtual void Update()								PURE;
	virtual void LateUpdate()							PURE;
	virtual void OnRender()								PURE;
	virtual void OnDestroy()							PURE;
	virtual void OnEnable()								PURE;
	virtual void OnDisable()							PURE;
	virtual void OnCollisionEnter(CObject * _pObject)	PURE;
	virtual void OnCollisionStay(CObject * _pObject)	PURE;
	virtual void OnCollisionExit(CObject * _pObject)	PURE;



private:
	bool m_bIsEnable;
	bool m_bStart = FALSE;
public:
	bool GetIsEnable()
	{
		return m_bIsEnable;
	}
	void SetIsEnable(bool _bIsEnable)
	{
		if (m_bIsEnable == true && _bIsEnable == false) OnDisable();
		else if (m_bIsEnable == false && _bIsEnable == true) OnEnable();
		m_bIsEnable = _bIsEnable;
	}
	//list<CComponent *>& GetComponents() 
	//{ 
	//	return this->m_pObject->GetComponents(); 
	//}

	template <typename T>
	T*  GetComponent()
	{
		return this->m_pObject->GetComponent<T>();
	}

	template <typename T>
	T* AddComponent()
	{
		return this->m_pObject->AddComponent<T>();
	}

	template <typename T>
	T* GetComponentInParent()
	{
		return m_pObject->GetComponentInParent<T>();
	}

	template <typename T>
	T* GetComponentInChild()
	{
		return m_pObject->GetComponentInChild<T>();
	}

	template <typename T>
	list<T*> GetComponentsInChild()
	{
		return m_pObject->GetComponentsInChild();
	}
public:
	CObject * m_pObject;
	CTransform * Transform = NULL;

};

