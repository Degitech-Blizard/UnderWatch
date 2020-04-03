#pragma once
#include "CComponent.h"
enum ItemKind { IK_HEAL, IK_ATKUP, IK_HPUP};
class CItem :
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
	CItem();
	~CItem();

private:
	ItemKind m_Kind;
	float m_fDegree;
	float m_fOffset;
	CObject * m_pBottom = nullptr;
public:
	ItemKind GetItemKind() { return m_Kind; }
	void SetItemKind(ItemKind _Kind) { 
		m_Kind = _Kind; 
		if (_Kind == ItemKind::IK_ATKUP)
		{
			this->GetComponent<CMeshRenderer>()->SetModel(MODEL["3D_ITEM_ATKUP"]);
		}
		else if (_Kind == ItemKind::IK_HPUP)
		{
			this->GetComponent<CMeshRenderer>()->SetModel(MODEL["3D_ITEM_HPUP"]);
		}
		else if (_Kind == ItemKind::IK_HEAL)
		{
			this->GetComponent<CMeshRenderer>()->SetModel(MODEL["3D_ITEM_HEAL"]);
		}
	}


};

