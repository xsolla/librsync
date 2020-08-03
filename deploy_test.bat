set CMAKE_PATH="C:\Program Files\CMake\bin"
set VC_VARS_PATH="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64"

rmdir build_dir
mkdir build_dir

cd build_dir
%CMAKE_PATH%\cmake -DENABLE_TRACE=true -G "Visual Studio 14 2015 Win64" ..\
cmake --build . --target rsync --config Debug --clean-first 

call %VC_VARS_PATH%\vcvars64.bat

lib /OUT:Debug/rsync.lib /LIBPATH:Debug/ rsync.dir/Debug/*.obj
cmake --build . --target test_app_build --config Debug --clean-first 

copy C:\Work_files\patchdata\file1_files\patch Debug\
copy C:\Work_files\patchdata\file1_files\source Debug\
cd Debug
del .\new_file
.\test_app_build.exe > log.txt
cd ..