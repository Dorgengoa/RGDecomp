/* rgp:protos */
#define RGP_SELF_NpcTalkTextPacPath_41dff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 Sprintf_1343b8(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00480138;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 NpcTalkTextPacPath_41dff0(s32 p0, s32 p1, struct Obj0 *p2)
{
    s32 t0;
    s32 rv1;
    s32 t1;
    s32 r0;

    if (p1 == 0 || p2 == 0) {
        return 0;
    }
    t0 = p2->m04;
    rv1 = 1;
    if (t0 == 0) {
        rv1 = 0;
    } else {
        t1 = D_00480138;
        r0 = Sprintf_1343b8(p1, t1, t0, t0);
        rv1 = 1;
    }
    return rv1;
}
