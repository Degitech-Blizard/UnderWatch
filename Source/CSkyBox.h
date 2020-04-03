#pragma once
class CSkyBox
{
	friend class CCameraManager;
public:
	CSkyBox(CTexture * top, CTexture * bottom, CTexture * left, CTexture * right, CTexture *front, CTexture * back);
	~CSkyBox();

private:
	int  FrameMove(float et);
	void FrameRender();

public:
	LPDIRECT3DVERTEXBUFFER9		mVtx[6];
	LPDIRECT3DINDEXBUFFER9		mIdx[6];
	LPDIRECT3DTEXTURE9			mTex[6];
};
