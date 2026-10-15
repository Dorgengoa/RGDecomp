#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_0045D050[];

extern s32 ActCfgTableGetInfoNameByMode_21f5b0(s32, s32, s32, s32, s32, s32, s32, void *);

s32 ActCfgTableGetRunMotionName_21f570(s32 a4, s32 a5, s32 a6)
{
    return ActCfgTableGetInfoNameByMode_21f5b0(a4, a5, a6, 0x65, 0x6F, 0x79, 0x83, D_0045D050);
}
