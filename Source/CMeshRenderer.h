#pragma once
#include "CRenderer3D.h"
class CMeshRenderer : public CRenderer3D
{
	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Awake()								override;
	virtual void Start()								override;
	virtual void Update()								override;
	virtual void LateUpdate()							override;
	virtual void Render()								override;
	virtual void OnRender()								override;
	virtual void OnDestroy()							override;
	virtual void OnEnable()								override;
	virtual void OnDisable()							override;
	virtual void OnCollisionEnter(CObject * _pObject)	override;
	virtual void OnCollisionStay(CObject * _pObject)	override;
	virtual void OnCollisionExit(CObject * _pObject)	override;

public:
	CMeshRenderer();
	~CMeshRenderer();


private:
	CModel * m_pModel =NULL;

public:
	void SetModel(CModel * _pModel)
	{
		m_pModel = _pModel;
	}
	CModel * GetModel(CModel * _pModel)
	{
		return m_pModel;
	}



};

