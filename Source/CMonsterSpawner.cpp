#include "DXUT.h"
#include "CMonsterSpawner.h"
#include "CEnemy01.h"
#include "CEnemy02.h"
#include "CEnemy03.h"

#include "CEnemyBase.h"
CMonsterSpawner::CMonsterSpawner()
{
}


CMonsterSpawner::~CMonsterSpawner()
{
}


void CMonsterSpawner::Awake()
{
}

void CMonsterSpawner::Start()
{
}

void CMonsterSpawner::Update()
{
	if (m_fBreakTime >= 0.f)
	{
		m_fBreakTime -= DeltaTime;
	}
	else
	{
		m_fBreakTime = 0.f;
		m_fPhaseRespawnTime += DeltaTime;
		if (m_fPhaseRespawnTime > m_fPhaseRespawnDelay)
		{
			m_fPhaseRespawnTime = 0.f;
			m_iPhaseRespawnCount--;
			Vector3 SpawnPos[7];
			SpawnPos[0] = Vector3(1550, 0, 2018);
			SpawnPos[1] = Vector3(2170, 0, 72);
			SpawnPos[2] = Vector3(2213, 0, 649);
			SpawnPos[3] = Vector3(2310, 0, 1320);
			SpawnPos[4] = Vector3(2250, 0, 2136);
			SpawnPos[5] = Vector3(1950, 0, 1360);
			SpawnPos[6] = Vector3(2060, 0, 764);
			if (m_iPhaseRespawnCount != 1)
			{
				for (int i = 0; i < max(3 + m_iPhase/4, 7); i++)
				{
					auto Enemy = OBJECT.AddObject("", Tag::Enemy);

					Enemy->AddComponent<CEnemy01>();
					Enemy->AddComponent<CEnemyBase>()->m_iMaxHp = 5 + (int)(m_iPhase /5);
					Enemy->GetComponent<CEnemyBase>()->m_iCurHp = 5 + (int)(m_iPhase /5);
					int seed = rand() % 3;
					Enemy->Transform->SetPosition(SpawnPos[i]);
				}
			}
			else
			{
				if (m_iPhase % 2 == 0)
				{
					for (int i = 0; i < min(m_iPhase /3 + 1, 5); i++)
					{

						auto Enemy = OBJECT.AddObject("", Tag::Enemy);
						Enemy->AddComponent<CEnemy02>();
						Enemy->AddComponent<CEnemyBase>()->m_iMaxHp = 14 + m_iPhase / 2;
						Enemy->GetComponent<CEnemyBase>()->m_iCurHp = 14 + m_iPhase / 2;
						int seed = rand() % 7;
						Enemy->Transform->SetPosition(SpawnPos[ 1 + i]);
					}
				}
				if (m_iPhase % 5 == 0)
				{
					if (a == false)
					{
						a = true;
						SOUND.Play("SND_MAIN_BG", false);
					}
					for (int i = 0; i < min(m_iPhase / 5,3); i++)
					{
						
						auto Enemy = OBJECT.AddObject("", Tag::Enemy);
						Enemy->AddComponent<CEnemy03>();
						Enemy->AddComponent<CEnemyBase>()->m_iMaxHp = 35 + m_iPhase *2;
						Enemy->GetComponent<CEnemyBase>()->m_iCurHp = 35 + m_iPhase *2;
						int seed = rand() % 7;
						Enemy->Transform->SetPosition(SpawnPos[2 + i]);
					}
				}
			}
			if (m_iPhaseRespawnCount <= 0)
			{
				m_fBreakTime = 5.f;
				m_iPhaseRespawnCount = 3 + m_iPhase / 2;
				m_iPhase++;
				SCENE.m_iScore += m_iPhase * 50;
			}

		}


	}


}

void CMonsterSpawner::LateUpdate()
{
}

void CMonsterSpawner::OnDestroy()
{
}

void CMonsterSpawner::OnRender()
{
}

void CMonsterSpawner::OnEnable()
{
}

void CMonsterSpawner::OnDisable()
{
}

void CMonsterSpawner::OnCollisionEnter(CObject * _pObject)
{
}

void CMonsterSpawner::OnCollisionStay(CObject * _pObject)
{
}

void CMonsterSpawner::OnCollisionExit(CObject * _pObject)
{
}
