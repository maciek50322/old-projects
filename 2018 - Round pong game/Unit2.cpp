//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
WORD lu1=90, ld1=88, ru1=37, rd1=39;
AnsiString inc, pre;
int chn=0;

void TForm2::doundo() {
if (chn==1){
        Label1->Caption=pre;
}
if (chn==2){
        Label2->Caption=pre;
}
if (chn==3){
        Label3->Caption=pre;
}
if (chn==4){
        Label4->Caption=pre;
}
chn=0;
}

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
       if ((Key>=37 && Key<=40) || (Key>=65 && Key<=90) || (Key>=48 && Key<=57)){
        if (Key==37) inc='<';
        else if (Key==38) inc='^';
        else if (Key==39) inc='>';
        else if (Key==40) inc='v';
        else inc=(char)Key;
        if (lu1==Key || ld1==Key || ru1==Key || rd1==Key) {
                if (chn==1) {
                        Label1->Caption=pre;
                }
                else if (chn==2) {
                        Label2->Caption=pre;
                }
                else if (chn==3) {
                        if (Label5->Height!=0 && (lu1==Key || ld1==Key)) {
                                if (lu1==Key) {
                                        lu1=ru1;
                                        ru1=Key;
                                        Label3->Caption=Label1->Caption;
                                        Label1->Caption=pre;
                                }
                                if (ld1==Key) {
                                        ld1=ru1;
                                        ru1=Key;
                                        Label3->Caption=Label2->Caption;
                                        Label2->Caption=pre;
                                }
                        } else Label3->Caption=pre;
                }
                else if (chn==4) {
                        if (Label5->Height!=0 && (lu1==Key || ld1==Key)) {
                                if (lu1==Key) {
                                        lu1=rd1;
                                        rd1=Key;
                                        Label4->Caption=Label1->Caption;
                                        Label1->Caption=pre;
                                }
                                if (ld1==Key) {
                                        ld1=rd1;
                                        rd1=Key;
                                        Label4->Caption=Label2->Caption;
                                        Label2->Caption=pre;
                                }
                        } else Label4->Caption=pre;
                }

                chn=0;
        }
        switch (chn) {
        case 1: Label1->Caption=inc;
                lu1=Key;
                break;
        case 2: Label2->Caption=inc;
                ld1=Key;
                break;
        case 3: Label3->Caption=inc;
                ru1=Key;
                break;
        case 4: Label4->Caption=inc;
                rd1=Key;
                break;
        }
        chn=0;
       }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
        if (chn!=0)
        doundo();
        Form1->SetControls(lu1, ld1, ru1, rd1);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label1Click(TObject *Sender)
{
        if (chn!=0)
        doundo();
                chn=1;
                pre=Label1->Caption;
                Label1->Caption="---";

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label2Click(TObject *Sender)
{
        if (chn!=0)
        doundo();
                chn=2;
                pre=Label2->Caption;
                Label2->Caption="---";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label3Click(TObject *Sender)
{
        if (chn!=0)
        doundo();
                chn=3;
                pre=Label3->Caption;
                Label3->Caption="---";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label4Click(TObject *Sender)
{
        if (chn!=0)
        doundo();
                chn=4;
                pre=Label4->Caption;
                Label4->Caption="---";
}
//---------------------------------------------------------------------------
