#pragma once
#include "CComponent.h"
class CHealMachine :
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
	CHealMachine();
	~CHealMachine();


private:
	float m_fHealPerSec;
	float m_fDuraction;
	float m_fTime;
	float m_fRange;
	CObject * m_pPlayer = nullptr;
	CObject * m_pFloor = nullptr;
public:
	float GetHealPerSec() { return m_fHealPerSec; }
	void SetHealPerSec(float _fHealPerSec) { m_fHealPerSec = _fHealPerSec; }
	float GetDuraction() { return m_fDuraction; }
	void SetDuraction(float _fDuraction) { m_fDuraction = _fDuraction; }
	float GetRange() { return m_fRange; }
	void SetRange(float _fRange) { m_fRange = _fRange; }

};

