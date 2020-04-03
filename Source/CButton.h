#pragma once
#include "CComponent.h"
enum class ButtonStatus { BS_IDLE,BS_ONCURSOR, BS_PRESS };
enum class ButtonType { BT_SCAILING, BT_COLORING,BT_IMAGESWAP};
class CSpriteRenderer;
class CButton :
	public CComponent
{
public:
	CButton();
	~CButton();
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

	CTexture * m_pSwapTexture = nullptr;
	CTexture * m_pNormalTexture; 
	Rect m_Rect;

	function<void()> m_OnClickFunc;
	ButtonStatus m_Status;
	ButtonType m_Type;
	CSpriteRenderer * m_pSpriteRender = nullptr;

public:
	void SetOnClickFunc(function<void()> _OnClickFunc) { m_OnClickFunc = _OnClickFunc; }
	
	CTexture * GetSwapTexture() { return m_pSwapTexture; }
	void SetSwapTexture(CTexture * _pSwapTexture) { m_pSwapTexture = _pSwapTexture; }

	CTexture * GetNormalTexture() { return m_pNormalTexture; }
	void SetNormalTexture(CTexture * _pNormalTexture) { m_pNormalTexture = _pNormalTexture; }

	void SetRect(Rect _Re) { m_Rect = _Re; }
	Rect GetRect() { return m_Rect; }

	ButtonStatus GetStatus() { return m_Status; }
	void SetStatus(ButtonStatus _Status) { m_Status = _Status; }

	ButtonType GetType() { return m_Type; }
	void SetType(ButtonType _Type) { m_Type = _Type; }
};

