/* rgp:protos */
#define RGP_SELF_InvCollectPlacedCagesInCurLocation_3c4be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Y3C4BE0 { u8 pad000[0x10]; s16 *f10; };
struct X3C4BE0 { u8 pad000[0x24]; struct Y3C4BE0 *f24; };
struct G3C4BE0 { u8 pad000[0x18]; struct X3C4BE0 *f18; };

extern struct G3C4BE0 *D_00483890;
/*rgp*/

s32 InvCollectPlacedCagesInCurLocation_3c4be0(void *self, s32 a, void *b)
{
    struct G3C4BE0 *g;
    struct Y3C4BE0 *y;
    s16 *x;
    s16 k;

    g = D_00483890;
    if (g == 0) return 0;
    y = g->f18->f24;
    if (y != 0) {
        x = y->f10;
    } else {
        x = 0;
    }
    if (x != 0) {
        k = *x;
    } else {
        k = -1;
    }
    return InvCollectPlacedCages_3c4c40(self, k, a, b);
}
