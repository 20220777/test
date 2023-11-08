@echo off
@set ARCH=%1
@set MODULE=%2
@set result=false
@set TARGET=binding.gyp
@set OUTPUT_DIR=out
rem ################################################################################
rem ################################################################################
rem ################################################################################
if exist build rmdir /S /Q build

if not exist then mkdir %OUTPUT_DIR%

if "%ARCH%" == "" (
  @echo %0 [system arch] [nmodule]
  goto :end
)

if "%MODULE%" == "" (
  @echo %0 [system arch] [nmodule]
  goto :end
)


@echo ################################################################################
@echo # check nbuild %ARCH%
@echo ################################################################################



if "%MODULE%" == "all" (
  @echo ################################################################################
  @echo # build %ARCH% serial
  @echo ################################################################################
  bindings %ARCH% serial
  node-gyp clean configure build
  @copy /Y build\Release\*serial*.node         %OUTPUT_DIR%

  @echo ################################################################################
  @echo # build %ARCH% socket
  @echo ################################################################################
  bindings %ARCH% socket
  node-gyp clean configure build
  @copy /Y build\Release\*socket*.node         %OUTPUT_DIR%

  @echo ################################################################################
  @echo # build %ARCH% shm
  @echo ################################################################################
  bindings %ARCH% shm
  node-gyp clean configure build
  @copy /Y build\Release\*shm*.node         %OUTPUT_DIR%

  @echo ################################################################################
  @echo # build %ARCH% httpd
  @echo ################################################################################
  bindings %ARCH% httpd
  node-gyp clean configure build
  @copy /Y build\Release\*httpd*.node         %OUTPUT_DIR%

  @echo ################################################################################
  @echo # build %ARCH% websocket
  @echo ################################################################################
  bindings %ARCH% websocket
  node-gyp clean configure build
  @copy /Y build\Release\*websocket*.node         %OUTPUT_DIR%

) else (
  @echo ################################################################################
  @echo # build %ARCH% %MODULE%
  @echo ################################################################################
  bindings %ARCH% %MODULE%
  node-gyp clean configure build
  @copy /Y build\Release\*%MODULE%*.node         %OUTPUT_DIR%
)

:end