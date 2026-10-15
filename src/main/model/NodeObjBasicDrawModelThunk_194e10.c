/* NodeObjBasicDrawModelThunk_194e10 -- shape-identical to merged MapGetFirstAreaSlot_1e5760 (2 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 0 immediate(s) substituted:
     MapGetAreaSlot_1e5770 -> NodeObjBasicDrawModel_196b10
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 NodeObjBasicDrawModel_196b10(s32, s32);

s32 NodeObjBasicDrawModelThunk_194e10(s32 a4)
{
    return NodeObjBasicDrawModel_196b10(a4, 0);
}
