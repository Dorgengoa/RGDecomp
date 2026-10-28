/* rgp:protos */
#define RGP_SELF_CharaCmdEffectSpawn_22db00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* argc 2 or 3.  The optional third argument uses a BRANCH-LIKELY (`bnel`) with
   the `c = 0` in the delay slot, so it is an if/else, not the plain-branch
   unconditional-then-overwrite shape of CharaCmdFadeIn_22bb10. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
};

struct Buf20 {
    u8 b[0x20];
};

s32 CharaCmdEffectSpawn_22db00(struct Obj0 *p0, s32 p1, s32 argc)
{
    struct Buf20 sp60 __attribute__((aligned(16)));
    s32 a;
    s32 b;
    s32 c;
    s32 m;

    if (argc != 2 && argc != 3) {
        return 1;
    }
    a = ScriptArgGetStr_302cb0(p1);
    b = ScriptArgGetInt_302d70(p1 + 5);
    if (argc >= 3) {
        c = ScriptArgGetStr_302cb0(p1 + 0xA);
    } else {
        c = 0;
    }
    m = ((s32)GetEffectMgr_2d9040());
    EffectCreateByName_2e1020(&sp60, m, a, (s16)b);
    EffectSetAutoRelease_2e1170(m, &sp60, 1);
    EffectSetId_2e0100(m, &sp60, p0->m00);
    EffectSetName_2e01c0(m, &sp60, c);
    return 1;
}
