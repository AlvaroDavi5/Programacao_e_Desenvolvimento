Attribute VB_Name = "ExtensoACD"
'Macro:         ACD_Extenso
'Vers?o:        3.2 (?ltima atualiza??o 03/02/2021)
'Finalidade:    Converte um valor num?rico em uma string
'               com o extenso monet?rio correspondente.
'Linguagem:     VBA
'Autor:         Antonio Carlos Don?
'               acdona@hotmail.com
'Distribui??o:  Livre e sem garantias, use por sua conta e risco.
'Observa??es:   1) Sempre deixar um espa?o em branco no in?cio
'                  do n?mero a ser convertido para extenso.
'               2) Favor reportar eventuais bugs.
'               3) Suporta valores at? $922.337.203.685.477,5807 que ? o limite
'                  da vari?vel Currency -922.337.203.685.477,5808 at? 922.337.203.685.477,5807
'               4) N?o foi feito nenhum teste com valores negativos
'
'Gram?tica portuguesa:
'Regra Geral: N?o se intercala a conjun??o 'e' e nem v?rgula entre posi??es de milhar.
'Exce??o: Se a milhar posterior for menor que 100 ou for centena inteira (Ex: 100,200,300...)
'Alguns gram?ticos n?o aceitam essa exce??o e outros j? aceitam a v?rgula.
'Nota: Segundo diversos gram?ticos nunca dever? ser usada a v?rgula na escrita de numerais por extenso.
'<-------------------------------------------------------------------------------------------------------
'In?cio da rotina ACD_Extenso()
Sub ACD_Extenso()
'Verifica se houve erro e pulo para Fim:
On Error GoTo Fim_Err
'declara as vari?veis
  Dim strValor As String        'alfanum?rico
  Dim strRetorno As String      'alfanum?rico
  Dim blnNoInicio As Boolean    'Falso/Verdadeiro
  Dim strTmp As String          'alfanum?rico
  Dim x As Integer              'inteiro
  Dim InicioExtenso As String   'Alfanum?rico
  Dim FimExtenso As String      'Alfanum?rico
  '
  'atribui os parenteses no in?cio e final do extenso
  'caso n?o queira nada antes ou depois do extenso alterar para ""
  InicioExtenso = " ("
  FimExtenso = ") "
  '
  'Verifica se n?o existe algo selecionado
  'atribui Verdadeiro para blnInicio e sai da macro
  If Selection.Type = wdSelectionIP And Selection.Start = 0 Then blnNoInicio = True
  If blnNoInicio = True Then Exit Sub
  '
  'Move para esquerda
  'unit = por caracter
  'count = um por vez
  'Extend = move para o final do n?mero extendido
  Selection.MoveLeft Unit:=wdCharacter, Count:=1, Extend:=wdExtend
  'quando achar um espa?o em branco no in?clio do n?mero selecionado
  While Selection.Text = " "
    'se chegou no in?cio do documento e n?o achou espa?o sai da macro
    If WordBasic.AtStartOfDocument() Then Exit Sub
      'volta onde estava sem marcar nada
      Selection.ExtendMode = False
      'Move para esquerda
      'unit = por caracter
      'count = um por vez
      'Extend = move para final do n?mero e pula para esquerda
      Selection.MoveLeft Unit:=wdCharacter, Count:=1, Extend:=wdMove
  Wend
  'volta para direita selecionando todo o n?mero
  Selection.MoveRight Unit:=wdCharacter, Count:=1, Extend:=wdMove
  Selection.ExtendMode = True
  'procura na sele??o
  With Selection.Find
      'em dire??o ao in?cio
      .Forward = False
      'quando encontrar o fim, para.
      .Wrap = wdFindStop
      'procura o espa?o em branco
      .Execute FindText:=" "
  End With
  'exibe texto na janela imediata
  Debug.Print Selection.Text
  'atribui texto selecionado ? macro
  'o CCur ? para transformar de texto para monet?rio
  strValor = Extenso(CCur(Selection.Text))
  'desmarca sele??o
  Selection.ExtendMode = False
  'volta para direita um caracter
  Selection.MoveRight Unit:=wdCharacter, Count:=1, Extend:=wdMove
  'caso queira tudo em min?scula, tire o UCASE abaixo 
  strTmp = InicioExtenso & strValor & FimExtenso
  'verifica se o valor atribu?do tem mais de um caracter
  'ou se ? diferente de espa?o
  'Escreve o valor por extenso a direita do n?mero digitado
  x = Len(strTmp)
  If x > 0 And strTmp <> " " Then
     Selection.TypeText Text:=strTmp
   End If
