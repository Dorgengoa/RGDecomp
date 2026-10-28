/* rgp:protos */
#define RGP_SELF_SaveCardHasFreeSpace_37b8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct G37B8C0 { u8 pad000[0x4EC]; s16 f4EC; };

extern struct G37B8C0 *D_004831D0;
/*rgp*/

s32 SaveCardHasFreeSpace_37b8c0(void)
{
    struct G37B8C0 *g;
    u8 *e;
    s32 v;

    g = D_004831D0;
    e = (u8 *)g + g->f4EC * 28 + 0x4A4;
    if (e == 0) return 0;
    v = *(s32 *)(e + 0x10);
    return !(v < SaveCalcSizeKB_3735e0((void *)(g)));
}
