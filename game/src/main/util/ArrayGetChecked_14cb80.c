/* rgp:protos */
#define RGP_SELF_ArrayGetChecked_14cb80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 { u8 pad000[0x4]; s32 m04; s32 m08; s32 m0C; };

s32 ArrayGetChecked_14cb80(struct Obj0 *p0, s32 p1)
{
    s32 t0;

    t0 = p0->m0C;
    if (t0 == 0) {
        return 0;
    }
    if (p1 >= 0) {
        if (p1 < p0->m04) {
            goto ok;
        }
    }
    return 0;
ok:
    return t0 + (p0->m08 * p1);
}
