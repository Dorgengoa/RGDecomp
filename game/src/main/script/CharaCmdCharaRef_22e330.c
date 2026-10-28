/* rgp:protos */
#define RGP_SELF_CharaCmdCharaRef_22e330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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

struct Ev {
    s32 m00;
    s32 m04;
    u8 pad[0x20];
    s8 m28;
};

s32 CharaCmdCharaRef_22e330(struct Obj0 *p0, s32 p1, s32 argc)
{
    s32 r0;
    s32 a;
    s32 b;
    s32 o;
    s32 o2;
    struct Ev *e;

    if (argc != 2) {
        return 0;
    }
    r0 = GetCurrentScene_1f5be0();
    if (r0 == 0) {
        return 1;
    }
    a = ScriptArgGetInt_302d70(p1);
    b = ScriptArgGetStr_302cb0(p1 + 5);
    o = GetLiveObjById_1ce420(p0->m00, a);
    if (o == 0) {
        return 1;
    }
    o2 = GetObjNodeByName_1ce3a0(p0->m00, -1, b);
    /* The LAST guard is a positive if-block, not an early return: retail's
       `beql $16,$0` jumps over it straight into the epilogue with the shared
       `addiu $2,$0,0x1` duplicated into the delay slot. */
    if (o2 != 0) {
        e = ((struct Ev *)ModelGetRootFrame_1511a0(o));
        e->m28 = 1;
        e->m04 = o2;
        FrameSetDirty_14a5e0(e);
    }
    return 1;
}
