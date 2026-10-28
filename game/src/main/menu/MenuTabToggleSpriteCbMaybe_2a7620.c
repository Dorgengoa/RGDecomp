/* rgp:protos */
#define RGP_SELF_MenuTabToggleSpriteCbMaybe_2a7620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S4 { s16 a; s16 b; s16 c; s16 d; } S4;

typedef struct N {
    u8  pad000[0x10];
    s16 f10;
} N;

extern s16 D_0047ECD0;
extern s16 D_0047ECD2;
extern s16 D_0047ECD4;
extern s16 D_0047ECD6;
extern void *D_00482360;

/*rgp*/

s32 MenuTabToggleSpriteCbMaybe_2a7620(N *p)
{
    s16 t[2][2];
    s32 i;

    *(S4 *)t = *(S4 *)&D_0047ECD0;
    i = p->f10;
    UiSetSpriteU_28f930(D_00482360, 0x144, t[i][0], 0);
    UiSetSpriteU_28f930(D_00482360, 0x144, t[p->f10][1], 1);
    return 1;
}
