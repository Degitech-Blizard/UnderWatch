#pragma once
#include "CComponent.h"
#include "CEnemyBase.h"
enum ENEMY02_STATUS {ENEMY02_IDLE, ENEMY02_LAUNCH, ENENMY02_SHOOT};
class CEnemy02 :
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
	CEnemy02();
	~CEnemy02();

private:
	ENEMY02_STATUS m_Status;
	CObject * m_pPlayer;

	float m_fRotationOffset = 0.f;
	float m_fTime = 0.f;
	float m_fTime2 = 0.f;
	float m_fFireDelay;
	bool m_bFire = false;
};

