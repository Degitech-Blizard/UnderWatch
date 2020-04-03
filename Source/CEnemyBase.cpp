#include "DXUT.h"
#include "CEnemyBase.h"
#include "CPlayer.h"
#include "CPlayerAim.h"
#include "CMainScene.h"
#include "CItem.h"
CEnemyBase::CEnemyBase()
{
}


CEnemyBase::~CEnemyBase()
{
}

void CEnemyBase::Hit(int _iDamage)
{

	m_iCurHp -= _iDamage;
	OBJECT.FindObjectWithTag(Tag::Player)->GetComponent<CPlayer>()->Hit(_iDamage,m_iCurHp <= 0);

}

void CEnemyBase::Awake()
{
	m_pHPBar = OBJECT.AddObject("hpbar", Tag::UI);
	m_pHPBar->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_ENEMT_HPBAR"]);
	m_pHPBar->GetComponent<CSpriteRenderer>()->SetOrderInLayer(2);
	m_pHPBar->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_Billboard);

	m_pHPBar_Edge = OBJECT.AddObject("hpbar", Tag::UI);
	m_pHPBar_Edge->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_ENEMT_HPBAR"]);
	m_pHPBar_Edge->GetComponent<CSpriteRenderer>()->SetColor(D3DCOLOR_ARGB(50, 255, 255, 255));
	m_pHPBar_Edge->GetComponent<CSpriteRenderer>()->SetOrderInLayer(1);
	m_pHPBar_Edge->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_Billboard);
}	


void CEnemyBase::Start()
{
}

void CEnemyBase::Update()
{
	if(m_pHPBar) m_pHPBar->Transform->SetPosition(this->Transform->GetPosition() + Vector3(0, m_fOffset, 0));
	if (m_pHPBar_Edge) m_pHPBar_Edge->Transform->SetPosition(this->Transform->GetPosition() + Vector3(0, m_fOffset, 0));
	if (m_pHPBar) m_pHPBar->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 137 * (float)m_iCurHp / (float)m_iMaxHp, 16));
}

void CEnemyBase::LateUpdate()
{
	if (this->m_iCurHp <= 0)
	{
		CObject * pEffect = OBJECT.AddObject();
		pEffect->Transform->SetPosition(this->Transform->GetPosition() + Vector3(0, 128, 0));
		pEffect->Transform->SetScale(Vector3(0.25f, 0.25f, 0.25f));

		pEffect->AddComponent<CEffect>()->SetEffect("2D_EFFECT_EXPLOSION", 0.f);
		m_pHPBar->Destroy();
		m_pHPBar_Edge->Destroy();
		this->m_pObject->Destroy();
	}
}


void CEnemyBase::OnDestroy()
{
//	auto Obj = OBJECT.AddObject();
//	Obj->AddComponent<CItem>()->SetItemKind(ItemKind::IK_ATKUP);
//	Obj->Transform->SetPosition(this->Transform->GetPosition() + Vector3(0,128,0));
}

void CEnemyBase::OnRender()
{
}

void CEnemyBase::OnEnable()
{
}

void CEnemyBase::OnDisable()
{
}

void CEnemyBase::OnCollisionEnter(CObject * _pObject)
{

}

void CEnemyBase::OnCollisionStay(CObject * _pObject)
{
}

void CEnemyBase::OnCollisionExit(CObject * _pObject)
{
}
