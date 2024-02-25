@echo off

if "%~1" == "" goto ARG_ERROR
if "%~2" == "" goto ARG_ERROR

set ASSETS_PATH=%~1
set "ASSETS_PATH=%ASSETS_PATH:/=\%"
set OUTPUT_PATH=%~2
set "OUTPUT_PATH=%OUTPUT_PATH:/=\%"
set BASE_OUTPUT_PATH=%OUTPUT_PATH%\..

if not exist %ASSETS_PATH% (
	echo ERROR: Source assets folder doesn't exists
	exit /B 2
)

if exist %OUTPUT_PATH% (
	echo Target folder already exists, skipping
	exit /B 0
) else (
	echo Creating output path folder %BASE_OUTPUT_PATH%
	mkdir %BASE_OUTPUT_PATH%
	echo Creating link %OUTPUT_PATH% pointing to %ASSETS_PATH%
	mklink /j %OUTPUT_PATH% %ASSETS_PATH%
	echo Done!
)

exit /B 0

:ARG_ERROR
echo "Usage: create_assets_link.bat {assets_folder_path} {output_assets_folder_path}"