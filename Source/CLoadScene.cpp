#include "DXUT.h"
#include "CLoadScene.h"


CLoadScene::CLoadScene()
{

}


CLoadScene::~CLoadScene()
{
}

void CLoadScene::Init()
{
	FX;
	INPUT.SetCenterFixCursor(false);
	m_bEndOfLoad = false;
	IMAGE.AddTexture("2D_TITLE_BACKGROUND", "./resource/2D/Title/UnderWatchMain.png");
	IMAGE.AddTexture("2D_TITLE_LOADING_BAR", "./resource/2D/Title/UnderWatchLoadingBar.png");
	IMAGE.AddTexture("2D_TITLE_LOADING_MSG", "./resource/2D/Title/UnderWatchLoadingWord.png");
	IMAGE.AddTexture("2D_TITLE_LOADING_STARTBUTTON", "./resource/2D/Title/UnderWatchMainStart.png");
	SOUND.AddSound("SND_TITLE", "resource/Sound/BGM/TitleBGM.mp3", SoundType::ST_BACKGROUND);
	SOUND.Play("SND_TITLE", true);
	m_pTitleBackground = OBJECT.AddObject();
	m_pTitleBackground->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_TITLE_BACKGROUND"]);
	m_pTitleBackground->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	m_pTitleBackground->GetComponent<CSpriteRenderer>()->SetOrderInLayer(0);
	m_pTitleBackground->Transform->SetPosition(Vector3(WinSize.x / 2.f, WinSize.y / 2.f, 0.f));

	m_pLoadingGauge = OBJECT.AddObject();
	m_pLoadingGauge->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_TITLE_LOADING_BAR"]);
	m_pLoadingGauge->AddComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	m_pTitleBackground->GetComponent<CSpriteRenderer>()->SetOrderInLayer(10);
	m_pLoadingGauge->Transform->SetPosition(Vector3(WinSize.x / 2.f, WinSize.y - 180, 0.f));
	m_pLoadingGauge->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 309 * 0.f, 65.f));
	//MODEL.AddShader("TOON", "./Shader/OutlineShader.fx");
	LoadMesh("3D_MAP", "3D/Map/Map", "3D/Map/");
	LoadMesh("3D_PLAYER_GUN", "3D/Player/Gun/Gun", "3D/Player/Gun/", 16);
	LoadMesh("3D_PLAYER_BULLET", "3D/Player/Bullet/Bullet", "3D/Player/Bullet/");
	LoadMesh("3D_PLAYER_ROCKET", "3D/Player/Rocket/Rocket", "3D/Player/Rocket/");
	LoadMesh("3D_PLAYER_HEALFLOOR", "3D/Player/HealFloor/HealFloor", "3D/Player/HealFloor/");
	LoadMesh("3D_PLAYER_HEALMACHINE", "3D/Player/HealMachine/HealMachine", "3D/Player/HealMachine/", 61);
	LoadMesh("3D_ITEM_BOTTOM", "./3D/Item/Bottom/Bottom", "./3D/Item/Bottom/");
	LoadMesh("3D_ITEM_HEAL", "./3D/Item/Bottom/Bottom", "./3D/Item/Bottom/");
	LoadMesh("3D_ITEM_HPUP", "./3D/Item/HpUp/HPUp", "./3D/Item/HpUp/");
	LoadMesh("3D_ITEM_ATKUP", "./3D/Item/AtkUp/ATKUp", "./3D/Item/HpUp/");


	LoadMesh("ENEMY01_BOOM", "3D/Enemy/Enemy01/Boom/Boom", "3D/Enemy/Enemy01/", 40);
	LoadMesh("ENEMY01_IDLE", "3D/Enemy/Enemy01/Idle/Idle", "3D/Enemy/Enemy01/", 40);
	LoadMesh("ENEMY01_DIE", "3D/Enemy/Enemy01/Die/Die", "3D/Enemy/Enemy01/", 20);

	LoadMesh("ENEMY02_LAUNCH", "3D/Enemy/Enemy02/Launch/Launch", "3D/Enemy/Enemy02/", 40);
	LoadMesh("ENEMY02_SHOOT", "3D/Enemy/Enemy02/Shoot/Shoot", "3D/Enemy/Enemy02/", 40);
	LoadMesh("ENEMY02_IDLE", "3D/Enemy/Enemy02/Idle/Idle", "3D/Enemy/Enemy02/", 40);
	LoadMesh("ENEMY02_DIE", "3D/Enemy/Enemy02/Die/Die", "3D/Enemy/Enemy02/", 20);
	LoadMesh("ENEMY02_BULLET", "3D/Enemy/Enemy02/Bullet", "3D/Enemy/Enemy02/");


	LoadMesh("ENEMY03_IDLE", "3D/Enemy/Enemy03/Idle/Idle", "3D/Enemy/Enemy03/Idle/", 40);


	//Load 2D Resource

	//Player
	LoadSprite("2D_PLAYER_HPBAR_EMPTY", "2D/Player/Hp/HPBarUi_Empty");
	LoadSprite("2D_PLAYER_HPBAR_FILL", "2D/Player/Hp/HPBarUi_Full");
	LoadSprite("2D_PLAYER_STATUS", "2D/Player/Hp/HpUi");

	LoadSprite("2D_EFFECT_EXPLOSION", "2D/Effect/Explosion/Explosion", 13);
	LoadSprite("2D_PLAYER_WEAPON", "2D/Player/Weapon/WeaponUi");

	LoadSprite("2D_PLAYER_FIREEFFECT_1", "2D/Player/FireEffect/1");
	LoadSprite("2D_PLAYER_FIREEFFECT_2", "2D/Player/FireEffect/2");
	LoadSprite("2D_PLAYER_FIREEFFECT_3", "2D/Player/FireEffect/3");
	LoadSprite("2D_PLAYER_FIREEFFECT_4", "2D/Player/FireEffect/4");

	LoadSprite("2D_PLAYER_ULTIMATE_GAUGE", "2D/Player/Ultimate/UltimateUi_%");
	LoadSprite("2D_PLAYER_ULTIMATE_GAUGE_MAX", "2D/Player/Ultimate/UltimateUi_Full");
	LoadSprite("2D_PLAYER_ULTIMATE_BACKGROUND", "2D/Player/Ultimate/UltimateUi_Aim");
	LoadSprite("2D_PLAYER_ULTIMATE_ENEMY", "2D/Player/Ultimate/UltimateUi_AimPoint");
	LoadSprite("2D_PLAYER_ULTIMATE_ENEMY2", "2D/Player/Ultimate/UltimateUi_EnemyPoint%");
	LoadSprite("2D_PLAYER_ULTIMATE_DURACTION_GAUGE", "2D/Player/Ultimate/UltimateUi_LeftBackGround");
	LoadSprite("2D_PLAYER_ULTIMATE_DURACTION_GAUGE_MAX", "2D/Player/Ultimate/UltimateUi_LeftBar");

	LoadSprite("2D_PLAYER_SKILL_COOLTIME", "2D/Player/Skill/CoolTimeUi");

	LoadSprite("2D_PLAYER_SKILL_E_ICON", "2D/Player/Skill/E_Logo");
	LoadSprite("2D_PLAYER_SKILL_E_KEY", "2D/Player/Skill/E_Word");
	LoadSprite("2D_PLAYER_SKILL_E_KEY_DOWN", "2D/Player/Skill/E_Word_Use");

	LoadSprite("2D_PLAYER_SKILL_LS_ICON", "2D/Player/Skill/LShift_Logo");
	LoadSprite("2D_PLAYER_SKILL_LS_KEY", "2D/Player/Skill/LShift_Word");
	LoadSprite("2D_PLAYER_SKILL_LS_KEY_DOWN", "2D/Player/Skill/LShift_Word_Use");

	LoadSprite("2D_PLAYER_SKILL_RM_ICON", "2D/Player/Skill/RightMouse_Logo");
	LoadSprite("2D_PLAYER_SKILL_RM_KEY", "2D/Player/Skill/RightMouse_Word");
	LoadSprite("2D_PLAYER_SKILL_RM_KEY_DOWN", "2D/Player/Skill/RightMouse_Word_Use");

	LoadSprite("2D_PLAYER_AIM_HIT", "2D/Player/Aim/Aim_Damage");
	LoadSprite("2D_PLAYER_AIM_HIT_HEADSHOT", "2D/Player/Aim/Aim_Damage2");
	LoadSprite("2D_PLAYER_AIM_KILL", "2D/Player/Aim/Aim_Kill");
	LoadSprite("2D_PLAYER_AIM_CROSSHAIR", "2D/Player/Aim/CrossHair");

	LoadSprite("2D_CASTLE_CASTLEUI", "2D/Castle/CastleHP");
	LoadSprite("2D_CASTLE_HPBAR", "2D/Castle/CastleHP_Bar");
	LoadSprite("2D_CASTLE_HPBAR_EDGE", "2D/Castle/CastleHP_BarBackGround");

	LoadSprite("2D_GAMEOVER_AIM_EXIT", "2D/GameOver/ExitButton");
	LoadSprite("2D_GAMEOVER_AIM_RETRY", "2D/GameOver/RetryButton");
	LoadSprite("2D_GAMEOVER_AIM_BACKGORUND", "2D/GameOver/BackGround");
	LoadSprite("2D_ENEMT_HPBAR", "2D/Enemy/EnemyHP");
	
	LoadSprite("2D_SKYBOX_FT", "2D/SkyBox/purplenebula_ft");
	LoadSprite("2D_SKYBOX_LF", "2D/SkyBox/purplenebula_lf");
	LoadSprite("2D_SKYBOX_RT", "2D/SkyBox/purplenebula_rt");
	LoadSprite("2D_SKYBOX_UP", "2D/SkyBox/purplenebula_up");
	LoadSprite("2D_SKYBOX_BK", "2D/SkyBox/purplenebula_bk");
	LoadSprite("2D_SKYBOX_DN", "2D/SkyBox/purplenebula_dn");

	LoadSound("SND_MAIN_BG", "Sound/BGM/IngameHilightBGM");
	LoadSound("SND_MAIN_BG2", "Sound/NaraitionVoice/Introduce1");

	LoadSound("SND_MAIN_BG2", "Sound/NaraitionVoice/Introduce1");

	LoadSound("SND_ENEMY_KILL", "Sound/Enemy/EnemyKill");
	LoadSound("SND_ENEMY_HIT", "Sound/Enemy/EnemyHit");

	LoadSound("SND_PLAYER_ULTIMATE_VOICE", "Sound/SoldierVoice/UltimateVoice");
	LoadSound("SND_PLAYER_FIRE", "Sound/SoldierSound/Fire1");
	LoadSound("SND_PLAYER_STEP", "Sound/SoldierSound/FootStep");
	LoadSound("SND_PLAYER_HIT", "Sound/SoldierSound/PlayerHit");
	LoadSound("SND_PLAYER_RM", "Sound/SoldierSound/Skill1");
	LoadSound("SND_PLAYER_E", "Sound/SoldierSound/Skill2");
	LoadSound("SND_PLAYER_Q", "Sound/SoldierSound/UltimateSFX");
	LoadSound("SND_PLAYER_EXPLOSION", "Sound/Expolsion/Explosion1");
	LoadSound("SND_PLAYER_KILL", "Sound/NaraitionVoice/Kill1");

	m_ImageMaxSize = m_vecImageLoad.size();
	m_MeshMaxSize = m_vecMeshLoad.size();
	m_SoundMaxSize = m_vecSoundLoad.size();

	m_SoundSize = 0;
	m_ImageSize = 0;
	m_MeshSize = 0;

	m_LoadMax = m_ImageMaxSize + m_MeshMaxSize + m_SoundMaxSize;
	DEBUG_LOG("리소스를 로드합니다.");
}

