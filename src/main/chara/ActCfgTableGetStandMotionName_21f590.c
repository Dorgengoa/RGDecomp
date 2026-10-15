#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_0045D058[];

extern s32 ActCfgTableGetInfoNameByMode_21f5b0(s32, s32, s32, s32, s32, s32, s32, void *);

s32 ActCfgTableGetStandMotionName_21f590(s32 a4, s32 a5, s32 a6)
{
    return ActCfgTableGetInfoNameByMode_21f5b0(a4, a5, a6, 0x64, 0x6E, 0x78, 0x82, D_0045D058);
}
