/* rgp:protos */
#define RGP_SELF_HandleEntryResetStack_3f1390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern s32 D_004644D0;

struct Obj0 {
    u8 pad000[0xC];
    s16 m0C;
};

s32 HandleEntryResetStack_3f1390(s32 p0, struct Obj0 *p1, s32 p2)
{
    s16 n;
    s32 r0;

    if (p1 == 0) {
        return 0;
    }
    n = p1->m0C;
    if (n >= 0) {
        if (n < D_004644D0) {
            goto ok;
        }
    }
    return 0;
ok:
    r0 = ((s32)MemStackArrayGet_3f15a0(p0, n));
    if (r0 == 0) {
        return 0;
    }
    if (p2 == 1 || p2 < 0) {
        MemStackReset_14d830(r0);
    }
    return 1;
}