'Rotina para sair da macro
Fim_Err:
'retira sele??o e vai para o final do extenso
Selection.ExtendMode = False
Selection.MoveRight Unit:=wdCharacter, Count:=1, Extend:=wdMove
   Exit Sub
End Sub
'Final da torina ACD_Extenso()
'------------------------------------------------------------------------------------------------------->
'
' Fun??o extenso, respons?vel por converter o n?mero em extenso
'
Function Extenso( _
  Valor As Currency, _
  Optional MoedaNoSingular As String = "real", _
  Optional MoedaNoPlural As String = "reais", _
  Optional CentavosNoSingular As String = "centavo", _
  Optional CentavosNoPlural As String = "centavos") _
As String
  
    Dim ParteInteira As Currency, ParteDecimal As Long
    Dim s As String
    
    ParteInteira = Fix(Valor)
    ParteDecimal = Fix((Valor - ParteInteira) * 100)
    
    s = ""
  
    If ParteInteira = 0 Then
    
        If ParteDecimal > 0 Then
            If ParteDecimal = 1 Then
              s = s & "um " & CentavosNoSingular & " de " & MoedaNoSingular
            Else
              s = s & Centena(ParteDecimal) & " " & CentavosNoPlural & " de " & MoedaNoSingular
            End If
        End If
        Extenso = s
        Exit Function
    
    End If
  
    If ParteInteira > 0 Then
      
      s = ConcatCentenas(ParteInteira)
      If s = "um" Then
        s = s & " " & MoedaNoSingular
      Else
        s = s & " " & MoedaNoPlural
      End If
      If ParteDecimal > 0 Then
        s = s & " e "
      End If
      
    End If
  
    If ParteDecimal > 0 Then
      If ParteDecimal = 1 Then
        s = s & "um " & CentavosNoSingular
      Else
        s = s & Centena(ParteDecimal) & " " & CentavosNoPlural
      End If
    End If

    Extenso = s

End Function

Function Resto(A As Currency, B As Long) As Currency
  Dim Aux As String, r As Currency
  Aux = Format(A / B, "###0.0000")
  Aux = Right$(Aux, 4)
  Resto = Aux * B / 10000
  If Resto < 1 And Resto > 0.99 Then
    Resto = 1
  End If
  Aux = Format(Resto, "###0.0000")
  Aux = Right$(Aux, 4)
  Resto = Resto - Aux / 10000
End Function

Function DivInt(A As Currency, B As Long) As Currency
  Dim Aux As String
  DivInt = A / B
  Aux = Format(DivInt, "###0.0000")
  Aux = Right$(Aux, 4)
  DivInt = DivInt - Aux / 10000
End Function

Private Function Unidade(N As Long) As String
    Dim varUnidade As Variant
    varUnidade = Array("", "um", "dois", "tr?s", "quatro", "cinco", "seis", "sete", "oito", "nove")
    Unidade = varUnidade(N)
End Function

Private Function Dezena(N As Long) As String
    Dim d As Long, u As Long
    Dim s As String
    Dim varDezena1 As Variant, varDezena2 As Variant
    
    varDezena1 = Array("dez", "onze", "doze", "treze", "quatorze", _
                      "quinze", "dezesseis", "dezessete", "dezoito", _
                      "dezenove")
    
    varDezena2 = Array("vinte", "trinta", "quarenta", "cinquenta", _
                       "sessenta", "setenta", "oitenta", "noventa")
                      
    d = N \ 10   '\ divide 2 numeros e retorna o resultado inteiro
    u = N Mod 10 'mod retorna o resto da divis?o

If d = 0 Then
    Dezena = Unidade(N)
    Exit Function
Else
    If d = 1 And u = 0 Then
        Dezena = varDezena1(0)
        Exit Function
    
    End If
    If d = 1 And u > 0 Then
        Dezena = varDezena1(u)
        Exit Function
    End If
End If

If d > 1 Then '-> alterado para arrumar as centenas
    If u = 0 Then
        Dezena = varDezena2(d - 2) & Unidade(u)
        Else
        Dezena = varDezena2(d - 2) & " e " & Unidade(u)
    End If
End If

End Function

