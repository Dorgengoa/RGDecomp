/* rgp:protos */
#define RGP_SELF_MotionEventCfgSeCmd_1b4070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    struct Obj1 *m00;
};

struct Obj1 {
    u8 pad000[0x44];
    struct Obj2 *m44;
};

struct Obj2 {
    u8 pad000[0x28];
    s32 m28;
};

s32 MotionEventCfgSeCmd_1b4070(s32 p0, s32 p1, struct Obj0 *p2)
{
    struct Obj1 *t0;
    s32 r0;
    s32 r1;

    t0 = p2->m00;
    if (t0->m44 == 0) {
        return 0;
    }
    r0 = VariantGetInt_15f780(p0);
    t0->m44->m28 = r0;
    if (p1 >= 2) {
        r1 = SlotGetInt_15f720((p0 + 8));
        MotionEventSeSetName_1b1800(t0->m44, r1);
    }
    return 1;
}
