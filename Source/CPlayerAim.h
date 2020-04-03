#pragma once
#include "CComponent.h"
#include "CPlayer.h"
class CPlayerAim :
	public CComponent
{
	friend class CObjectManager;
	friend class CObject;
	friend class CMainScene;
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
	CPlayerAim();
	~CPlayerAim();

private:
	CObject * m_pCrossHairAim;
	CObject * m_pHitAim;
	CObject * m_pKillAim;
public: 
	void Hit();
	void Kill();

};

