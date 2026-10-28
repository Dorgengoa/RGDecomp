#include "types.h"
/* stack-block, 2026-10-24 (docs/PROTOS.md "function-pointer resolution"):
   CallTbl_401880 tail-jumps through the function table D_00480040
   (`addiu %lo(D); addu idx; lw f, 0(t); jr f`, the AnimKeyEval* shape); the
   table's WriteQuad_4018c0 stores 16 bytes through the pointer, so `s32 v[2]`
   is one block reaching 0x10 (tools/stages/sbresolve.py `dtbl`). */
extern void CallTbl_401880(s32 *p, s32 k);

s32 FnTblBlock_401800(void)
{
    s32 v[2];

    CallTbl_401880(v, 0);
    return v[0];
}

/* the callees (their listings are the truth; text only) */
typedef void (*TblFn)(s32 *p);
extern TblFn D_00480040[2];

void CallTbl_401880(s32 *p, s32 k)
{
    D_00480040[k](p);
}

void WriteQuad_4018c0(s32 *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}
