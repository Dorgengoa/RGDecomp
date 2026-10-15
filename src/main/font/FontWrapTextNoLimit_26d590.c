#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 FontWrapText_26d5a0(s32, s32, s32, s32, s32, s32);

s32 FontWrapTextNoLimit_26d590(s32 a4, s32 a5, s32 a6, s32 a7)
{
    return FontWrapText_26d5a0(a4, a5, a6, a7, 0, 0);
}
