@echo off
rem Build the native-renderer lane's command-line tools into out\nrender
rem (docs/NATIVE-RENDER.md "Tools").  RG_NR_LIBDIR: build tree with the VIF/VU libs.
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86 >nul 2>&1
if "%RG_NR_LIBDIR%"=="" set RG_NR_LIBDIR=build\nrender-i686
set P=.
set CC=../tools\llvm\bin\clang.exe --target=i686-pc-windows-msvc -O2 -msse2 -D_CRT_SECURE_NO_WARNINGS -I%P%\src\ps2\vif -I%P%\src\ps2\vu -I%P%\src\native\render -I%P%\include
set LIBS=%RG_NR_LIBDIR%\src\ps2\vif\rg_ps2_vif.lib %RG_NR_LIBDIR%\src\ps2\vu\rg_ps2_vu.lib
if not exist %P%\out\nrender mkdir %P%\out\nrender
%CC% %P%\tools\native\render_nmcheck.c %P%\src\native\render\nr_vu1.c -o %P%\out\nrender\rg-nr-nmcheck.exe || exit /b 1
%CC% %P%\tools\native\render_vutrace.c -o %P%\out\nrender\rg-nr-vutrace.exe %LIBS% || exit /b 1
%CC% %P%\tools\native\render_meshcheck.c %P%\src\native\render\nr_mesh.c -o %P%\out\nrender\rg-nr-meshcheck.exe %LIBS% || exit /b 1
%CC% %P%\tools\native\render_meshdump.c %P%\src\native\render\nr_mesh.c -o %P%\out\nrender\rg-nr-meshdump.exe || exit /b 1
