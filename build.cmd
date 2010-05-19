@echo off
set PATH=%PATH%;%ProgramFiles(x86)%\Microsoft Visual Studio 9.0\Common7\IDE
devenv logging.sln /Build Release
