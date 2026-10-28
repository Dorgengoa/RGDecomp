/* rgp:protos */
#define RGP_SELF_EvCmdSubMoveByVel_263460 1
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

/* the optional 6th operand: retail FALLS THROUGH into the read when
   argc >= 6 (slti argc,6 then bnel past it), so that is the if body. */

s32 EvCmdSubMoveByVel_263460(SArg *p0, s32 p1)
{
    f32 v[4] __attribute__((aligned(16)));
    s32 a;
    s32 b;
    s32 c;
    s32 r;
    s32 rv;

    c = 0;
    a = ScriptGetInt_26a2a0(p0++);
    v[0] = TaggedGetFloat_26a280(p0++);
    v[1] = TaggedGetFloat_26a280(p0++);
    v[2] = TaggedGetFloat_26a280(p0++);
    v[3] = 1.0f;
    b = ScriptGetInt_26a2a0(p0++);
    if (p1 >= 6) {
        c = ScriptGetInt_26a2a0(p0);
    }
    r = ((s32)EvtGetSubMachine_26abb0(a));
    rv = 1;
    if (r == 0) {
        rv = 0;
    } else {
        EventSubNodeAddMoveByVel_2515b0(r, v, b, c);
        rv = 1;
    }
    return rv;
}
