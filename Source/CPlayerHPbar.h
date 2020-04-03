#pragma once
#include "CComponent.h"
#include "CPlayer.h"
class CPlayerHPbar :
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
	CPlayerHPbar();
	~CPlayerHPbar();

private:
	CObject * m_pPlayerStatus;
	CObject * m_pHPbarEdge;
	CObject * m_pHPbarFull;

	CPlayer * m_pPlayer = nullptr;

};

