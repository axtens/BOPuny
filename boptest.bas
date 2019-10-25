Attribute VB_Name = "Module1"
Declare Function ToPunyCode Lib "Debug\bop.dll" (ByVal utfLen As Long, utf16 As Long, punycode As Byte, pLen As Long) As Long
Declare Function FromPunyCode Lib "Debug\bop.dll" (ByVal pLen As Long, punycode As Byte, utf16 As Long, utfLen As Long) As Long

Dim oFSO As Scripting.FileSystemObject
Dim oStr As Scripting.TextStream

Sub Main()
    Dim p As New PerlLibrary_TypeLib.PerlLibrary
    Dim oFSO As New Scripting.FileSystemObject
    Dim oStrInput As Scripting.TextStream
    Dim oStrOutput As Scripting.TextStream
    
    Set oStrInput = oFSO.OpenTextFile("boptest.txt", ForReading, False, TristateTrue)
    Set oStrOutput = oFSO.CreateTextFile("boptest.out", True, True)
    
    Dim sPLPuny As String
    Dim sPLUnpuny As String
    Dim sBOPuny As String
    Dim sBOUnpuny As String
    
    Dim sString As String
    Dim i As Integer
    Dim punycode() As Byte
    Dim punyLen As Long
    Dim lBOUnpuny As Long
    oStrOutput.WriteLine "String" & vbTab & "enBOP --> deBOP" & vbNewLine & vbTab & "enBOPL --> deBOPL"
    Do While Not oStrInput.AtEndOfStream
        sString = oStrInput.ReadLine
        sPLPuny = p.EnPunyCode(sString)
        ReDim punycode(Len(sString) * 10)
        i = ToPunyCode(Len(sString), StrPtr(sString), punycode(0), punyLen)
        Debug.Print punyLen
        sBOPuny = punycode
        sBOPuny = LeftB$(sBOPuny, punyLen)
        sBOPuny = StrConv(sBOPuny, vbUnicode)
        sPLUnpuny = p.DePunyCode(sPLPuny)
        sBOUnpuny = Space$(255)
        i = FromPunyCode(punyLen, punycode(0), StrPtr(sBOUnpuny), lBOUnpuny)
        sBOUnpuny = Left$(sBOUnpuny, lBOUnpuny)
        oStrOutput.WriteLine sString & vbTab & sBOPuny & " --> " & sBOUnpuny & vbNewLine & vbTab & sPLPuny & " --> " & sPLUnpuny
    Loop
    
    oStrInput.Close
    oStrOutput.Close

End Sub
