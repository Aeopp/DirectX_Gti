#include "CScene.h"
#include "Layer.h"
#include "Obj.h"
#include <algorithm>
#include <tuple>
#include <vector>

CScene::CScene()
{
	CLayer* pLayer = CreateLayer(L"UI",  INT_MAX);
	pLayer = CreateLayer(L"HUD", INT_MAX-1);

	CurrentDefaultLayer =  pLayer = CreateLayer(L"Default",1);
	pLayer = CreateLayer(L"Stage");
	
	m_eSceneType = SC_CURRENT;
}

CScene::~CScene() noexcept
{
	ErasePrototype(m_eSceneType);
	Safe_Delete_VecList(m_LayerList);
}

CLayer* CScene::CreateLayer(const wstring& strTag, int iZOrder)
{
	CLayer* pLayer = new CLayer;

	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZOrder);
	pLayer->SetScene(this); 

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 2) {
		m_LayerList.sort(CScene::LayerSort);
	}
	return  pLayer; 
}

CLayer* CScene::FindLayer(const wstring& strTag)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter) {
		if ((*iter)->GetTag() == strTag) {
			return *iter; 
		} 
	}
	return nullptr; 
}

bool CScene::Init()
{
	return true;
}

void CScene::Input(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()){
			++iter;
			continue; 
		}
		(*iter)->Input(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;  
	}
}

int CScene::Update(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;
	}
	// ���� ������Ʈ�� ����ִ� ������Ʈ�� �и�
	// �и��� ���� �ڷᱸ������ ������Ʈ�� �����ϰ� �޸𸮸� �����Ѵ�.
	using ObjPtrType = decltype(CObj::m_ObjList)::value_type;
	// True //////iter->False 
	auto DieObject = std::stable_partition(std::begin(CObj::m_ObjList), std::end(CObj::m_ObjList),
		[](ObjPtrType findDeath) {
			return  (findDeath->GetLife()==true); });
	std::for_each(DieObject, std::end(CObj::m_ObjList), [](ObjPtrType Obj) {
		SAFE_DELETE(Obj); });
	CObj::m_ObjList.erase(DieObject, std::end(CObj::m_ObjList));

	return 0; 
}

int CScene::LateUpdate(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->LateUpdate(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;
	}
	return 0;
}

void CScene::Collision(float fDeltaTime)
{
	if (bCollisionUpdate == false)return;

	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Collision(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;
	}
}

void CScene::Render(HDC hDC, float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Render(hDC, fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;
	}
}

void CScene::StageClear()& {
	for (auto& element : MonsterList) {
		element->m_bEnable = false; 
		element->bCollision = false;
	}
	MonsterList.clear();
	return; 
}

bool CScene::LayerSort(CLayer* pL1, CLayer* pL2)
{
	//CLayer* pLayer = new CLayer;

	return pL1->GetZOrder() < pL2->GetZOrder(); 
}
void CScene::ErasePrototype(
	SCENE_CREATE sc)
{
	Safe_Release_Map(m_mapPrototype[sc]);
}
void CScene::ErasePrototype(const wstring& strTag,
	SCENE_CREATE sc)
{
	auto iter = m_mapPrototype[sc].find(strTag);
	if (!iter->second) {
		return;
	}
	SAFE_RELEASE(iter->second);
	m_mapPrototype[sc].erase(iter);
}


CObj* CScene::FindPtototype(const wstring& strKey,
	SCENE_CREATE sc)
{
	auto iter = m_mapPrototype[sc].find(strKey);
	if (iter == m_mapPrototype[sc].end())
		return nullptr;

	return iter->second;
}






void CScene::ChangeProtoType()
{
	ErasePrototype(SC_CURRENT);
	m_mapPrototype[SC_CURRENT] = m_mapPrototype[SC_NEXT];
	m_mapPrototype[SC_NEXT].clear();
}