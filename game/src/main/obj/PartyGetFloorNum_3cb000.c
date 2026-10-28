/* rgp:protos */
#define RGP_SELF_PartyGetFloorNum_3cb000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x2A];
    s16 m30;
};

s32 PartyGetFloorNum_3cb000(struct Obj0 *p0)
{
    s32 r;
    s16 t1;

    r = 0;
    if (p0->m04 == 0xA) {
        t1 = p0->m30;
        if (t1 > 0x4E20 && t1 < 0x5209) {
            r = (s32)(t1 + -0x4E20);
        }
    }
    return r;
}
