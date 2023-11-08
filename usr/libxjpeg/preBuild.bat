set PARENT_PATH=%1
set PLATFORM_TYPE=%2
@if not exist then mkdir coms
@copy /Y %PARENT_PATH%\xmtif\out\*.dll                              coms
@copy /Y %PARENT_PATH%\xmtif\xmain\gxLocal.h                        coms
@copy /Y %PARENT_PATH%\xmtif\xmain\xmainc.h                         coms
@copy /Y %PARENT_PATH%\xmtif\xmain\*fx.h                            coms
@copy /Y %PARENT_PATH%\xmtif\m\cCommon.h                            coms
@copy /Y %PARENT_PATH%\xmtif\io\coms\*.h                            coms
@copy /Y %PARENT_PATH%\xmtif\io\coms\*.lib                          coms
