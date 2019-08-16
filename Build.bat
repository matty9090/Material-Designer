@echo off

SET generator="Visual Studio 15"
SET config="Debug"
SET test=""

IF "%1" NEQ "" SET generator="%1"
IF "%2" NEQ "" SET config="%2"
IF "%3" NEQ "" SET test="%3"

IF NOT EXIST "Build/" mkdir Build

cmake -G %generator% -BBuild -DINSTALL_GTEST=0 -DBUILD_GMOCK=0 .
cmake --build Build --config %config%