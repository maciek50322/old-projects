//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
double d1=30, d2=50, d3=500;
WORD enter=VK_RETURN;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key==VK_RETURN) {
        for (int i=0;i<Edit1->Text.Length();i++) {
                if (Edit1->Text.c_str()[i]<'0' || Edit1->Text.c_str()[i]>'9'){
                        Edit1->Text=d1;
                        break;
                }
        }
        if (Edit1->Text.ToInt()<20) Edit1->Text="20";
        if (Edit1->Text.ToInt()>100) Edit1->Text="100";
                Shape2->Width=Edit1->Text.ToInt();
                Shape3->Width=Edit1->Text.ToInt();
                Shape2->Left=60-Shape2->Width/2;
                Shape3->Left=175-Shape3->Width/2;
        d1=Edit1->Text.ToInt();
        if (d3<d1+d2+40) {
                d3=d1+d2+40;
                Edit3->Text=d3;
                Edit3KeyDown(Sender, enter , Shift);
        }
        Form1->Shape2->Left=Form1->Shape2->Left+Form1->Shape2->Width/2-Edit1->Text.ToInt()/2;
        Form1->Shape2->Top=Form1->Shape2->Top+Form1->Shape2->Height/2-Edit1->Text.ToInt()/2;
        Form1->Shape2->Width=Edit1->Text.ToInt();
        Form1->Shape2->Height=Edit1->Text.ToInt();
        Form1->Shape3->Left=Form1->Shape3->Left+Form1->Shape3->Width/2-Edit1->Text.ToInt()/2;
        Form1->Shape3->Top=Form1->Shape3->Top+Form1->Shape3->Height/2-Edit1->Text.ToInt()/2;
        Form1->Shape3->Width=Edit1->Text.ToInt();
        Form1->Shape3->Height=Edit1->Text.ToInt();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Edit2KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key==VK_RETURN) {
        for (int i=0;i<Edit2->Text.Length();i++) {
                if (Edit2->Text.c_str()[i]<'0' || Edit2->Text.c_str()[i]>'9'){
                        Edit1->Text=d1;
                        break;
                }
        }
        if (Edit2->Text.ToInt()<20) Edit2->Text="20";
        if (Edit2->Text.ToInt()>200) Edit2->Text="200";
                Shape4->Width=Edit2->Text.ToInt();
                Shape4->Left=115-Shape4->Width/2;
        d2=Edit2->Text.ToInt();
        if (d3<d1+d2+40) {
                d3=d1+d2+40;
                Edit3->Text=d3;
                Edit3KeyDown(Sender, enter , Shift);
        }
        Form1->Shape4->Left=Form1->Shape4->Left+Form1->Shape4->Width/2-Edit2->Text.ToInt()/2;
        Form1->Shape4->Top=Form1->Shape4->Top+Form1->Shape4->Height/2-Edit2->Text.ToInt()/2;
        Form1->Shape4->Width=Edit2->Text.ToInt();
        Form1->Shape4->Height=Edit2->Text.ToInt();

        }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Edit3KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key==VK_RETURN) {
        for (int i=0;i<Edit3->Text.Length();i++) {
                if (Edit3->Text.c_str()[i]<'0' || Edit3->Text.c_str()[i]>'9'){
                        Edit1->Text=d1;
                        break;
                }
        }
        if (Edit3->Text.ToInt()<d1+d2+40) Edit3->Text=d1+d2+40;
        if (Edit3->Text.ToInt()<300) Edit3->Text="300";
        if (Edit3->Text.ToInt()>900) Edit3->Text="900";
                Shape1->Width=Edit3->Text.ToInt()/3;
                Shape1->Left=450-Shape1->Width/2;
        d3=Edit3->Text.ToInt();
        Form1->px=Form1->px*Edit3->Text.ToInt()/Form1->Shape1->Width;
        Form1->py=Form1->py*Edit3->Text.ToInt()/Form1->Shape1->Height;
        Form1->Shape1->Width=Edit3->Text.ToInt();
        Form1->Shape1->Height=Edit3->Text.ToInt();
        Form1->Shape4->Left=Form1->px+Form1->Shape1->Left-Form1->Shape4->Width/2;
        Form1->Shape4->Top=Form1->py+Form1->Shape1->Left-Form1->Shape4->Height/2;
        Form1->Shape3->Left=Form1->Shape1->Width/2+Form1->Shape1->Left-Form1->Shape3->Width/2-cos(Form1->pos2)*Form1->Shape1->Width/2;
        Form1->Shape3->Top=Form1->Shape1->Height/2+Form1->Shape1->Top-Form1->Shape3->Height/2-sin(Form1->pos2)*Form1->Shape1->Height/2;
        Form1->Shape2->Left=Form1->Shape1->Width/2+Form1->Shape1->Left-Form1->Shape2->Width/2-cos(Form1->pos1)*Form1->Shape1->Width/2;
        Form1->Shape2->Top=Form1->Shape1->Height/2+Form1->Shape1->Top-Form1->Shape2->Height/2-sin(Form1->pos1)*Form1->Shape1->Height/2;
        Form1->ClientHeight=Edit3->Text.ToInt()+120;
        Form1->ClientWidth=Edit3->Text.ToInt()+120;
        Form1->Button1->Top=Form1->Shape1->Top+Form1->Shape1->Height/2-Form1->Button1->Height/2;
        Form1->Button1->Left=Form1->Shape1->Left+Form1->Shape1->Width/2-Form1->Button1->Width/2;
        Form1->Label2->Left=Form1->Button1->Left+2;
        Form1->Label2->Top=Form1->Button1->Top+115;
        Form1->Label3->Top=Form1->Label2->Top;
        Form1->Label3->Left=Form1->Button1->Left+Form1->Button1->Width-Form1->Label3->Width+2;
        Form1->Image1->Align=alClient;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
        TShiftState Shift;
        Edit1KeyDown(Sender, enter, Shift);
        Edit2KeyDown(Sender, enter, Shift);
        Edit3KeyDown(Sender, enter, Shift);
}
//---------------------------------------------------------------------------

