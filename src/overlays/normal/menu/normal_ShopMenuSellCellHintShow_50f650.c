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

extern Cell *func_28EA40(void *w, s32 id);
extern Ctx  *func_1FEDE0(void);
extern s32   func_3C86E0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void  normal_ShopMenuSellItemStatusLayout_50ef80(s32 a);
extern void  func_28FCD0(void *w, u16 id, s32 a, s32 b);
extern void  func_290F60(void *w, u16 id, s32 a, s32 b);
extern void  func_28FC90(void *w, u16 id, s32 a, s32 b);
extern void  func_28F930(void *w, u16 id, s32 a, s32 b);
extern void  func_290BD0(void *w, u16 id, s32 a, s32 b, s32 c, s32 d);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);

s32 normal_ShopMenuSellCellHintShow_50f650(s32 a)
{
    Cell *o;
    Ctx  *ctx;
    s32   r;
    s32   u;
    s32   v;

    if (a != 0) {
        o = func_28EA40(D_004845D0, 0x7534);
        ctx = func_1FEDE0();
        r = func_3C86E0(ctx->f18, 0, D_004845D4->f11, o->f14, o->f16, 0);
        if (r == 0) {
            return 0;
        }
        normal_ShopMenuSellItemStatusLayout_50ef80(r);
        func_28FCD0(D_004845CC, 0x5B, 0x54, 9);
        u = o->f14 * 42 - 0x14;
        v = o->f16 * 50;
        if (o->f16 < 2) {
            func_290F60(D_004845CC, 0x57, u + 0x33, v + 0xBD);
            func_290F60(D_004845CC, 0x5B, u + 0x33, v + 0xA2);
            func_28FC90(D_004845CC, 0x5B, -0xE, 9);
            func_28F930(D_004845CC, 0x5B, 0xF0, 9);
            func_290BD0(D_004845CC, 0x5B, 0x40, -1, 9, 0);
        } else {
            func_290F60(D_004845CC, 0x57, u + 0x33, v - 0x2D);
            func_290F60(D_004845CC, 0x5B, u + 0x33, v + 0x3A);
            func_28FC90(D_004845CC, 0x5B, 0x1B, 9);
            func_28F930(D_004845CC, 0x5B, 0xE0, 9);
            func_290BD0(D_004845CC, 0x5B, 0x40, 1, 9, 0);
        }
        func_290690(D_004845CC, 0x57, 1.0f, D_0047D34C, -1.0f);
        func_290690(D_004845CC, 0x5B, 1.0f, D_0047D34C, -1.0f);
    } else {
        func_290690(D_004845CC, 0x57, 0.0f, D_0047D3C8, -1.0f);
        func_290690(D_004845CC, 0x5B, 0.0f, D_0047D3C8, -1.0f);
    }
    return 1;
}
