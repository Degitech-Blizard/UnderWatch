#pragma once
#include "CScene.h"
class CGameOverScene :
	public CScene
{
public:
	CGameOverScene();
	~CGameOverScene();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

