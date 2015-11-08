echo off
setlocal ENABLEDELAYEDEXPANSION
set d=%cd::=%\
echo. > pngs.txt
for /R %%i in (*.png) do (
	set x=%%i
	set y=!x::=!
	echo !y:%d%=! >> pngs.txt
)