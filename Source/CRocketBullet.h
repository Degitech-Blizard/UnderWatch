#pragma once
#include "CComponent.h"
class CRocketBullet :
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
	CRocketBullet();
	~CRocketBullet();
	

public:
	Vector3 m_vDir;
	float m_fTime = 0.f;

	list<CObject *> m_listEnemy;
};

