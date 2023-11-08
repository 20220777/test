set OUTPUT_TYPE=%1
set PROJECT_PATH=%2
set OUTPUT_NAME=%3
@if not exist then mkdir %PROJECT_PATH%\out

@copy /Y %PROJECT_PATH%\out\%OUTPUT_NAME%.dll %PROJECT_PATH%\out\%OUTPUT_NAME%.%OUTPUT_TYPE%.dll
@copy /Y %PROJECT_PATH%\out\%OUTPUT_NAME%.dll %PROJECT_PATH%\..\..\..\c\lite.io\%OUTPUT_TYPE%\