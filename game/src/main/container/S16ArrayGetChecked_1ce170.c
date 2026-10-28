/* rgp:protos */
#define RGP_SELF_S16ArrayGetChecked_1ce170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x2];
    s16 m06;
};

s32 S16ArrayGetChecked_1ce170(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 t1;

    t0 = p0->m00;
    if (t0 != 0) {
        if (p1 >= 0) {
            t1 = p0->m06;
            if (t1 > p1) goto ok;
        }
    }
    return -1;
ok:
    return (s32)*(s16 *)(t0 + (p1 << 1));
}
