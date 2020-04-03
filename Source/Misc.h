#pragma once
//------------------------------------------------------------------
// 버텍스
//------------------------------------------------------------------
struct  CVERTEX2D { float x, y, z, rhw;		DWORD color; };	//버텍스 타입 구조체
#define CVERTEX2D_FVF		( D3DFVF_XYZRHW		|	D3DFVF_DIFFUSE	)	//버텍스 포맷

struct  CVERTEX3D { float x, y, z;			DWORD color; };
#define CVERTEX3D_FVF		( D3DFVF_XYZ		|	D3DFVF_DIFFUSE	)

struct	CVERTEXLT { D3DXVECTOR3 pos;		D3DXVECTOR3 normal; };
#define	CVERTEXLT_FVF		( D3DFVF_XYZ		|	D3DFVF_NORMAL	)

struct	CVERTEX2D_TEX { D3DXVECTOR4 pos;		D3DCOLOR color;		float tu, tv; };
#define	CVERTEX2D_TEX_FVF	( D3DFVF_XYZRHW		|	D3DFVF_DIFFUSE	|	D3DFVF_TEX1  )

struct	CVERTEX3D_TEX { D3DXVECTOR3 pos;		D3DXVECTOR3 normal;	float tu, tv; };
#define	CVERTEX3D_TEX_FVF	( D3DFVF_XYZ		|	D3DFVF_NORMAL	|	D3DFVF_TEX1  )

struct	CINDEX { WORD _0, _1, _2; };
struct	CINDEXLINE { WORD _0, _1; };

void	Set_Vtx2D(CVERTEX2D &ct, float x, float y, float z, float rhw, DWORD clr);
void	Set_Vtx3D(CVERTEX3D &ct, float x, float y, float z, DWORD clr);
void	Set_VtxLT(CVERTEXLT &ct, D3DXVECTOR3 p, D3DXVECTOR3 n);
void	Set_Vtx2D_Tex(CVERTEX2D_TEX &ct, D3DXVECTOR4 p, DWORD clr, float tu, float tv);
void	Set_Vtx3D_Tex(CVERTEX3D_TEX &ct, D3DXVECTOR3 p, D3DXVECTOR3 n, float tu, float tv);
void	Set_Idx(CINDEX &ci, WORD _0, WORD _1, WORD _2);
void	Set_IdxLine(CINDEXLINE &ci, WORD _0, WORD _1);

//------------------------------------------------------------------
// 
//------------------------------------------------------------------
HRESULT	Create_Vtx2D(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DTEXTURE9 &tex, int x, int y, int w, int h, WCHAR* str = NULL, DWORD dif = 0xffffffff, float tu0 = 0.f, float tv0 = 0.f, float tu1 = 1.f, float tv1 = 1.f);
void	Render_Vtx2D(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DTEXTURE9 &tex);
HRESULT	Create_Vtx2DI(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DINDEXBUFFER9 &ib, LPDIRECT3DTEXTURE9 &tex, int x, int y, int w, int h, WCHAR* str = NULL, DWORD dif = 0xffffffff, float tu0 = 0.f, float tv0 = 0.f, float tu1 = 1.f, float tv1 = 1.f);
void	Render_Vtx2DI(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DINDEXBUFFER9 &ib, LPDIRECT3DTEXTURE9 &tex);

void	Release_Vtx(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DTEXTURE9 &tex);
void	Release_VtxI(LPDIRECT3DVERTEXBUFFER9 &vb, LPDIRECT3DINDEXBUFFER9 &ib, LPDIRECT3DTEXTURE9 &tex);
//------------------------------------------------------------------
// 
//------------------------------------------------------------------
WCHAR*  ctow(char* val, ...);
void	DrawPrintf(WCHAR* str, int x, int y, int w, int h, DWORD flags = DT_LEFT, DWORD color = 0xffffffff);