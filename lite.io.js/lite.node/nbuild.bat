@echo off

@set PLATFORMTARGET=%1

if "%PLATFORMTARGET%"=="" GOTO END

if not exist then mkdir coms
if not exist then mkdir coms\%PLATFORMTARGET%

if "%PLATFORMTARGET%" == "clean" (
  rmdir /S /Q coms
  goto :END
)

@copy /Y ..\..\lite.io\%PLATFORMTARGET%\*.h coms\%PLATFORMTARGET%
@copy /Y ..\..\lite.io\%PLATFORMTARGET%\*.lib coms\%PLATFORMTARGET%
rem @copy /Y ..\lite.n\dzcf\*.h  coms\%PLATFORMTARGET%
rem @copy /Y ..\lite.n\i\*.h  coms\%PLATFORMTARGET%
rem @copy /Y ..\lite.n\n\*.h  coms\%PLATFORMTARGET%
rem @copy /Y ..\lite.n\z\*.h  coms\%PLATFORMTARGET%
rem @copy /Y ..\lite.n\out\*.lib  coms\%PLATFORMTARGET%
:END