void CLoadScene::Update()
{
	if (m_ImageSize + m_MeshSize + m_SoundSize == m_LoadMax)
	{
		if (m_bEndOfLoad == false)
		{
			m_bEndOfLoad = true;
			DEBUG_LOG("리소스 로딩이 모두 완료되었습니다.");
			m_pLoadingGauge->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_TITLE_LOADING_STARTBUTTON"]);
			m_pLoadingGauge->AddComponent<CButton>()->SetType(ButtonType::BT_COLORING);
			m_pLoadingGauge->GetComponent<CButton>()->SetRect(m_pLoadingGauge->AddComponent<CSpriteRenderer>()->GetRect());
			m_pLoadingGauge->GetComponent<CButton>()->SetOnClickFunc([&]() {SOUND.Stop("SND_TITLE"); SCENE.ChangeScene("S_MAIN");
			});
		}
		DEBUG_LOG("%.1f 초 경과", m_fTime);
	}
	else
	{
		CThreadPool pool;

		m_fTime += DeltaTime;
		int i = 0;

	
					if (m_MeshSize < m_MeshMaxSize)
					{
						pool.EnqueueJob([&](MeshLoadData& index) {
							LoadMesh(index);
						}, m_vecMeshLoad[m_MeshSize]);
						m_MeshSize++;
					}
					else if (m_ImageSize < m_ImageMaxSize)
					{
						pool.EnqueueJob([&](ImageLoadData& index) {
							LoadSprite(index);
						}, m_vecImageLoad[m_ImageSize]);
						m_ImageSize++;
					}
					else if (m_SoundSize < m_SoundMaxSize)
					{
						pool.EnqueueJob([&](SoundLoadData& index) {
							LoadSound(index);
						}, m_vecSoundLoad[m_SoundSize]);
						m_SoundSize++;
					}
				
	
			m_pLoadingGauge->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 309 * ((float)(m_ImageSize + m_MeshSize + m_SoundSize) / (float)m_LoadMax), 65.f));
	}
}

