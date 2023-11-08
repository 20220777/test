set OUTPUT_TYPE=%1
set PROJECT_PATH=%2
@if not exist then mkdir %PROJECT_PATH%\out


@copy /Y %PROJECT_PATH%\..\..\..\c\lite.io\%OUTPUT_TYPE%\lite.io.dll       %PROJECT_PATH%\out