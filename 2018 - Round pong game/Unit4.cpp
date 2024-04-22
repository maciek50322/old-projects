//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit4.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
double p=0, q=1;
const long double pi=3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798;

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
        p+=Form1->speedthing;
        if (p<0) p-=2*pi;
        if (p>2*pi) p+=2*pi;
        Shape2->Left=Shape1->Left+Shape1->Width/2-Shape2->Width/2+cos(p)*Shape1->Width/2;
        Shape2->Top=Shape1->Top+Shape1->Height/2-Shape2->Height/2+sin(p)*Shape1->Height/2;

        Shape3->Left=Shape3->Left+q*Form1->ppc;
        if (Shape3->Left<=Shape1->Left) q=1;
        else if (Shape3->Left+Shape3->Width>=Shape1->Width+Shape1->Left) q=-1;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormCreate(TObject *Sender)
{
        DoubleBuffered=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::TrackBar1Change(TObject *Sender)
{
        Form1->speedthing=pi/500*(TrackBar1->Max+1-TrackBar1->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::TrackBar2Change(TObject *Sender)
{
        Form1->ppc=TrackBar2->Max+1-TrackBar2->Position;
}
//---------------------------------------------------------------------------
