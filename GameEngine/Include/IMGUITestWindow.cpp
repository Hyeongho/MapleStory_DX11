#include "IMGUITestWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
//#include "IMGUICheckBox.h"

CIMGUITestWindow::CIMGUITestWindow()
{
}

CIMGUITestWindow::~CIMGUITestWindow()
{
}

bool CIMGUITestWindow::Init()
{
    CIMGUIWindow::Init();

    CIMGUIButton* Button = AddWidget<CIMGUIButton>("Button1");

    Button->SetClickCallback<CIMGUITestWindow>(this, &CIMGUITestWindow::ClickButton1);

    CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");
    Line->SetOffsetX(200.f);
    Line->SetSpacing(100.f);

    Button = AddWidget<CIMGUIButton>("Button2", 100.f, 30.f);

    Button->SetClickCallback<CIMGUITestWindow>(this, &CIMGUITestWindow::ClickButton2);

    CIMGUILabel* Label = AddWidget<CIMGUILabel>("Test", 100.f, 30.f);

    Label->SetColor(255, 0, 0);
    Label->SetAlign(0.5f, 0.f);

    Line = AddWidget<CIMGUISameLine>("Line");

    CIMGUIText* Text = AddWidget<CIMGUIText>("Text", 100.f, 30.f);
    Text->SetText("и旋ぬ纂 褒ぬ");
    Text->SetColor(255, 255, 0);

    CIMGUITextInput* TextInput = AddWidget<CIMGUITextInput>("TextInput", 200.f, 30.f);
    TextInput->SetHideName(true);
    //TextInput->EnablePassword(true);


    CIMGUIListBox* ListBox = AddWidget<CIMGUIListBox>("ListBox", 200.f, 30.f);
    ListBox->SetHideName(true);

    ListBox->AddItem("じ賅");
    ListBox->AddItem("陛種檜");
    ListBox->AddItem("辦種檜");
    ListBox->AddItem("辦種檜1");


    CIMGUIComboBox* ComboBox = AddWidget<CIMGUIComboBox>("ComboBox", 200.f, 30.f);
    ComboBox->SetHideName(true);

    ComboBox->AddItem("じ賅");
    ComboBox->AddItem("陛種檜");
    ComboBox->AddItem("辦種檜");

    for (int i = 0; i < 100; ++i)
    {
        ComboBox->AddItem("辦種檜1");
    }

    CIMGUIImage* Image = AddWidget<CIMGUIImage>("Image", 200.f, 200.f);

    Image->SetTexture("TeemoTest", TEXT("Teemo.jpg"));
    Image->SetImageStart(0.f, 0.f);
    Image->SetImageEnd(1215.f, 717.f);
    Image->SetTint(255, 0, 0);

    return true;
}

void CIMGUITestWindow::Update(float DeltaTime)
{
    CIMGUIWindow::Update(DeltaTime);
}

void CIMGUITestWindow::ClickButton1()
{
    MessageBox(0, TEXT("aa"), TEXT("aa"), MB_OK);
}

void CIMGUITestWindow::ClickButton2()
{
    MessageBox(0, TEXT("bb"), TEXT("bb"), MB_OK);
}
