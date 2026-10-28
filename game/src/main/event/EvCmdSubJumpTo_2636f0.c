/* rgp:protos */
#define RGP_SELF_EvCmdSubJumpTo_2636f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* One script-command handler out of an address-local family.  The
   operand stream is read 8 bytes at a time through three accessors;
   retail keeps a REAL incrementing cursor in a callee-saved register
   (daddu cur,a0 / addiu cur,8 in the jal delay slot), which is the
   POST-INCREMENT form f(p++).  Writing "f(p); p += 8;" instead lets
   mwcc fold every advance into base+offset addressing and the unit
   comes out one word short per operand. */

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSubJumpTo_2636f0(SArg *p0)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];
    s32 a;
    s32 b;
    s32 r;
    s32 rv;
    f32 fv;

    a = ScriptGetInt_26a2a0(p0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[0] = TaggedGetFloat_26a280(p0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[1] = TaggedGetFloat_26a280(p0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[2] = TaggedGetFloat_26a280(p0++);
    fv = TaggedGetFloat_26a280(p0++);
    b = ScriptGetInt_26a2a0(p0);
    r = ((s32)EvtGetSubMachine_26abb0(a));
    rv = 1;
    if (r == 0) {
        rv = 0;
    } else {
        EventSubNodeAddJumpTo_2516b0(r, (*(f32 (*)[3])(rgp_blk1 + 0x0)), b, fv);
        rv = 1;
    }
    return rv;
}
