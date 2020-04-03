#include "DXUT.h"
#include "CButton.h"


CButton::CButton()
{
}


CButton::~CButton()
{
}

void CButton::Awake()
{
	this->m_pSwapTexture = nullptr;
	this->m_Rect = Rect(0, 0, 0, 0);
	this->m_Status = ButtonStatus::BS_IDLE;
	this->m_Type = ButtonType::BT_COLORING;
}

void CButton::Start()
{
	this->m_pSpriteRender = this->GetComponent<CSpriteRenderer>();
}

void CButton::Update()
{
	Vector2 vMouse = INPUT.GetMousePos();
	Vector2 Pos = this->Transform->GetPosition();
	bool OnCursor = Physic.CheckCollision(Rect(Pos - Vector2(this->m_Rect.GetWidth()/2.f, this->m_Rect.GetHeight()/2.f), m_Rect.GetWidth(), m_Rect.GetHeight()), vMouse);
	if (OnCursor)
	{
		if (INPUT.KeyDown(VK_LBUTTON))
		{
			this->m_Status = ButtonStatus::BS_PRESS;
		}
		else if (INPUT.KeyUp(VK_LBUTTON))
		{
			if(m_OnClickFunc)
			this->m_OnClickFunc();
		}
		else this->m_Status = ButtonStatus::BS_ONCURSOR;
	}
	else
	{
		this->m_Status = ButtonStatus::BS_IDLE;
	}

	if (OnCursor)
	{
		switch (m_Type)
		{
		case ButtonType::BT_IMAGESWAP:
		{
			m_pSpriteRender->SetTexture(this->m_pSwapTexture);
			break;
		}
		case ButtonType::BT_COLORING:
		{
			D3DXCOLOR Color = D3DXCOLOR(m_pSpriteRender->GetColor());
			D3DXColorLerp(&Color, &Color, &D3DXCOLOR(1.f, 0.75f, 0.75f, 0.75f), DeltaTime * 12);
			m_pSpriteRender->SetColor(Color);
			break;
		}
		case ButtonType::BT_SCAILING:
		{
			Vector3 Scale = this->Transform->GetScale();
			Lerp(&Scale, Scale, Vector3(1.2f, 1.2f, 1.f), DeltaTime * 12.f);
			this->Transform->SetScale(Scale);
			break;
		}
		}
	}
	else
	{
		switch (m_Type)
		{
		case ButtonType::BT_IMAGESWAP:
		{
			m_pSpriteRender->SetTexture(this->m_pNormalTexture);
			break;
		}
		case ButtonType::BT_COLORING:
		{
			D3DXCOLOR Color = D3DXCOLOR(m_pSpriteRender->GetColor());
			D3DXColorLerp(&Color, &Color, &D3DXCOLOR(1.f, 1.f, 1.f, 1.f), DeltaTime * 12);
			m_pSpriteRender->SetColor(Color);
			break;
		}
		case ButtonType::BT_SCAILING:
		{
			Vector3 Scale = this->Transform->GetScale();
			Lerp(&Scale, Scale, Vector3(1.2f, 1.2f, 1.f), DeltaTime * 12.f);
			this->Transform->SetScale(Scale);
			break;
		}
		}
	}
}

void CButton::LateUpdate()
{
}

void CButton::OnDestroy()
{
}

void CButton::OnRender()
{
}

void CButton::OnEnable()
{
}

void CButton::OnDisable()
{
}

void CButton::OnCollisionEnter(CObject * _pObject)
{
}

void CButton::OnCollisionStay(CObject * _pObject)
{
}

void CButton::OnCollisionExit(CObject * _pObject)
{
}