void CLoadScene::Render()
{
}

void CLoadScene::Release()
{
}

void CLoadScene::LoadSprite(CRString _Key, CRString _Path, int _iSize)
{
	if (_iSize == 1)
	{
		char Path[100];
		sprintf(Path, "./resource/%s.png", _Path.c_str());
		m_vecImageLoad.push_back(ImageLoadData(_Key, Path));
	}
	else
	{
		for (int i = 1; i <= _iSize; i++)
		{
			char Path[100];
			char Key[100];
			sprintf(Path, "./resource/%s (%d).png", _Path.c_str(), i);
			sprintf(Key, "%s (%d)", _Key.c_str(), i);

			m_vecImageLoad.push_back(ImageLoadData(Key, Path));
		}
	}
}

void CLoadScene::LoadMesh(CRString _Key, CRString _Path, CRString _MapPath, int _iSize)
{
	if (_iSize == 1)
	{
		char Path[100];
		sprintf(Path, "./resource/%s.obj", _Path.c_str());

		char MapPath[100];
		sprintf(MapPath, "./resource/%s", _MapPath.c_str());


		m_vecMeshLoad.push_back(MeshLoadData(_Key, Path, MapPath));
	}
	else
	{
		for (int i = 1; i <= _iSize; i++)
		{
			char Key[100];
			sprintf(Key, "%s (%d)", _Key.c_str(), i);

			char Path[100];
			sprintf(Path, "./resource/%s (%d).obj", _Path.c_str(), i);

			char MapPath[100];
			sprintf(MapPath, "./resource/%s", _MapPath.c_str());


			m_vecMeshLoad.push_back(MeshLoadData(Key, Path, MapPath));
		}
	}
}

