#include "DamagePont.h"
#include "Texture.h"
#include "ResourcesManager.h"
#include <string>

bool DamagePont::Init()
{
	SetPos(0.f, 0);
	SetSize(34.f, 46.f);
	SetPivot(0.5f, 0.5f);
	
	SetTexture(L"Damage", L"Damage/Damage.bmp");
	SetColorKey(255, 0, 255);
	//Ponts.resize(10);
	//	SetTexture(L"Player", L"Animation/Player/Left/DEAD.bmp");
	//	std::wstring PontName = L"Damage";

	//	for (int i = 0; i < 10; ++i) {
	//		auto* Texture = Ponts[i];
	//		std::wstring PontIdxStr = PontName + std::to_wstring(i);
	//		Texture = GET_SINGLE(CResourcesManager)->LoadTexture(PontIdxStr,
	//			        (to_wstring(i) + L".bmp").c_str(),TEXTURE_PATH);
	//		Ponts[i] = Texture;
	//		SAFE_RELEASE(Texture);
	//	};

	

    return true ;
}

DamagePont* DamagePont::Clone()
{
    return new DamagePont{ *this } ;
}

void DamagePont::Render(HDC hDC, float fDeltaTime)
{
	if (bRender == false)return;

	auto strIdx = to_wstring(CurrentPrintDamage);

	for (int i = 0; i < strIdx.size();++i) {
		char Number     =       strIdx[i] - 48;
		if (m_pTexture != nullptr) {
			POSITION tPos = DamagePosition - m_tSize * m_tPivot;
			tPos -= GET_SINGLE(CCamera)->GetPos();
			POSITION tImagePos;
			tImagePos += m_tImageOffset;
			if (m_pTexture->GetColorKeyEnable() == true) {
				TransparentBlt(hDC,tPos.x + (i* m_tSize.x), tPos.y, m_tSize.x,
					m_tSize.y, m_pTexture->GetDC(), (Number * m_tSize.x)+tImagePos.x, tImagePos.y,
					m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
			}
			else {
				BitBlt(hDC, tPos.x, tPos.y,
					m_tSize.x, m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y,
					SRCCOPY);
			}
		}
	}
	DamagePosition.y -= fDeltaTime *100;
};

void DamagePont::DamagePrint(POSITION PrintPos,int Damage)
{
	bRender = true;
	RenderDelta = 1.f;
	CurrentPrintDamage = Damage;
	DamagePosition = std::move(PrintPos);
};

int DamagePont::Update(float fDeltaTime)
{
	CStaticObj::Update(fDeltaTime);
	RenderDelta -= fDeltaTime;
	if (RenderDelta < 0) {
		bRender = false;
	}
	return 0;
}
