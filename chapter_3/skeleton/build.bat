rem the cmakelist file has been automatically created using vscode extension, and filled to support winapi appllication.
rem configfure project under "build directory"
cmake.exe --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -S./ -B build -G "Visual Studio 17 2022" -T host=x64 -A win32
rem build for debug
cmake.EXE --build build --config Debug --target ALL_BUILD -j 18 --

rem how to clean
rem cmake.EXE" --build ./build --config Debug --target clean -j 18 --