#pragma once
#include "CComponent.h"
class CCastle :
	public CComponent
{
	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Awake()								override;
	virtual void Start()								override;
	virtual void Update()								override;
	virtual void LateUpdate()							override;
	virtual void OnDestroy()							override;
	virtual void OnRender()								override;
	virtual void OnEnable()								override;
	virtual void OnDisable()							override;
	virtual void OnCollisionEnter(CObject * _pObject)	override;
	virtual void OnCollisionStay(CObject * _pObject)	override;
	virtual void OnCollisionExit(CObject * _pObject)	override;
public:
	float m_fCurHp = 1000;
	float m_fMaxHp = 1000;

	CObject * m_pCastleUI = nullptr;
	CObject * m_pCastleHPFull = nullptr;
	CObject * m_pCastleHPEdge = nullptr;

	CCastle();
	~CCastle();
};

