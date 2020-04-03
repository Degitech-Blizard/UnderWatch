#include "DXUT.h"
#include "CPlayerSkill.h"


CPlayerSkill::CPlayerSkill()
{
}


CPlayerSkill::~CPlayerSkill()
{
}

void CPlayerSkill::UseSkill01(float _fCoolTime)
{
	m_fPlayerSkill01_CoolTime = _fCoolTime;
	m_fTime01 = _fCoolTime;
	this->m_pPlayerSkill01_CoolTime->GetComponent<CSpriteRenderer>()->SetIsEnable(true);
	this->m_pPlayerSkill01_CoolTime->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 91, 65));
}

void CPlayerSkill::UseSkill02(float _fCoolTime)
{
	m_fPlayerSkill02_CoolTime = _fCoolTime;
	m_fTime02 = _fCoolTime;
	this->m_pPlayerSkill02_CoolTime->GetComponent<CSpriteRenderer>()->SetIsEnable(true);
	this->m_pPlayerSkill02_CoolTime->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 91, 65));
}

void CPlayerSkill::UseSkill03(float _fCoolTime)
{
	m_fPlayerSkill03_CoolTime = _fCoolTime;
	m_fTime03 = _fCoolTime;
	this->m_pPlayerSkill03_CoolTime->GetComponent<CSpriteRenderer>()->SetIsEnable(true);
	this->m_pPlayerSkill03_CoolTime->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 91, 65));

}

void CPlayerSkill::Awake()
{
	this->m_pPlayerSkill01_CoolTime = OBJECT.AddObject("Skill01", Tag::UI);
	this->m_pPlayerSkill02_CoolTime = OBJECT.AddObject("Skill01", Tag::UI);
	this->m_pPlayerSkill03_CoolTime = OBJECT.AddObject("Skill01", Tag::UI);
	this->m_pPlayerSkill01_CoolTime->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_COOLTIME"]);
	this->m_pPlayerSkill02_CoolTime->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_COOLTIME"]);
	this->m_pPlayerSkill03_CoolTime->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_COOLTIME"]);
	this->m_pPlayerSkill01_CoolTime->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerSkill02_CoolTime->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerSkill03_CoolTime->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerSkill01_CoolTime->GetComponent<CSpriteRenderer>()->SetOrderInLayer(10);
	this->m_pPlayerSkill02_CoolTime->GetComponent<CSpriteRenderer>()->SetOrderInLayer(10);
	this->m_pPlayerSkill03_CoolTime->GetComponent<CSpriteRenderer>()->SetOrderInLayer(10);
	this->m_pPlayerSkill01_CoolTime->Transform->SetPosition(Vector3(Property::WinSize.x - 300, WinSize.y-100, 0.f));
	this->m_pPlayerSkill02_CoolTime->Transform->SetPosition(Vector3(Property::WinSize.x - 200, WinSize.y-100, 0.f));
	this->m_pPlayerSkill03_CoolTime->Transform->SetPosition(Vector3(Property::WinSize.x - 100, WinSize.y-100, 0.f));
	this->m_pPlayerSkill01_CoolTime->AddComponent<CSpriteRenderer>()->SetIsEnable(false);
	this->m_pPlayerSkill02_CoolTime->AddComponent<CSpriteRenderer>()->SetIsEnable(false);
	this->m_pPlayerSkill03_CoolTime->AddComponent<CSpriteRenderer>()->SetIsEnable(false);

	this->m_pPlayerSkill01_Icon = OBJECT.AddObject("Skill01", Tag::UI);
	this->m_pPlayerSkill02_Icon = OBJECT.AddObject("Skill01", Tag::UI);
	this->m_pPlayerSkill03_Icon = OBJECT.AddObject("Skill01", Tag::UI);
	this->m_pPlayerSkill01_Icon->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_LS_ICON"]);
	this->m_pPlayerSkill02_Icon->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_E_ICON"]);
	this->m_pPlayerSkill03_Icon->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_RM_ICON"]);
	this->m_pPlayerSkill01_Icon->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerSkill02_Icon->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerSkill03_Icon->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerSkill01_Icon->Transform->SetPosition(Vector3(Property::WinSize.x - 300,WinSize.y-100, 0.f));
	this->m_pPlayerSkill02_Icon->Transform->SetPosition(Vector3(Property::WinSize.x - 200,WinSize.y-100, 0.f));
	this->m_pPlayerSkill03_Icon->Transform->SetPosition(Vector3(Property::WinSize.x - 100,WinSize.y-100, 0.f));


	this->m_pPlayerSkill01_Key = OBJECT.AddObject("Skill01", Tag::UI);
	this->m_pPlayerSkill02_Key = OBJECT.AddObject("Skill01", Tag::UI);
	this->m_pPlayerSkill03_Key = OBJECT.AddObject("Skill01", Tag::UI);
	this->m_pPlayerSkill01_Key->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_LS_KEY"]);
	this->m_pPlayerSkill02_Key->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_E_KEY"]);
	this->m_pPlayerSkill03_Key->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_RM_KEY"]);
	this->m_pPlayerSkill01_Key->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerSkill02_Key->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerSkill03_Key->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerSkill01_Key->Transform->SetPosition(Vector3(Property::WinSize.x - 300, WinSize.y -50, 0.f));
	this->m_pPlayerSkill02_Key->Transform->SetPosition(Vector3(Property::WinSize.x - 200, WinSize.y -50, 0.f));
	this->m_pPlayerSkill03_Key->Transform->SetPosition(Vector3(Property::WinSize.x - 100, WinSize.y -50, 0.f));
}

