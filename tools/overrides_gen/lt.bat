@echo off
set PATH=C:\Windows\system32;C:\Windows
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86 >nul 2>&1
cd /d .
set FL=-target i686-pc-windows-msvc -m32 -msse2 -mfpmath=sse -fwrapv -fno-strict-aliasing -fno-delete-null-pointer-checks -O1 -std=gnu99 -include port/prelude.h -I include -I game/include -Wno-int-conversion -Wno-incompatible-pointer-types -Wno-incompatible-function-pointer-types -fgnu89-inline -Wno-implicit-function-declaration -I tests/bindings -fuse-ld=lld -llegacy_stdio_definitions
set SR=overrides/src/main/vec/VecDot3_1cba90.c overrides/src/main/vec/VecLengthSq_1cb470.c overrides/src/main/vec/VecLength_1cb4c0.c overrides/src/main/vec/VecCross_1cb9f0.c overrides/src/main/vec/VecSub_1cbd00.c overrides/src/main/vec/VecDivScalar_1cbbf0.c overrides/src/main/vec/VecScaleToLength_1cb510.c overrides/src/main/matrix/MatMul_1cb700.c overrides/src/main/vec/VecNormalize_1cbb80.c overrides/src/main/matrix/MtxInverseAffine_1cb640.c overrides/src/main/vec/TriNormalDot_1cb600.c overrides/src/main/model/VertsPackQuantized_164bb0.c overrides/src/main/vec/VecMinMax_1cb570.c overrides/src/main/vec/VecLerp_1cbb20.c overrides/src/main/matrix/MatMulVec4Args_1cb7f0.c overrides/src/main/script/FixCameraRecInit_193860.c 
../tools\llvm\bin\clang.exe %FL% tests/bindings/ovr_gamecop2.c %SR% src/ps2/vu0.c %~dp0main.c -o %~dp0t.exe
../tools\llvm\bin\clang.exe %FL% -DRG_BT_WRONG tests/bindings/ovr_gamecop2.c %SR% src/ps2/vu0.c %~dp0main.c -o %~dp0tw.exe
%~dp0t.exe
echo rc=%errorlevel%
%~dp0tw.exe
echo rcw=%errorlevel%
