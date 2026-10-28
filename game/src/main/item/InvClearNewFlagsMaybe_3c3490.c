/* rgp:protos */
#define RGP_SELF_InvClearNewFlagsMaybe_3c3490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

extern s32 D_00465B50;

struct Obj0 {
    u8 pad000[0x168];
    s32 m168;
};

struct Obj1 {
    u8 pad000[0xA];
    u8 m0A_b0 : 1;
    u8 m0A_b1 : 1;
    u8 m0A_b2 : 6;
};

s32 InvClearNewFlagsMaybe_3c3490(struct Obj0 *p0)
{
    s32 t0;
    s32 l0;
    s32 t1;
    struct Obj1 *r1;

    t0 = D_00465B50;
    l0 = 0;
    while (l0 < t0) {
        t1 = p0->m168;
        r1 = (struct Obj1 *)PoolGetUsedElem_36acb0(t1, l0);
        if (r1 != 0) {
            if (r1->m0A_b1 == 0) {
                r1->m0A_b0 = 0;
            }
        }
        l0 = (l0 + 1);
    }
    return 1;
}
