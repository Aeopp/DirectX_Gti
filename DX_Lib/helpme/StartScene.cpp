#include "StartScene.h"
#include "UIButton.h"
#include "UIPanel.h"
#include "Camera.h"
#include "Layer.h"
#include "Pixel.h" 
#include "CCore.h"
#include "Collision/ColinderRect.h"
#include "CAnimation.h"
#include "CSceneManager.h"
#include "CIngameScene.h"

CStartScene::CStartScene()
{
};

CStartScene::~CStartScene()
{
}
void CStartScene::Render(HDC hDC, float fDeltaTime)
{
    CScene::Render(hDC, fDeltaTime);
    //
    //for (auto& UI: UIs) {
    //    // 사용자가 버튼을 눌렀다면
    //    UI->m_pAnimation->ChangeClip(L"StartButton");
    //    UI->m_pAnimation->SetDefaultClip(L"StartButton");
    //}
};

bool CStartScene::Init()
{
    if (!CScene::Init())
        return false; 

    CLayer* pLayer = FindLayer(L"UI");

	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>(L"BackPanel", pLayer);

    pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
    pBackPanel->SetTexture(L"StartBack",
     L"StartBack.bmp");

    SAFE_RELEASE(pBackPanel);

    CUIButton* pStartBtn= CObj::CreateObj<CUIButton>(L"EndButton", pLayer);

    pStartBtn->SetPos(GETRESOLUTION.iW / 2 -
        350, GETRESOLUTION.iH / 2 - 100);
    pStartBtn->SetSize(300, 200);
    pStartBtn->SetTexture(L"EndButton",
        L"StartButton.bmp");
    pStartBtn->SetColorKey(255, 0, 255);
    pStartBtn->bBorder = false;


    pStartBtn->SetCallback(this,
        &CStartScene::StartButtonCallback);


    SAFE_RELEASE(pStartBtn);

        return true;
}

void CStartScene::StartButtonCallback(float fTime)
{
    GET_SINGLE(CSceneManager)->CreateScene<CIngameScene>(SC_NEXT);
}

void CStartScene::EndButtonCallback(float fTime)
{
    GET_SINGLE(CCore)->DestroyGame();
}
