@echo off

@set ADDON_PATH=..\addon
if not exist %ADDON_PATH%\coms\%1 mkdir %ADDON_PATH%\coms\%1

@set ADDON_EX_PATH=..\addon.ex
if not exist %ADDON_EX_PATH%\coms\%1 mkdir %ADDON_EX_PATH%\coms\%1


@copy /Y ..\..\lite.io\%1\*.h      %ADDON_PATH%\coms\%1
@copy /Y ..\..\lite.io\%1\*.lib    %ADDON_PATH%\coms\%1
@copy /Y out\*.%1.lib              %ADDON_PATH%\coms\%1
@copy /Y dzcf\*.h                  %ADDON_PATH%\coms\%1
@copy /Y i\*.h                     %ADDON_PATH%\coms\%1
@copy /Y n\*.h                     %ADDON_PATH%\coms\%1
@copy /Y z\*.h                     %ADDON_PATH%\coms\%1

@copy /Y ..\..\lite.io\%1\*.h      %ADDON_EX_PATH%\coms\%1
@copy /Y ..\..\lite.io\%1\*.lib    %ADDON_EX_PATH%\coms\%1
@copy /Y out\*.%1.lib              %ADDON_EX_PATH%\coms\%1
@copy /Y dzcf\*.h                  %ADDON_EX_PATH%\coms\%1
@copy /Y i\*.h                     %ADDON_EX_PATH%\coms\%1
@copy /Y n\*.h                     %ADDON_EX_PATH%\coms\%1
@copy /Y z\*.h                     %ADDON_EX_PATH%\coms\%1

