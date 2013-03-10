call "%VS100COMNTOOLS%vsvars32.bat"

msbuild.exe ../../Installer/WiX/WinMerge.wixproj /p:Platform=x86
msbuild.exe ../../Installer/WiX/WinMerge.wixproj /p:Platform=x64