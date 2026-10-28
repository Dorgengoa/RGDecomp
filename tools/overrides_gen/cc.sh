#!/bin/sh
# usage: cc.sh relpath...
cd ../port
S=$TMPDIR/scratch/gamecop2/obj
mkdir -p $S
rc=0
for r in "$@"; do
  o=$S/$(basename $r .c).obj
  ../tools/llvm/bin/clang.exe -target i686-pc-windows-msvc -m32 -msse2 -mfpmath=sse -fwrapv -fno-strict-aliasing -fno-delete-null-pointer-checks -O1 -std=gnu99 -include port/prelude.h -I include -I game/include -Wno-int-conversion -Wno-incompatible-pointer-types -Wno-incompatible-function-pointer-types -fgnu89-inline -Wno-implicit-function-declaration -c overrides/$r -o $o || { echo "FAIL $r"; rc=1; }
done
exit $rc