void CPlayerSkill::Start()
{
}

void CPlayerSkill::Update()
{
	if (m_fPlayerSkill01_CoolTime > 0.f)
	{
		m_fPlayerSkill01_CoolTime -= DeltaTime;

		this->m_pPlayerSkill01_CoolTime->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 91 *  m_fPlayerSkill01_CoolTime / m_fTime01, 65));
		this->m_pPlayerSkill01_Key->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_LS_KEY_DOWN"]);
		this->m_pPlayerSkill01_CoolTime->AddComponent<CSpriteRenderer>()->SetIsEnable(true);
	}
	else
	{
		this->m_pPlayerSkill01_Key->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_LS_KEY"]);
		this->m_pPlayerSkill01_CoolTime->AddComponent<CSpriteRenderer>()->SetIsEnable(false);
	}


	if (m_fPlayerSkill02_CoolTime > 0.f)
	{
		m_fPlayerSkill02_CoolTime -= DeltaTime;

		this->m_pPlayerSkill02_CoolTime->GetComponent<CSpriteRenderer>()->SetRect(Rect(0,  0, 91 * m_fPlayerSkill02_CoolTime / m_fTime02, 65));
		this->m_pPlayerSkill02_Key->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_E_KEY_DOWN"]);
		this->m_pPlayerSkill02_CoolTime->AddComponent<CSpriteRenderer>()->SetIsEnable(true);

	}
	else
	{
		this->m_pPlayerSkill02_Key->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_E_KEY"]);
		this->m_pPlayerSkill02_CoolTime->AddComponent<CSpriteRenderer>()->SetIsEnable(false);
	}


	if (m_fPlayerSkill03_CoolTime > 0.f)
	{
		m_fPlayerSkill03_CoolTime -= DeltaTime;

		this->m_pPlayerSkill03_CoolTime->GetComponent<CSpriteRenderer>()->SetRect(Rect(0,  0, 91 *  m_fPlayerSkill03_CoolTime / m_fTime03, 65));
		this->m_pPlayerSkill03_Key->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_RM_KEY_DOWN"]); 
		this->m_pPlayerSkill03_CoolTime->AddComponent<CSpriteRenderer>()->SetIsEnable(true);

	}
	else
	{
		this->m_pPlayerSkill03_Key->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_SKILL_RM_KEY"]);
		this->m_pPlayerSkill03_CoolTime->AddComponent<CSpriteRenderer>()->SetIsEnable(false);
	}
}

void CPlayerSkill::LateUpdate()
{
}

void CPlayerSkill::OnDestroy()
{
}

void CPlayerSkill::OnRender()
{
}

void CPlayerSkill::OnEnable()
{
}

void CPlayerSkill::OnDisable()
{
}

void CPlayerSkill::OnCollisionEnter(CObject * _pObject)
{
}

void CPlayerSkill::OnCollisionStay(CObject * _pObject)
{
}

void CPlayerSkill::OnCollisionExit(CObject * _pObject)
{
}
