//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TEdit *Edit1;
        TEdit *Edit2;
        TShape *Shape1;
        TEdit *Edit3;
        TShape *Shape5;
        TShape *Shape6;
        TShape *Shape7;
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit2KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit3KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
