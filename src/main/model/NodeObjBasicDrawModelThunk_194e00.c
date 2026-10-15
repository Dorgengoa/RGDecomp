/* NodeObjBasicDrawModelThunk_194e00 -- shape-identical to merged GameSceneSoundSlot6Free_1d0850 (2 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 1 immediate(s) substituted:
     GameSceneSoundSlotFree_1d1210 -> NodeObjBasicDrawModel_196b10
     imm 6 -> 1
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 NodeObjBasicDrawModel_196b10(s32, s32);

s32 NodeObjBasicDrawModelThunk_194e00(s32 a4)
{
    return NodeObjBasicDrawModel_196b10(a4, 1);
}
