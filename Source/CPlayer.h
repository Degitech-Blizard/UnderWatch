#pragma once
#include "CComponent.h"
#include "CGun.h"
#include "CPlayerSkill.h"
const enum Axis{	Foward,	 Backward,	Left,	Right,	Up,	Down,	Last};
class CPlayerSkill;
class CPlayer :
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
	CPlayer();
	~CPlayer();
	Vector3 m_vAxis[Axis::Last];

	CPlayerSkill * m_pPlayerSkill = nullptr;
	float m_fOffset = 0.f;
	bool m_IsFire = false;
	float m_fCurHp = 200.f;
	float m_fMaxHp = 200.f; 
	float m_fCurUltimate = 3000.f;
	float m_fMaxUltimate = 3000.f;
	float m_fUltimateDuraction = 0.f;
	bool m_bIsCollision = false;
	bool m_bUltimateEnable = false;

	void Hit(float _fDamage,bool _bKill);
private:
	float m_fRebound = 0.f;
	float m_fDegree = 0.f;
	float m_fSensitivity = 10.f;		 // 마우스 감도
	float m_fCamrotX = 0.f;
	float m_fTime = 0.f;
	float m_fWalkTime = 0.f;
	Quaternion m_OldQt;
	Vector3 m_vCamDir;
	CGun * m_pGun = nullptr;
	float m_fMoveSpeed = 500.f;


	


};
