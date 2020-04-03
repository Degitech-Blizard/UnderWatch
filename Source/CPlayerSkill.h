#pragma once
#include "CComponent.h"
#include "CPlayer.h"
class CPlayer;
class CPlayerSkill :
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
	CPlayerSkill();
	~CPlayerSkill();

	CObject * m_pPlayerSkill01_CoolTime;
	CObject * m_pPlayerSkill01_Icon;
	CObject * m_pPlayerSkill01_Key;
	float m_fPlayerSkill01_CoolTime = 0.f;
	float m_fTime01 = 0.f;
	
	CObject * m_pPlayerSkill02_CoolTime;
	CObject * m_pPlayerSkill02_Icon;
	CObject * m_pPlayerSkill02_Key;
	float m_fPlayerSkill02_CoolTime = 0.f;
	float m_fTime02 = 0.f;

	CObject * m_pPlayerSkill03_CoolTime;
	CObject * m_pPlayerSkill03_Icon;
	CObject * m_pPlayerSkill03_Key;
	float m_fPlayerSkill03_CoolTime = 0.f;
	float m_fTime03 = 0.f;
	CPlayer * m_pPlayer = nullptr;

	void UseSkill01(float _fCoolTime);
	void UseSkill02(float _fCoolTime);
	void UseSkill03(float _fCoolTime);

	bool CanUseSkill01() { return m_fPlayerSkill01_CoolTime <= 0; }
	bool CanUseSkill02() { return m_fPlayerSkill02_CoolTime <= 0; }
	bool CanUseSkill03() { return m_fPlayerSkill03_CoolTime <= 0; }
};

