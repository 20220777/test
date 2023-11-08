@echo off

@set ARCH=%1
if "%ARCH%" == "x86" (
@set COPT=VC-WIN32
)
if "%ARCH%" == "x86_64" (
@set COPT=VC-WIN64A
)

@set OPENSSL_DIR=X:\xlocal\crl\c\usr\openssl-1.1.1t
@set PREFIX=X:\xlocal\crl\c\usr\openssl\v1.1.1t\%ARCH% --openssldir=%OPENSSL_DIR%
@set PATH=.;c:\UnixUtils\;C:\unixutils\perl\perl\bin;c:\UnixUtils\bin;%PATH%;%OPENSSL_DIR%


perl %OPENSSL_DIR%\Configure %COPT% -static no-tests no-rdrand no-ts no-ui-console no-hw no-err no-aria no-seed no-idea no-md2 no-mdc2 no-rc5 no-rc4 no-asm no-shared no-autoload-config no-deprecated no-egd no-sse2 --release --prefix=%PREFIX%  --openssldir=%OPENSSL_DIR%
nmake