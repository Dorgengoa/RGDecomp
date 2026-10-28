/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellCellHintShow_50f650 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050F650 -- open (a != 0) / close (a == 0) of the 0x57 + 0x5B
 * caption pair, positioned from the 0x14/0x16 cell of the 0x7534 object. */

typedef struct Cell { u8 pad00[0x14]; s16 f14; s16 f16; } Cell;
typedef struct Ctx  { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct Cfg  { u8 pad00[0x11]; s8  f11; } Cfg;

extern f32   D_0047D34C;          /* gp - 0x7E24 */
extern f32   D_0047D3C8;          /* gp - 0x7DA8 */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */
extern Cfg  *D_004845D4;          /* gp - 0xB9C  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuSellCellHintShow_50f650(s32 a)
{
    Cell *o;
    Ctx  *ctx;
    s32   r;
    s32   u;
    s32   v;

    if (a != 0) {
        o = ((Cell *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7534));
        ctx = ((Ctx *)GetGameData_1fede0());
        r = ((s32)InvFindByCategoryIndex_3c86e0(ctx->f18, 0, D_004845D4->f11, o->f14, o->f16, 0));
        if (r == 0) {
            return 0;
        }
        normal_ShopMenuSellItemStatusLayout_50ef80(r);
        UiSetSpriteX_28fcd0(D_004845CC, 0x5B, 0x54, 9);
        u = o->f14 * 42 - 0x14;
        v = o->f16 * 50;
        if (o->f16 < 2) {
            UiSetWidgetPos_290f60(D_004845CC, 0x57, u + 0x33, v + 0xBD);
            UiSetWidgetPos_290f60(D_004845CC, 0x5B, u + 0x33, v + 0xA2);
            UiSetSpriteY_28fc90(D_004845CC, 0x5B, -0xE, 9);
            UiSetSpriteU_28f930(D_004845CC, 0x5B, 0xF0, 9);
            UiSetSpriteFlags_290bd0(D_004845CC, 0x5B, (long long)(0x40), -1, 9, 0);
        } else {
            UiSetWidgetPos_290f60(D_004845CC, 0x57, u + 0x33, v - 0x2D);
            UiSetWidgetPos_290f60(D_004845CC, 0x5B, u + 0x33, v + 0x3A);
            UiSetSpriteY_28fc90(D_004845CC, 0x5B, 0x1B, 9);
            UiSetSpriteU_28f930(D_004845CC, 0x5B, 0xE0, 9);
            UiSetSpriteFlags_290bd0(D_004845CC, 0x5B, (long long)(0x40), 1, 9, 0);
        }
        UiFadeWidgetAlpha_290690(D_004845CC, 0x57, 1.0f, D_0047D34C, -1.0f);
        UiFadeWidgetAlpha_290690(D_004845CC, 0x5B, 1.0f, D_0047D34C, -1.0f);
    } else {
        UiFadeWidgetAlpha_290690(D_004845CC, 0x57, 0.0f, D_0047D3C8, -1.0f);
        UiFadeWidgetAlpha_290690(D_004845CC, 0x5B, 0.0f, D_0047D3C8, -1.0f);
    }
    return 1;
}
