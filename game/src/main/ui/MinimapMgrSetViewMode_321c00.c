/* rgp:protos */
#define RGP_SELF_MinimapMgrSetViewMode_321c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E321 {
    u8 pad000[0x11C];
    u8 m11C;
    u8 pad11D[0x93];
};

/*rgp*/

void MinimapMgrSetViewMode_321c00(struct E321 *p0, s32 p1)
{
    s32 i;
    struct E321 *e;
    s32 r;

    i = 0;
    do {
        e = &p0[i];
        r = MinimapSlotIsActive_322510(e);
        if (r != 0) {
            e->m11C = p1;
        }
        i = i + 1;
    } while (i < 3);
}
