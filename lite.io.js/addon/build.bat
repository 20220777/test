@echo off
@set ARCH=%1
@set MODULE=%2
@set result=false
@set TARGET=binding.gyp

rem ################################################################################
rem ################################################################################
rem ################################################################################
if exist build rmdir /S /Q build

if "%ARCH%" == "" (
  @echo %0 [system arch] [nmodule]
  goto :end
)

if "%MODULE%" == "" (
  @echo %0 [system arch] [nmodule]
  goto :end
)

if "%MODULE%" == "all" (
  @echo ################################################################################
  @echo # build %ARCH% serial
  @echo ################################################################################
  bindings %ARCH% serial
  node-gyp clean configure build
  @copy /Y build\Release\*serial*.node         bin

  @echo ################################################################################
  @echo # build %ARCH% shm
  @echo ################################################################################
  bindings %ARCH% shm
  node-gyp clean configure build
  @copy /Y build\Release\*shm*.node         bin

  @echo ################################################################################
  @echo # build %ARCH% httpd
  @echo ################################################################################
  bindings %ARCH% httpd
  node-gyp clean configure build
  @copy /Y build\Release\*httpd*.node         bin

  @echo ################################################################################
  @echo # build %ARCH% http
  @echo ################################################################################
  bindings %ARCH% http
  node-gyp clean configure build
  @copy /Y build\Release\*http*.node         bin

  @echo ################################################################################
  @echo # build %ARCH% wsd
  @echo ################################################################################
  bindings %ARCH% wsd
  node-gyp clean configure build
  @copy /Y build\Release\*wsd*.node         bin

  @echo ################################################################################
  @echo # build %ARCH% wsc
  @echo ################################################################################
  bindings %ARCH% wsc
  node-gyp clean configure build
  @copy /Y build\Release\*wsc*.node         bin

  @echo ################################################################################
  @echo # build %ARCH% tcpd
  @echo ################################################################################
  bindings %ARCH% tcpd
  node-gyp clean configure build
  @copy /Y build\Release\*tcpd*.node         bin

  @echo ################################################################################
  @echo # build %ARCH% tcp
  @echo ################################################################################
  bindings %ARCH% tcp
  node-gyp clean configure build
  @copy /Y build\Release\*tcp*.node         bin
) else (
  @echo ################################################################################
  @echo # build %ARCH% %MODULE%
  @echo ################################################################################
  bindings %ARCH% %MODULE%
  node-gyp clean configure build
  @copy /Y build\Release\*%MODULE%*.node         bin
)

:end