/* rgp:protos */
#define RGP_SELF_ItemGameRecBind_3d0490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct C_FUN_003d0490 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
} C_FUN_003d0490;

typedef struct G_FUN_003d0490 {
    u8 pad000[0x174];
    s32 m174;
} G_FUN_003d0490;

typedef struct O_FUN_003d0490 {
    u8 pad000[0x14];
    s16 m14;
    u8 pad016[0x2];
    C_FUN_003d0490 *m18;
} O_FUN_003d0490;

extern G_FUN_003d0490 *D_004838F0;
/*rgp*/

s32 ItemGameRecBind_3d0490(O_FUN_003d0490 *o)
{
    C_FUN_003d0490 *p;
    s32 ok;

    if (D_004838F0 == 0) return 0;
    p = ((C_FUN_003d0490 *)GameRecGetInsectRecSlot_3ce090(D_004838F0->m174, o->m14));
    o->m18 = p;
    if (p == 0) {
        ok = 0;
        p->b0 = ok;
        return ok;
    }
    ok = 1;
    p->b0 = ok;
    return ok;
}
