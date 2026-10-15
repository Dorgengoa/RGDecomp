#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SoundPlayEntry_1b8f90(s32, s32, s32, s32, s32, s32, s32);

s32 SoundPlayVolPan_1b9aa0(s32 a4, s32 a5, s32 a6, s32 a7, s32 a8)
{
    return SoundPlayEntry_1b8f90(a4, a5, -1, a6, a7, 0x2000, a8);
}
