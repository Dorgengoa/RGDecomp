/* rgp:protos */
#define RGP_SELF_UiSelFrameCalcTileCounts_28d9d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
    s16 m0A;
    u8 pad00C[0xC];
    s32 m18;
    s32 m1C;
};

void UiSelFrameCalcTileCounts_28d9d0(struct Obj0 *p0)
{
    s32 t0;
    s32 l0;
    s32 l1;
    s32 t1;

    t0 = p0->m18;
    l0 = 1;
    l1 = 1;
    while ((l0 << 4) < t0) {
        l0 = (l0 + 1);
    }
    t1 = p0->m1C;
    while ((l1 << 4) < t1) {
        l1 = (l1 + 1);
    }
    p0->m08 = l0;
    p0->m0A = l1;
}
