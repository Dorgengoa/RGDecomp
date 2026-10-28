/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x0050ECC0 -- opens the item-detail page for `e`: the 0x4C name box
 * takes the entity's 0x10->0x2C string id, the 0x4A icon is centred on 0xA0
 * from its own measured width, the entity is handed the 0x527EA0 descriptor
 * through its virtual slot 17, the four 0x77..0x7A stat widgets are raised and
 * the 0x4F row is cleared and re-keyed to the entity's slot-18 value.
 *
 * TWO VIRTUAL calls (`lw $25,0($x) / lw $25,off($25) / jalr $25`), so the unit
 * is .cpp -- a struct of function pointers gives `jalr $v0`, only a real C++
 * `virtual` gives `jalr $t9`.  mwcc puts the first virtual at vtable +0x08, so
 * the slots are (0x4C-8)/4 = 17 and (0x50-8)/4 = 18.
 * `bgez / sra 1 / addiu +1 / sra 1` is a SIGNED `/ 2`, not a shift.
 * `daddu $17,$2,$0` and `sd $2,0x68($16)` sit in a call's DELAY SLOT and carry
 * the PREVIOUS statement's value, not that call's.
 * `addiu $7,$0,1` is hoisted ABOVE the k==1 test and shared by both arms of
 * func_291110's fourth argument, so only the third argument differs. */

struct Desc {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void attach(const void *p) { VCM(void, (void *, const void *), 0x4C, p); }   /* slot 17 -> vtable +0x4C */
    s32 kind(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x50, rgp_fwd1, rgp_fwd2, rgp_fwd3); }                  /* slot 18 -> vtable +0x50 */
    u8    pad04[0x10 - 4];
    void *f10;
};

typedef struct Name { u8 pad00[0x2C]; s16 f2C; } Name;
typedef struct Box  { u8 pad00[4]; s16 f04; s16 f06; u8 pad08[4]; s16 f0C; s16 f0E; } Box;
typedef struct Row  { u8 pad00[0x48]; s64 f48; u8 pad50[0x68 - 0x50]; s64 f68;
                      u8 pad70[0x76 - 0x70]; s16 f76; s16 f78; } Row;

extern "C" u8 normal_D_00527EA0[];

extern "C" void *D_004845CC;      /* gp - 0xBA4 */
extern "C" void *D_004845F8;      /* gp - 0xB78 */

extern "C" void        UiSetItemIconUv_288e50(void *p, s16 a, s32 b, s32 c);
extern "C" void        UiLayoutStringGlyphs_28a800(void *w, const void *a, s32 b, s32 c, s32 d);
extern "C" const void *MsgTableLookup_28aa30(void *p, s32 id);
extern "C" void        UiSetTextCenteredX_28f300(void *p, s32 id, s32 c, s32 d);
extern "C" s32         UiGetWidgetTextWidth_28f400(void *p, s32 id, s32 c);
extern "C" void        UiSetTextString_28f510(void *p, s32 id, const void *q, s32 d);
extern "C" void        UiSetTextX_28f590(void *p, s32 id, s32 c, s32 d);
extern "C" Row        *UiGetWidgetSubItem_28f2b0(void *p, s32 id, s32 c);
extern "C" Box        *UiGetWidgetSprite_28fe10(void *p, s32 id, s32 c);
extern "C" void        UiSetWidgetPos_290f60(void *p, s32 id, s32 x, s32 y);
extern "C" void        UiSetWidgetsVisibleById_291110(void *p, s32 id, s32 c, s32 d);
extern "C" s32         ItemGetSellPrice_3d4320(Desc *e);
extern "C" void        normal_ShopMenuSellTotalPriceSet_50ec80(s32 a, s32 b);

extern "C" s32 normal_ShopMenuSellQtyPanelLayout_50ecc0(Desc *e, int rgp_a1, int rgp_a2, int rgp_a3);

extern "C" s32 normal_ShopMenuSellQtyPanelLayout_50ecc0(Desc *e, int rgp_a1, int rgp_a2, int rgp_a3)
{
    Box *t;
    Box *u;
    Row *m;
    s32  k;
    s32  r;

    if (e == 0) {
        return 0;
    }
    k = e->kind((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    t = UiGetWidgetSprite_28fe10(D_004845CC, 0x4C, 0);
    if (t == 0) {
        return 0;
    }
    UiSetItemIconUv_288e50(t, ((Name *)e->f10)->f2C, 0x28, 0x2D);
    UiSetTextString_28f510(D_004845CC, 0x4A, MsgTableLookup_28aa30(D_004845F8, 4), 0);
    if (k == 1) {
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x4D, 0, 1);
    } else {
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x4D, 1, 1);
    }
    UiSetTextX_28f590(D_004845CC, 0x4A, 0xA0 - UiGetWidgetTextWidth_28f400(D_004845CC, 0x4A, 0) / 2, 0);
    e->attach(normal_D_00527EA0);
    UiSetTextString_28f510(D_004845CC, 0x4A, normal_D_00527EA0, 1);
    UiSetTextCenteredX_28f300(D_004845CC, 0x4A, 0xA8, 1);
    t = UiGetWidgetSprite_28fe10(D_004845CC, 0x7A, 0);
    if (t == 0) {
        return 0;
    }
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x77, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x78, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x79, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x7A, 1, 1);
    UiLayoutStringGlyphs_28a800(t, MsgTableLookup_28aa30(D_004845F8, 0x15), 0, 0, -2);
    UiSetWidgetPos_290f60(D_004845CC, 0x77, 0x70, 0x5A);
    UiSetWidgetPos_290f60(D_004845CC, 0x78, 0x3E, 0x72);
    UiSetWidgetPos_290f60(D_004845CC, 0x79, 0xB4, 0x44);
    UiSetWidgetPos_290f60(D_004845CC, 0x7A, 0x3E, 0x44);
    u = UiGetWidgetSprite_28fe10(D_004845CC, 0x4F, 0);
    if (u == 0) {
        return 0;
    }
    u->f0E = 0;
    u->f06 = 0;
    u->f0C = 0;
    u->f04 = 0;
    m = UiGetWidgetSubItem_28f2b0(D_004845CC, 0x4F, 0);
    if (m == 0) {
        return 0;
    }
    m->f76 = 0xC;
    m->f78 = 0x10;
    m->f68 = k;
    r = ((short)ItemGetSellPrice_3d4320(e));
    m->f48 = r;
    normal_ShopMenuSellTotalPriceSet_50ec80(r, 1);
    return 1;
}
