@echo off
pushd %~dp0\
call windows\premake5.exe vs2019
popd
PAUSE