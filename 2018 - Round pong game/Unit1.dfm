object Form1: TForm1
  Left = 225
  Top = 244
  BiDiMode = bdLeftToRight
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Pong'
  ClientHeight = 620
  ClientWidth = 620
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poDefault
  PrintScale = poNone
  Scaled = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  PixelsPerInch = 120
  TextHeight = 16
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 620
    Height = 620
    Align = alClient
    AutoSize = True
    Stretch = True
  end
  object Shape1: TShape
    Left = 60
    Top = 60
    Width = 500
    Height = 500
    Brush.Style = bsClear
    Pen.Style = psDashDot
    Shape = stCircle
  end
  object Shape2: TShape
    Left = 45
    Top = 295
    Width = 30
    Height = 30
    Brush.Color = clYellow
    Shape = stCircle
  end
  object Shape3: TShape
    Left = 545
    Top = 295
    Width = 30
    Height = 30
    Brush.Color = 13994496
    Shape = stCircle
  end
  object Shape4: TShape
    Left = 285
    Top = 285
    Width = 50
    Height = 50
    Brush.Color = 56797
    Pen.Color = clYellow
    Shape = stCircle
  end
  object Label2: TLabel
    Left = 162
    Top = 380
    Width = 153
    Height = 56
    Alignment = taRightJustify
    AutoSize = False
    Caption = '0 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -53
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object Label3: TLabel
    Left = 330
    Top = 380
    Width = 132
    Height = 56
    AutoSize = False
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -53
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object Button1: TButton
    Left = 160
    Top = 265
    Width = 300
    Height = 90
    Caption = 'Begin'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -43
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 16
    object Game1: TMenuItem
      Caption = 'Game'
      object Mode1: TMenuItem
        Caption = 'Mode'
        object N0Players1: TMenuItem
          Caption = '0 Players'
          OnClick = N0Players1Click
        end
        object N1Player1: TMenuItem
          Caption = '1 Player'
          OnClick = N1Player1Click
        end
        object N2Players1: TMenuItem
          Caption = '2 Players'
          Enabled = False
          OnClick = N2Players1Click
        end
      end
      object Restart1: TMenuItem
        Caption = 'Restart'
        OnClick = Restart1Click
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Settings1: TMenuItem
      Caption = 'Settings'
      object Wallpaper1: TMenuItem
        Caption = 'Wallpaper'
        object None1: TMenuItem
          Caption = 'None'
          OnClick = None1Click
        end
        object Stolenimage11: TMenuItem
          Caption = 'Stolen image 1'
          OnClick = Stolenimage11Click
        end
        object Stolenimage21: TMenuItem
          Caption = 'Stolen image 2'
          OnClick = Stolenimage21Click
        end
        object Stolenimage31: TMenuItem
          Caption = 'Stolen image 3'
          OnClick = Stolenimage31Click
        end
        object Stolenimage41: TMenuItem
          Caption = 'Stolen image 4'
          OnClick = Stolenimage41Click
        end
      end
      object Controls1: TMenuItem
        Caption = 'Controls'
        OnClick = Controls1Click
      end
      object Size1: TMenuItem
        Caption = 'Size'
        OnClick = Size1Click
      end
      object Speed1: TMenuItem
        Caption = 'Speed'
        OnClick = Speed1Click
      end
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 15
    OnTimer = Timer1Timer
    Left = 24
    Top = 248
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 15
    OnTimer = Timer2Timer
    Left = 568
    Top = 256
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 15
    OnTimer = Timer3Timer
    Left = 48
    Top = 16
  end
  object Timer4: TTimer
    Enabled = False
    Interval = 200
    OnTimer = Timer4Timer
    Left = 80
    Top = 16
  end
end
