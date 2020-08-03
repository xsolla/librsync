set CMAKE_PATH="C:\Program Files\CMake\bin"
set VC_VARS_PATH="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64"

mkdir build_dir
cd build_dir
%CMAKE_PATH%\cmake -DENABLE_TRACE=true -G "Visual Studio 14 2015 Win64" ..\
cmake --build . --target rsync --config Debug --clean-first
cmake --build . --target rsync --config Release --clean-first

call %VC_VARS_PATH%\vcvars64.bat


lib /OUT:Debug/rsync.lib /LIBPATH:Debug/ rsync.dir/Debug/*.obj
copy /y Debug\rsync.* ..\..\..\win\librsync\lib\Debug\
lib /OUT:Release\rsync.lib /LIBPATH:Release/ rsync.dir/Release/*.obj
copy /y Release\rsync.* ..\..\..\win\librsync\lib\Release\

cd ..

copy /y src\*.h ..\..\win\librsync\include\
copy /y src\blake2\*.h ..\..\win\librsync\include\blake2\

rmdir /S /q build_dir