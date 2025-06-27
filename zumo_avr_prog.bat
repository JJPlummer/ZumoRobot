echo off
REM Get directory of script
pushd %~dp0
set ROOTPATH=%CD%
popd

set "comport="
set "hexfile="

REM Jump to start
goto :argloop

REM emit usage on parsing error
:usage
echo %0 -f filename.hex [-com COMPORTNUMBER]
echo example: %0 -f test.hex -com 4
goto :fail

REM Start of argument processing
:argloop
IF NOT "%~1"=="" (
    IF "%1"=="-com" (
        SET comport=%2
        SHIFT
    )
    IF "%1"=="-f" (
       SET hexfile=%~2
        SHIFT
    )
    SHIFT
    GOTO :argloop
)
if "%hexfile%" == "" (
	echo Error: must specify hexfile to program
	goto :usage
)

SET AVR_DUDE_PATH=c:\WinAVR-20100110\bin
:continue
IF "%comport%" == "" SET comport=6 5 7 4 3 8 1 2

for %%p in ( %comport% ) DO (
	echo Trying com port COM%%p
	"%AVR_DUDE_PATH%"\avrdude -F -p atmega32u4 -c avr109 -P COM%%p -Uflash:w:"%hexfile%":i 
	IF NOT ERRORLEVEL 1 (
		goto :success
	)
)
goto :continue
:success
echo.
echo + + + + + + + + + + +    Programming Succeeded    + + + + + + + + + + +    
exit /b 0