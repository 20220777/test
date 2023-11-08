@echo off
@set ARCH=%1
@set MODULE=%2
@set result=false
@set TARGET=binding.gyp

if "%ARCH%" == "" (
  @echo %0 [system arch] [nmodule]
  goto :exit
)

if "%MODULE%" == "" (
  @echo %0 [system arch] [nmodule]
  goto :exit
)

if "%ARCH%" == "x86" (
  @set result=true
)

if "%ARCH%" == "x86_64" (
  @set result=true
)

if "%result%" == "true" (
  @set EXT=lib
  @set DEBUG_FLAGS="__LINUX__=0","__WIN32__=1",
) else (
  @set EXT=a
  @set DEBUG_FLAGS="__LINUX__=1","__WIN32__=0",
)

if "%MODULE%" == "http" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NHTTP__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NHTTP__=0",
)

if "%MODULE%" == "httpd" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NHTTPD__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NHTTPD__=0",
)

if "%MODULE%" == "httpsd" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NHTTPSD__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NHTTPSD__=0",
)

if "%MODULE%" == "serial" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NSERIAL__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NSERIAL__=0",
)

if "%MODULE%" == "tcp" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NTCP__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NTCP__=0",
)

if "%MODULE%" == "tcpd" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NTCPD__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NTCPD__=0",
)

if "%MODULE%" == "tcpsd" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NTCPSD__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NTCPSD__=0",
)

if "%MODULE%" == "wsc" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NWSC__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NWSC__=0",
)

if "%MODULE%" == "wsd" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NWSD__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NWSD__=0",
)

if "%MODULE%" == "shm" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NSHM__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NSHM__=0",
)

if "%MODULE%" == "mdns" (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NMDNS__=1",
) else (
  @set DEBUG_FLAGS=%DEBUG_FLAGS%"__NWDNS__=0",
)

@set BINDING={
@set BINDING=%BINDING%"targets":[
@set BINDING=%BINDING%{
@set BINDING=%BINDING%"target_name": "liteio_%MODULE%_%ARCH%",
@set BINDING=%BINDING%"msvs_settings": { 'VCCLCompilerTool': { 'RuntimeLibrary': 1, } } ,
@set BINDING=%BINDING%"sources" : [
@set BINDING=%BINDING%"./nxx/m.c",
@set BINDING=%BINDING%],
@set BINDING=%BINDING%"include_dirs" : [
@set BINDING=%BINDING%"./",
@set BINDING=%BINDING%"./nxx",
@set BINDING=%BINDING%"./coms",
@set BINDING=%BINDING%"./coms/%ARCH%",
@set BINDING=%BINDING%"<(module_root_dir)/../../usr/openssl/v1.1.1t/%ARCH%/include",
@set BINDING=%BINDING%"<(module_root_dir)/../../usr/openssl/v1.1.1t/%ARCH%/include/openssl",
@set BINDING=%BINDING%],
@set BINDING=%BINDING%"link_settings" : {
@set BINDING=%BINDING%"libraries" : [
@set BINDING=%BINDING%"ws2_32.lib",
@set BINDING=%BINDING%"crypt32.lib",
@set BINDING=%BINDING%"<(module_root_dir)/../../usr/openssl/v1.1.1t/%ARCH%/lib/libcrypto.%EXT%",
@set BINDING=%BINDING%"<(module_root_dir)/../../usr/openssl/v1.1.1t/%ARCH%/lib/libssl.%EXT%",
@set BINDING=%BINDING%"<(module_root_dir)/coms/%ARCH%/liblite.n.%ARCH%.%EXT%",
@set BINDING=%BINDING%"<(module_root_dir)/coms/%ARCH%/liblite.io.%ARCH%.%EXT%",
@set BINDING=%BINDING%"<(module_root_dir)/coms/%ARCH%/libio.%ARCH%.%EXT%",
@set BINDING=%BINDING%],
@set BINDING=%BINDING%},
@set BINDING=%BINDING%"cflags" : [
@set BINDING=%BINDING%"/GS ",
@set BINDING=%BINDING%"/GL ",
@set BINDING=%BINDING%"/analyze- ",
@set BINDING=%BINDING%"/W3 ",
@set BINDING=%BINDING%"/Gy ",
@set BINDING=%BINDING%"/Zc:wchar_t ",
@set BINDING=%BINDING%"/Zi ",
@set BINDING=%BINDING%"/Gm- ",
@set BINDING=%BINDING%"/O2 ",
@set BINDING=%BINDING%"/sdl- ",
@set BINDING=%BINDING%"/Zc:inline ",
@set BINDING=%BINDING%"/fp:precise ",
@set BINDING=%BINDING%"/errorReport:prompt ",
@set BINDING=%BINDING%"/WX- ",
@set BINDING=%BINDING%"/Zc:forScope ",
@set BINDING=%BINDING%"/Gd ",
@set BINDING=%BINDING%"/Oy- ",
@set BINDING=%BINDING%"/Oi ",
@set BINDING=%BINDING%"/MT ",
@set BINDING=%BINDING%"/EHsc /LTCG",
@set BINDING=%BINDING%"/nologo ", ],
@set BINDING=%BINDING%"defines" : [
@set BINDING=%BINDING%"_WIN32_WINNT=0x0600",
@set BINDING=%BINDING%"__DEBUG__=1",
@set BINDING=%BINDING%"__DRBG_CHECK__=0",
@set BINDING=%BINDING%"__HTTP__=1",
@set BINDING=%BINDING%"__MIME__=1",
@set BINDING=%BINDING%"__SHM__=1",
@set BINDING=%BINDING%"__NIC__=0",
@set BINDING=%BINDING%"__CGI__=0",
@set BINDING=%BINDING%"__XML__=0",
@set BINDING=%BINDING%"__SERIAL__=1",
@set BINDING=%BINDING%"__SOCKET__=1",
@set BINDING=%BINDING%"__PACKET__=1",
@set BINDING=%BINDING%"__DBC__=0",
@set BINDING=%BINDING%"__SHA1__=1",
@set BINDING=%BINDING%"__LIST__=0",
@set BINDING=%BINDING%"__QUEUE__=0",
@set BINDING=%BINDING%"__STACK__=0",
@set BINDING=%BINDING%"__JSON__=1",
@set BINDING=%BINDING%"__SYSQUEUE__=0",
@set BINDING=%BINDING%"__TRIGONOMETRIC__=1",
@set BINDING=%BINDING%"__SSL_TLS__=1",
@set BINDING=%BINDING%"__CUSTOM_X_SOCKET__=1",
@set BINDING=%BINDING%"__CUSTOM_X_HTTP__=1",
@set BINDING=%BINDING%"__CUSTOM_X_HTTPD__=1",
@set BINDING=%BINDING%"__CUSTOM_X_HTTPSD__=0",
@set BINDING=%BINDING%"__CUSTOM_X_WS__=1",
@set BINDING=%BINDING%"__CUSTOM_X_SERIAL__=1",
@set BINDING=%BINDING%"__CUSTOM_X_SIFR__=0",
@set BINDING=%BINDING%"__STATIC_LIB__=1",
@set BINDING=%BINDING%"__NODE__=1",
@set BINDING=%BINDING%%DEBUG_FLAGS%]
@set BINDING=%BINDING%}
@set BINDING=%BINDING%]
@set BINDING=%BINDING%}

@echo %BINDING% > %TARGET%



:exit
