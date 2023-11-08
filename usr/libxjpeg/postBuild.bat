set OUTPUT_NAME=%1
set PROJECT_PATH=%2
set PLATFORM_TYPE=%3
set OUTPUT_TYPE=%4
@set /p txt=<.version
@set _ver=%txt:~1,16%

@echo -------------------------------------------------------------
@echo %OUTPUT_NAME% %PROJECT_PATH% %PLATFORM_TYPE% %_ver%
@echo =============================================================

@copy /Y %PROJECT_PATH%\out\%OUTPUT_NAME%.%PLATFORM_TYPE%%OUTPUT_TYPE%    %PROJECT_PATH%\out\%OUTPUT_NAME%.%PLATFORM_TYPE%.%_ver%%OUTPUT_TYPE%
@copy /Y %PROJECT_PATH%\out\%OUTPUT_NAME%.%PLATFORM_TYPE%%OUTPUT_TYPE%    %PROJECT_PATH%\out\%OUTPUT_NAME%%OUTPUT_TYPE%

@copy /Y %PROJECT_PATH%\i\*.h                                             %PROJECT_PATH%\..\..\lite.io\%PLATFORM_TYPE%\
@copy /Y %PROJECT_PATH%\out\%OUTPUT_NAME%.%PLATFORM_TYPE%%OUTPUT_TYPE%    %PROJECT_PATH%\..\..\lite.io\%PLATFORM_TYPE%\%OUTPUT_NAME%%OUTPUT_TYPE%
