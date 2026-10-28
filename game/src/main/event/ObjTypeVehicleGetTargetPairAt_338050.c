/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleGetTargetPairAt_338050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x110];
    s32 m110;
    s16 m114;
};

s32 ObjTypeVehicleGetTargetPairAt_338050(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 t1;

    t0 = p0->m110;
    if (t0 != 0) {
        if (p1 >= 0) {
            t1 = p0->m114;
            if (t1 > p1) goto ok;
        }
    }
    return 0;
ok:
    return (t0 + p1 * 100);
}
