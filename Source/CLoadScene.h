#pragma once
#include "CScene.h"

struct SoundLoadData
{
public:
	SoundLoadData(CRString _Key, CRString _Path) : m_Key(_Key), m_Path(_Path) { }
	~SoundLoadData() {}
public:
	string m_Key;
	string m_Path;
};

struct MeshLoadData
{
public:
	MeshLoadData(CRString _Key, CRString _Path ,CRString _MapPath) : m_Key(_Key), m_Path(_Path), m_MapPath(_MapPath) { }
	~MeshLoadData() {}
public:
	string m_Key;
	string m_Path;
	string m_MapPath;
};

struct ImageLoadData
{
public:
	ImageLoadData(CRString _Key, CRString _Path) : m_Key(_Key), m_Path(_Path) { }
	~ImageLoadData() {}
public:
	string m_Key;
	string m_Path;
};


class CLoadScene : public CScene
{
public:
	CLoadScene();
	~CLoadScene();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void LoadSprite (CRString _Key, CRString _Path, int _iSize = 1);
	void LoadMesh	(CRString _Key, CRString _Path, CRString _MapPath = "", int _iSize = 1);
	void LoadSound	(CRString _Key, CRString _Path, int _iSize = 1);
private:

	void LoadSprite(ImageLoadData _Data);
	void LoadMesh(MeshLoadData _Data);
	void LoadSound(SoundLoadData _Data);
	vector<MeshLoadData>  m_vecMeshLoad ;
	vector<SoundLoadData> m_vecSoundLoad;
	vector<ImageLoadData> m_vecImageLoad;
	CObject * m_pTitleBackground;
	CObject * m_pTitleStartButton;
	CObject * m_pLoadingGauge;
	int m_MeshSize;
	int m_MeshMaxSize;
	int m_SoundSize;
	int m_SoundMaxSize;
	int m_ImageSize;
	int m_ImageMaxSize;
	int m_LoadMax;

	float m_fTime = 0.f; 
	bool m_bEndOfLoad;
};

