/* rgp:protos */
#define RGP_SELF_CharaIsDeadVanishedMaybe_210a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 { u8 pad000[0x3D0]; s64 m3D0; u8 pad3D8[0x65A]; s16 mA32; s16 mA34; };

u8 CharaIsDeadVanishedMaybe_210a90(struct Obj0 *p0)
{
    s64 t0;
    s32 b;
    s16 t1;
    s16 t2;

    t0 = p0->m3D0;
    b = !(t0 & (((s64)0x2000000) << 0x20));
    if (b) {
        goto ok1;
    }
    return 0;
ok1:
    t1 = p0->mA32;
    if (t1 == 0x11) {
        goto ok2;
    }
    return 0;
ok2:
    t2 = p0->mA34;
    return (t2 == 0xA);
}
