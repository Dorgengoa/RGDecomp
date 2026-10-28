/* rgp:protos */
#define RGP_SELF_EvCmdOptionsSet_240930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Script-command handler; sibling of src/bodies2/EvCmdPartySetActiveCount_240ab0.c and
   src/p23f/EvCmdPartySetLeader_240ef0.cpp, which fix GetGameData_1fede0's void signature and the
   ScriptGetInt_2490f0(p0) argument-evaluator shape.

   Seven-case jump table jtbl_0045E9E0: entries 0-4 and 6 all point at the
   shared epilogue (empty arms), only case 5 has a body, so the source must
   spell SEVEN case labels -- a single case compiles to a compare, not a table.
   The table is the identity permutation, so physical block order IS source
   order (seed src/wf/main/UiQuadSetByModeRelated_3934d0.c).

   `lw $16,0xC($2)` reads the accessor's result DIRECTLY out of $2 before the
   next call, so `t0 = r0->m0C;` is BEFORE `r1 = ScriptGetInt_2490f0(p0);`.  Had the
   load come after, $2 would first have to be moved to a callee-saved register
   -- which is exactly what EvCmdPartySetActiveCount_240ab0 and EvCmdPartySetLeader_240ef0 do, and both of those
   sources put the load after the call.

   MEASURED (12-arm sweep, build/wf37v/930): the ONLY spelling that keeps
   retail's `addiu $17,$17,0x8` as its own word is a POST-INCREMENT ON A
   POINTER USED AS THE CALL ARGUMENT.  `p0 = p0 + 8`, `p0 += 8`, a separate
   local `q = p0 + 8`, an `s32 *` with `p0 = p0 + 2`, a `static inline`
   returning `p + 8`, and folding `p0 + 8` at the use ALL compile to the same
   object (sha1 f09b64d9 for five of them): mwcc sinks the assignment into the
   arm and folds it into the argument as `addiu $4,$17,0x8`, one word short.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  EvCmdOptionsSet_240930  0045E9E0  1C   # jtbl_0045E9E0, 7 cases
   Score with scripts/rodata_check.py, never bare sandbox_build.py. */

/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

struct Cmd {
    s32 a;
    s32 b;
};

s32 EvCmdOptionsSet_240930(struct Cmd *p0, s32 p1)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;

    r0 = GetGameData_1fede0();
    t0 = r0->m0C;
    r1 = ScriptGetInt_2490f0((s32)p0++);
    switch (r1) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    case 5:
        OptionsSetDrawMessage_3d6020(t0, ScriptGetInt_2490f0((s32)p0));
        break;
    case 6:
        break;
    }
    return 1;
}
