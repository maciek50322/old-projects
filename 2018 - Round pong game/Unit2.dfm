object Form2: TForm2
  Left = 804
  Top = 249
  BorderStyle = bsDialog
  Caption = 'Controls'
  ClientHeight = 150
  ClientWidth = 310
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
  OnKeyDown = FormKeyDown
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 20
    Top = 20
    Width = 90
    Height = 45
    Alignment = taCenter
    AutoSize = False
    Caption = 'Z'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -40
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    OnClick = Label1Click
  end
  object Label2: TLabel
    Left = 200
    Top = 20
    Width = 90
    Height = 45
    Alignment = taCenter
    AutoSize = False
    Caption = 'X'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -40
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    OnClick = Label2Click
  end
  object Label3: TLabel
    Left = 20
    Top = 85
    Width = 90
    Height = 45
    Alignment = taCenter
    AutoSize = False
    Caption = '<'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -40
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    OnClick = Label3Click
  end
  object Label4: TLabel
    Left = 200
    Top = 85
    Width = 90
    Height = 45
    Alignment = taCenter
    AutoSize = False
    Caption = '>'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -40
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    OnClick = Label4Click
  end
  object Shape2: TShape
    Left = 140
    Top = 32
    Width = 30
    Height = 30
    Brush.Color = clYellow
    Shape = stCircle
  end
  object Shape3: TShape
    Left = 140
    Top = 92
    Width = 30
    Height = 30
    Brush.Color = 13994496
    Shape = stCircle
  end
  object Label5: TLabel
    Left = 16
    Top = 20
    Width = 275
    Height = 0
    Alignment = taCenter
    AutoSize = False
    Caption = 'CPU'
    Color = clYellow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -43
    Font.Name = 'Arial'
    Font.Style = [fsItalic]
    ParentColor = False
    ParentFont = False
  end
end