Private Function Centena(N As Long) As String
  Dim c As Long, d As Long
  Dim s As String
  Dim varCentena As Variant
  
  varCentena = Array("duzentos", "trezentos", "quatrocentos", "quinhentos", _
                     "seiscentos", "setecentos", "oitocentos", "novecentos")
                     
  c = N \ 100
  d = N Mod 100
  
  If c = 0 Then
    Centena = Dezena(N)
    Exit Function
  End If
  
  If c = 1 Then
    If d = 0 Then
        Centena = "cem"
    Else
        Centena = "cento e " & Dezena(d)
    End If
    Exit Function
  End If
  
  If d = 0 Then
    Centena = varCentena(c - 2)
  Else
    Centena = varCentena(c - 2) & " e " & Dezena(d)
  End If
End Function

Private Function SingleAlg(N As Currency) As Boolean
  Dim s As String, i As Integer
  s = N
  SingleAlg = False
  For i = 1 To Len(s)
    If Mid$(s, i, 1) <> 0 Then
      If SingleAlg Then
        SingleAlg = False
        Exit Function
      Else
        SingleAlg = True
      End If
    End If
  Next i
End Function

Private Function ConcatCentenas(N As Currency) As String
  Dim Trilhao As Long, Bilhao As Long, _
    Milhao As Long, Milhar As Long, Um As Long, _
    Menores As Integer
  Dim TiraUmMil As Boolean
  Dim s As String, m As Currency
  
  TiraUmMil = True 'Escolha do Mil (True=Mil False=Um Mil)
  
  s = ""
  m = N
  
  Um = Resto(N, 1000)      'Um = N Mod 1000
  N = DivInt(N, 1000)      'N = N \ 1000
  Milhar = Resto(N, 1000)  'Milhar = N Mod 1000
  N = DivInt(N, 1000)      'N = N \ 1000
  Milhao = Resto(N, 1000)  'Milhao = N Mod 1000
  N = DivInt(N, 1000)      'N = N \ 1000
  Bilhao = Resto(N, 1000)  'Bilhao = N Mod 1000
  N = DivInt(N, 1000)      'N = N \ 1000
  Trilhao = Resto(N, 1000) 'Trilhao = N Mod 1000000000

  m = m - Trilhao * 1000000000000@
  Menores = Bilhao + Milhao + Milhar + Um
  If Trilhao > 0 Then
    If Trilhao = 1 Then
      s = "um trilh?o"
    Else
      s = Centena(Trilhao) & " trilh?es"
    End If
    If Menores > 0 Then
      If SingleAlg(m) Then
        s = s & " e "
      Else
        's = s & ", " 'retirada das v?rgulas
        s = s & " "
    End If
    Else
      s = s & " de"
    End If
  End If
  
  m = m - Bilhao * 1000000000@
  Menores = Milhao + Milhar + Um
  If Bilhao > 0 Then
    If Bilhao = 1 Then
      s = s & "um bilh?o"
    Else
      s = s & Centena(Bilhao) & " bilh?es"
    End If
    If Menores > 0 Then
      If SingleAlg(m) Then
        s = s & " e "
      Else
        's = s & ", " 'retirada da v?rgula
        s = s & " "
      End If
    Else
      s = s & " de"
    End If
  End If
  
  m = m - Milhao * 1000000
  Menores = Milhar + Um
  If Milhao > 0 Then
    If Milhao = 1 Then
      s = s & "um milh?o"
    Else
        s = s & Centena(Milhao) & " milh?es"
    End If
    If Menores > 0 Then
      If SingleAlg(m) Then
        s = s & " e "
      Else
        '       s = s & ", " 'retirada da v?rgula do milhar
       s = s & " "
      End If
    Else
      s = s & " de"
    End If
  End If
  
  m = -(Milhar * 1000) + m
  Menores = Um
  If Milhar > 0 Then
  
    s = s & Centena(Milhar) & " mil "
    'Verifica se quer "um mil" ou "mil
    If TiraUmMil Then
        If Left$(s, 7) = "um mil " Then s = Mid$(s, 4)
    End If

    If Menores > 0 Then
      If SingleAlg(m) Then
        s = s & "e "
      Else
       ' s = s & ", " '->Retirada da v?gula no milhar
      End If
    End If
  End If
  s = s & Centena(Um)
  ConcatCentenas = s
End Function
'fim da fun??o ACD_Extenso
