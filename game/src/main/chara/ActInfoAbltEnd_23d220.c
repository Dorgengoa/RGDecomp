/* rgp:protos */
#define RGP_SELF_ActInfoAbltEnd_23d220 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct El8 { s32 x; s32 y; };
struct El12 { u8 d[12]; };
struct BigP { struct El12 *p; s32 pad[3]; };
struct BigS { s16 v; s16 pad[7]; };
extern struct El8 *D_00481E80 __attribute__((section(".sdata")));
extern s32 D_00481E84 __attribute__((section(".sdata")));
extern struct BigP D_004BCE6C;
extern struct BigS D_004BCE92;
extern u8 D_004BCE20[];
/*rgp*/
/*rgp*/
/*rgp*/
s32 ActInfoAbltEnd_23d220(s32 a, s32 b)
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
    p = D_004BCE6C.p + D_004BCE92.v;
    r = ((struct El8 *)ActInfoAbltGetList_22ec40(p));
    ActInfoAbltSetCount_22ec30(p, (D_00481E80 + D_00481E84) - r);
    ActCfgTableSetAbltCount_223bf0(D_004BCE20, D_004BCE92.v + 1);
    return 1;
}
