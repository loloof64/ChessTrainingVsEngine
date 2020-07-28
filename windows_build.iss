; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define IconName "chess.ico"
#define OutputDir "release"
#define SourcePath "C:\projects\chesstrainingvsengine"
#define BuildPath "C:\projects\chesstrainingvsengine\release"
#define MyAppName "Chess Training Vs Engine"
#define MyAppVersion "0.1.46"
#define MyAppPublisher "loloof64"
#define MyAppURL "https://github.com/loloof64/ChessTrainingVsEngine"
#define MyAppExeName "ChessTrainingVsEngine.exe"
#define MinGWBinPath "C:\msys64\mingw64\bin"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{618786A3-6C60-446F-9FD6-969E40BBC890}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
LicenseFile="{#SourcePath}\LICENSE.txt"
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=dialog
OutputDir="{#OutputDir}"
OutputBaseFilename=ChessTrainingVsEngine
SetupIconFile="{#SourcePath}/{#IconName}"
Compression=lzma
SolidCompression=yes
WizardStyle=modern
ArchitecturesInstallIn64BitMode=x64
UninstallDisplayIcon="{#SourcePath}\{#IconName}"

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#BuildPath}\*"; DestDir: "{app}"; Flags: recursesubdirs
Source: "{#SourcePath}\{#IconName}"; DestDir: "{app}"


; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#IconName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#IconName}"; Tasks: desktopicon
