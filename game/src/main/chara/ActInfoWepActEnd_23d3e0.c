/* rgp:protos */
#define RGP_SELF_ActInfoWepActEnd_23d3e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct El8 { s32 x; s32 y; };
struct El12 { u8 d[12]; };
struct BigP { struct El12 *p; s32 pad[3]; };
struct BigS { s16 v; s16 pad[7]; };
extern struct El8 *D_00481E80 __attribute__((section(".sdata")));
extern s32 D_00481E84 __attribute__((section(".sdata")));
extern struct BigP D_004BCE68;
extern struct BigS D_004BCE90;
extern u8 D_004BCE20[];
/*rgp*/
/*rgp*/
/*rgp*/
s32 ActInfoWepActEnd_23d3e0(s32 a, s32 b)
{
    struct El12 *p;
    struct El8 *r;
    if (b != 0) {
        return 0;
    }
    if (D_00481E80 == 0) goto ret1;
    if (D_00481E84 >= 0x100) goto ret1;
    goto body;
ret1:
    return 1;
body:
    p = D_004BCE68.p + D_004BCE90.v;
    r = ((struct El8 *)ActInfoWepActGetList_22eef0(p));
    ActInfoWepActSetCount_22eee0(p, (D_00481E80 + D_00481E84) - r);
    ActCfgTableSetWepActCount_223c00(D_004BCE20, D_004BCE90.v + 1);
    return 1;
}
