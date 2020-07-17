
; ------------------------------------------------------------------------

; Incluir el archivo para la interfaz nueva
!include "MUI2.nsh"

; ------------------------------------------------------------------------

;General

!define CompanyName "FrostDisk"
!define ProductName "El Escape de Lugh"
!define ProductCaption "El Escape de Lugh"
!define ProductVersion "1.0.1"
!define WebsiteUrl "http://www.frostdisk.com/projects/lugh"

!define SetupFile "LughEscape-Setup.exe"
!define BinaryFile "Lugh.exe" 
!define LicenseFile "license.txt"
; !define NoteFile "README.txt"

;Files

!define InstallFiles "Files.nsi"
; !define UnistallFiles "Unfiles.nsi"

!define InstallerIcon "icono.ico"
!define UninstallerIcon "unicono.ico"

 
;Global Values
!define srcdir "."
!define regkey "Software\${CompanyName}\${ProductName}"
!define uninstkey "Software\Microsoft\Windows\CurrentVersion\Uninstall\${ProductName}"
 
!define startmenu "$SMPROGRAMS\${CompanyName}\${ProductName}"
!define uninstaller "uninstall.exe"

;Configuration

Name "${ProductName}"
OutFile "${SetupFile}"


InstallDir "$PROGRAMFILES\${CompanyName}\${ProductName}"
InstallDirRegKey HKLM "${regkey}" ""
RequestExecutionLevel admin
 
!ifdef LicenseFile
LicenseText "License"
LicenseData "${srcdir}\${LicenseFile}"
!endif


; ------------------------------------------------------------------------

; Iconos
!define MUI_ICON "${srcdir}\${InstallerIcon}"
!define MUI_UNICON "${srcdir}\${UninstallerIcon}"


; Cabecera
!define MUI_HEADERIMAGE
	!define MUI_HEADERIMAGE_BITMAP "${srcdir}\header.bmp"
	!define MUI_HEADERIMAGE_UNBITMAP "${srcdir}\unheader.bmp"

!define MUI_BGCOLOR "FFFFFF"

; Imagenes
!define MUI_WELCOMEFINISHPAGE_BITMAP "${srcdir}\win.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "${srcdir}\unwin.bmp"

; Iconos
!define MUI_COMPONENTSPAGE_CHECKBITMAP "${srcdir}\modern.bmp"

;Interface Settings

!define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
!ifdef LicenseFile
  !insertmacro MUI_PAGE_LICENSE "${srcdir}\${LicenseFile}"
!endif
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;Language Selection Dialog Settings

  ;Remember the installer language
  !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
  !define MUI_LANGDLL_REGISTRY_KEY "${regkey}" 
  !define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"


  !insertmacro MUI_LANGUAGE "SpanishInternational"  ;first language is the default language
  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "Spanish"


!insertmacro MUI_RESERVEFILE_LANGDLL

;Installer Functions

Function .onInit

  !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd


; beginning (invisible) section
Section 
 
  WriteRegStr HKLM "${regkey}" "Install_Dir" "$INSTDIR"
  WriteRegStr HKLM "${uninstkey}" "InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "${uninstkey}" "DisplayName" "${ProductName}"
  WriteRegStr HKLM "${uninstkey}" "DisplayIcon" "$INSTDIR\${uninstaller}"
  WriteRegStr HKLM "${uninstkey}" "UninstallString" "$INSTDIR\${uninstaller}"
  WriteRegStr HKLM "${uninstkey}" "Publisher" "${CompanyName}"

!ifdef WebsiteUrl
  WriteRegStr HKLM "${uninstkey}" "URLInfoAbout" "${WebsiteUrl}"
!endif

!ifdef ProductVersion
  WriteRegStr HKLM "${uninstkey}" "DisplayVersion" "${ProductVersion}"
!endif
 
!ifdef filetype
  WriteRegStr HKCR "${filetype}" "" "${ProductName}"
!endif
 
  WriteRegStr HKCR "${ProductName}\Shell\open\command\" "" "$INSTDIR\${BinaryFile} %1"
 
!ifdef IconFile
  WriteRegStr HKCR "${ProductName}\DefaultIcon" "" "$INSTDIR\${IconFile}"
!endif
 
  SetOutPath $INSTDIR
 
 
; package all files, recursively, preserving attributes
; assume files are in the correct places
File /a "${srcdir}\${BinaryFile}"
 
!ifdef licensefile
File /a "${srcdir}\${LicenseFile}"
!endif
 
!ifdef NoteFile
File /a "${srcdir}\${NoteFile}"
!endif
 
!ifdef IconFile
File /a "${srcdir}\${IconFile}"
!endif
 
; any application-specific files
!ifdef InstallFiles
!include "${InstallFiles}"
!endif
 
  WriteUninstaller "${uninstaller}"
 
SectionEnd



Section "${ProductName}"
 
  CreateDirectory "${startmenu}"
  SetOutPath $INSTDIR ; for working directory
!ifdef IconFile
  CreateShortCut "${startmenu}\${ProductName}.lnk" "$INSTDIR\${BinaryFile}" "" "$INSTDIR\${IconFile}"
!else
  CreateShortCut "${startmenu}\${ProductName}.lnk" "$INSTDIR\${BinaryFile}"
!endif
 
!ifdef NoteFile
  CreateShortCut "${startmenu}\LEEME.txt.lnk "$INSTDIR\${NoteFile}"
!endif
 
!ifdef helpfile
  CreateShortCut "${startmenu}\Documentacion.lnk "$INSTDIR\${helpfile}"
!endif
 
!ifdef WebsiteUrl
WriteINIStr "${startmenu}\pagina web.url" "InternetShortcut" "URL" ${WebsiteUrl}
 ; CreateShortCut "${startmenu}\Web Site.lnk "${website}" "URL"
!endif
 
!ifdef NoteFile
ExecShell "open" "$INSTDIR\${NoteFile}"
!endif
 
SectionEnd



Section "Uninstall"
 
  DeleteRegKey HKLM "${uninstkey}"
  DeleteRegKey HKLM "${regkey}"
 
  Delete "${startmenu}\*.*"
  Delete "${startmenu}"
 
!ifdef LicenseFile
Delete "$INSTDIR\${LicenseFile}"
!endif
 
!ifdef NoteFile
Delete "$INSTDIR\${NoteFile}"
!endif
 
!ifdef icon
Delete "$INSTDIR\${IconFile}"
!endif
 
Delete "$INSTDIR\${BinaryFile}"
 
!ifdef unfiles
!include "${unfiles}"
!endif

Delete "$INSTDIR\${uninstaller}"

Delete "$PROGRAMFILES\${CompanyName}\${ProductName}\*.*"
Delete "$PROGRAMFILES\${CompanyName}\${ProductName}"
Delete "$PROGRAMFILES\${CompanyName}"

SectionEnd