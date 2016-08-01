@echo off

set CUR_DIR=%~dp0\
set BIN_DIR=%~dp0\bin\\
set DOT_NET=C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727
set SERVER_SRC=%~dp0\.\..\chatserver\src\
set CLIENT_SRC=%~dp0\.\..\unity5_3_client\chat_demo\Assets\_script\proto\Plugins\

if not exist "%BIN_DIR%" md "%BIN_DIR%"
copy "%CUR_DIR%c#\CoreOnly\ios\protobuf-net.dll" "%BIN_DIR%\protobuf-net.dll"
copy "%CUR_DIR%c#\CoreOnly\ios\protobuf-net.dll" "%CLIENT_SRC%\protobuf-net.dll"

::c++
for /f "tokens=*" %%i in ('dir/b *.proto') do (
 if exist "%%i" (
 @call "%CUR_DIR%c++\protoc" -I="%CUR_DIR%" --cpp_out="%BIN_DIR%" "%CUR_DIR%%%i")
 copy "%BIN_DIR%\%%~ni.pb.h" "%SERVER_SRC%\%%~ni.pb.h"
 copy "%BIN_DIR%\%%~ni.pb.cc" "%SERVER_SRC%\%%~ni.pb.cc"
)
)

::c#
for /f "tokens=*" %%i in ('dir/b *.proto') do (
 if exist "%%i" (
 @call "%CUR_DIR%\c#\ProtoGen\protogen" -i:%%i -o:"%BIN_DIR%\%%~ni.cs"
 @call "%DOT_NET%\csc.exe" /noconfig /out:"%BIN_DIR%\%%~ni.dll" /r:"%DOT_NET%\System.dll" /r:"%CUR_DIR%c#\CoreOnly\ios\protobuf-net.dll" /nologo /warn:4 /optimize- /t:library "%BIN_DIR%\%%~ni.cs" /fullpaths /utf8output
 @call "%CUR_DIR%\c#\Precompile\precompile" "%BIN_DIR%\%%~ni.dll" -o:"%BIN_DIR%\%%~niSerializer.dll" -t:"%%~niSerializer"
 copy "%BIN_DIR%\%%~ni.dll" "%CLIENT_SRC%\%%~ni.dll"
 copy "%BIN_DIR%\%%~niSerializer.dll" "%CLIENT_SRC%\%%~niSerializer.dll"
 )
 )  

pause