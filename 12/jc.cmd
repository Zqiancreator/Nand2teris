@echo off
pushd .
call D:\DeskTop\nand2tetris\nand2tetris\tools\JackCompiler.bat %cd%\%1
REM 获取第一个参数的文件名和扩展名
set FileName=%~n1

echo %FileName%
set TestDir=%FileName%Test
if exist %FileName%.vm (
    REM 移动.mv文件到目标文件夹
    move %FileName%.vm %TestDir%
) else (
	echo %FileName%.vm is not exist
)

popd