@set NODE_PATH=X:\xlocal\projectX\tools\ngine\out
@set NODE_BIN=%NODE_PATH%\ngine.x86.exe
@set NODE_LOG=%NODE_PLUGIN%\log

%NODE_BIN% --m console --d WAAS_NODE --s WAAS_NODE --X %NODE_PATH%\mtif.x86.dll --l %NODE_LOG% --e d2 --serial_port %1 --serial_baudrate %2
