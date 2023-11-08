@echo off

@set PLATFORMTARGET=%1

if "%PLATFORMTARGET%"=="" GOTO END

@copy /Y ..\..\lite.io\%PLATFORMTARGET%\*.h coms\%PLATFORMTARGET%
@copy /Y ..\..\lite.io\%PLATFORMTARGET%\*.lib coms\%PLATFORMTARGET%
@copy /Y ..\lite.n\dzcf\*.h  coms\%PLATFORMTARGET%
@copy /Y ..\lite.n\i\*.h  coms\%PLATFORMTARGET%
@copy /Y ..\lite.n\n\*.h  coms\%PLATFORMTARGET%
@copy /Y ..\lite.n\z\*.h  coms\%PLATFORMTARGET%
@copy /Y ..\lite.n\out\*.lib  coms\%PLATFORMTARGET%
:END