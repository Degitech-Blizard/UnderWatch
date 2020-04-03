#pragma once
#include "CComponent.h"
#include "CPlayer.h"
class CPlayerUltimate :
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
	CPlayerUltimate();
	~CPlayerUltimate();

private:
	CObject * m_pUltimateUI;

	CObject * m_pUltimateDuractionMax;
	CObject * m_pUltimateDuractionEdge;


	CObject * m_pUltimateBackground;
	
	CPlayer * m_pPlayer = nullptr;
};

