/* rgp:protos */
#define RGP_SELF_RecStackSlotRelease_201d10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of RecStackHeapSlotRelease_201ea0 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0;

struct Obj0 {
    s32 m00;
};

void RecStackSlotRelease_201d10(s32 p0, struct Obj0 *p1)
{
    s32 t0;
    s32 r0;
    s32 t1;

    if (p1 != 0) {
        t0 = p1->m00;
        if (t0 >= 0) {
            r0 = GetCurrentScene_1f5be0();
            t1 = p1->m00;
            RecStackPop_1c4140(r0, t1);
        }
        p1->m00 = -1;
    }
    if (p0 != 0) {
        MemStackReset_14d830(p0);
        return;
    }
}
