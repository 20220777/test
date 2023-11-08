@set TARGET=%1
@set PLATFORMTARGET=%2
@set PACKAGENAME=%3
@set /p txt=<.version
@set _ver=%txt:~1,16%

@echo -------------------------
@echo %TARGET%
@echo =========================


@copy /Y out\%TARGET%.lib            out\%TARGET%.%_ver%.lib

:exit