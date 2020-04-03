#pragma once
#include "CComponent.h"
class CMonsterSpawner :
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
	CMonsterSpawner();
	~CMonsterSpawner();

	int m_iPhase = 1;
	int m_iPhaseRespawnCount = 3;
	bool a = false;

	float m_fPhaseRespawnDelay = 2.5f;
	float m_fPhaseRespawnTime = 0.f;
	float m_fBreakTime = 5.f;

};

