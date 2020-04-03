#pragma once
#include "CScene.h"

#include "CPlayerHPbar.h"
#include "CPlayerUltimate.h"
class CMainScene :
	public CScene
{
public:
	CMainScene();
	~CMainScene();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	CPlayerHPbar * m_pPlayerHPbar;
	CPlayerUltimate * m_pPlayerUltimate;

	int * m_iPhase = nullptr;
};

