#pragma once
#include "CComponent.h"
class CEnemy03 :
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
	CEnemy03();
	~CEnemy03();

	CObject * m_pPlayer;
	float m_fDegree = 0.f;
	float m_fOffset = 0.f;
	int i = 0;

};

