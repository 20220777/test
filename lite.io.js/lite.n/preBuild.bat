@echo off

@set PLATFORMTARGET=%1


if not exist ..\..\usr\out mkdir ..\..\usr\out

@copy /Y ..\..\lite.io\%PLATFORMTARGET%\*%PLATFORMTARGET%.*                ..\..\usr\out
