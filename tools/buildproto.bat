@echo off

SET PROTOC=protoc.exe
SET PROTO_DIR=../protos/scripts
SET SERVER_OUTPUT=../protos/code

FOR %%P IN (%PROTO_DIR%/*.proto) DO (
	%PROTOC% -I%PROTO_DIR% --cpp_out=%SERVER_OUTPUT% %PROTO_DIR%/%%P	
	@echo Generate From %%P
	)

pause