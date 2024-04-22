object Form3: TForm3
  Left = 819
  Top = 446
  BorderStyle = bsDialog
  Caption = 'Size'
  ClientHeight = 345
  ClientWidth = 610
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  Scaled = False
  OnClose = FormClose
  PixelsPerInch = 120
  TextHeight = 16
  object Shape7: TShape
    Left = 290
    Top = 170
    Width = 160
    Height = 1
    Pen.Color = clSilver
    Pen.Style = psDot
  end
  object Shape6: TShape
    Left = 60
    Top = 60
    Width = 180
    Height = 1
    Pen.Color = clSilver
    Pen.Style = psDot
  end
  object Shape5: TShape
    Left = 115
    Top = 230
    Width = 125
    Height = 1
    Pen.Color = clSilver
    Pen.Style = psDot
  end
  object Shape2: TShape
    Left = 45
    Top = 5
    Width = 30
    Height = 110
    Brush.Color = clYellow
    Shape = stCircle
  end
  object Shape3: TShape
    Left = 160
    Top = 5
    Width = 30
    Height = 110
    Cursor = crSizeNWSE
    Brush.Color = 13994496
    Shape = stCircle
  end
  object Shape4: TShape
    Left = 90
    Top = 120
    Width = 50
    Height = 220
    Brush.Color = 56797
    Pen.Color = clYellow
    Shape = stCircle
  end
  object Shape1: TShape
    Left = 367
    Top = 20
    Width = 167
    Height = 300
    Brush.Style = bsClear
    Pen.Style = psDashDot
    Shape = stCircle
  end
  object Edit1: TEdit
    Left = 240
    Top = 45
    Width = 50
    Height = 31
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Text = '30'
    OnKeyDown = Edit1KeyDown
  end
  object Edit2: TEdit
    Left = 240
    Top = 215
    Width = 50
    Height = 31
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Text = '50'
    OnKeyDown = Edit2KeyDown
  end
  object Edit3: TEdit
    Left = 240
    Top = 155
    Width = 50
    Height = 31
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Text = '500'
    OnKeyDown = Edit3KeyDown
  end
end
