#pragma once
#include "CComponent.h"
class CEnemyBase :
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
	CEnemyBase();
	~CEnemyBase();
	int m_iMaxHp;
	int m_iCurHp;
	float m_fMoveSpeed;

private:
	CObject * m_pHPBar = nullptr;
	CObject * m_pHPBar_Edge = nullptr;

public:
	float m_fOffset;
	void Hit(int _iDamage);

};

