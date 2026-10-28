/* rgp:protos */
#define RGP_SELF_MesWinDrawChoiceArrow_271730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 x, y, w, h; } Rect;
typedef struct { u8 r, g, b, a; u8 pad[4]; } Col;

typedef struct {
    u8 pad0[0x195C];
    u8 fade;
    u8 pad195D[0x1C30 - 0x195D];
    s32 y;
    s32 x;
    u8 pad1C38[4];
    s32 x1C3C;
} O;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0045F6E0[];
extern s32 D_0045F6E4[];
extern s32 D_0045F6E8[];
extern s32 D_0045F6EC[];
extern s8 D_00482108;

void MesWinDrawChoiceArrow_271730(O *o, s32 arg1)
{
    Col c1 __attribute__((aligned(16)));
    Col c2 __attribute__((aligned(16)));
    Rect r1 __attribute__((aligned(16)));
    Rect r2 __attribute__((aligned(16)));

    if (((unsigned char)DoubleLess_1002b0(MesWinGetOpenRate_277540((void *)o), 1.0)) != 0) {
        goto fail;
    }
    if (MesWinGetChoiceIndex_271b50(o) < 0) {
fail:
        o->x1C3C = 0;
        return;
    }
    if (arg1 == 0) {
        return;
    }
    c1.b = 0x80;
    c1.g = 0x80;
    c1.r = 0x80;
    c1.a = (o->fade * 128) / 128;
    c2.b = 0;
    c2.g = 0;
    c2.r = 0;
    c2.a = (o->fade * 64) / 128;
    if (D_00482108 == 0) {
        D_0045F6E0[0] = 0;
        D_0045F6E4[0] = 0xA2;
        D_0045F6E8[0] = 0x14;
        D_0045F6EC[0] = 0x22;
        D_00482108 = 1;
    }
    { s32 y = o->y + 5; s32 x = o->x + 5; r1.x = x; r1.y = y; r1.w = 0x14; r1.h = 0x22; }
    FontDrawGaijiSprite_26fa50(arg1, &r1, D_0045F6E0, &c2);
    { s32 y = o->y; s32 x = o->x; r2.x = x; r2.y = y; r2.w = 0x14; r2.h = 0x22; }
    FontDrawGaijiSprite_26fa50(arg1, &r2, D_0045F6E0, &c1);
}