void CLoadScene::LoadSound(CRString _Key, CRString _Path, int _iSize)
{
	if (_iSize == 1)
	{
		char Path[100];
		sprintf(Path, "./resource/%s.mp3", _Path.c_str());
		m_vecSoundLoad.push_back(SoundLoadData(_Key, Path));
	}
	else
	{
		for (int i = 1; i <= _iSize; i++)
		{
			char Path[100];
			char Key[100];
			sprintf(Path, "./resource/%s (%d).mp3", _Path.c_str(), i);
			sprintf(Key, "%s (%d)", _Key.c_str(), i);
			m_vecSoundLoad.push_back(SoundLoadData(Key, Path));
		}
	}
}

void CLoadScene::LoadSprite(ImageLoadData _Data)
{
	this_thread::sleep_for(Second(1) / 1000);
	Sleep(1);

	IMAGE.AddTexture(_Data.m_Key, _Data.m_Path);
	DEBUG_LOG("텍스쳐 데이터 %d 개중 %d를 로딩 했습니다. (%.1f%%)", m_ImageMaxSize, m_ImageSize, 100.f *  (float)m_ImageSize / (float)m_ImageMaxSize);
}

void CLoadScene::LoadMesh(MeshLoadData _Data)
{
	this_thread::sleep_for(Second(1) / 1000);
	Sleep(1);
	MODEL.AddModel(_Data.m_Key, _Data.m_Path, _Data.m_MapPath);
	DEBUG_LOG("메쉬 데이터 %d 개중 %d를 로딩 했습니다. (%.1f%%)", m_MeshMaxSize, m_MeshSize, 100.f *  (float)m_MeshSize / (float)m_MeshMaxSize);

}

void CLoadScene::LoadSound(SoundLoadData _Data)
{
	this_thread::sleep_for(Second(1)/1000);
	Sleep(1);
	SOUND.AddSound(_Data.m_Key, _Data.m_Path, SoundType::ST_BACKGROUND);
	DEBUG_LOG("사운드 데이터 %d 개중 %d를 로딩 했습니다. (%.1f%%)", m_SoundMaxSize, m_SoundSize, 100.f *  (float)m_SoundSize / (float)m_SoundMaxSize);

}
