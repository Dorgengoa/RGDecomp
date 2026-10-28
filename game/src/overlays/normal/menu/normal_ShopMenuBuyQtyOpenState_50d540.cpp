/* rgp:protos */
#line 1
#include "types.h"
#pragma divbyzerocheck on
/* normal 0x0050D540 -- the 0x46/0x47/0x48/0x50/0x67 widget page builder.
 * 357 instructions, frame -0x80.  C++: four `jalr $25` sites, vptr at offset 0.
 *  - func_3D4D80's object: slots 0x388 / 0x38C  = virtuals #224 / #225
 *  - the object those return: slots 0x78 / 0x90 = virtuals #28 / #34
 * `break 0, 7` at 0x0050D9F8 is the divide trap: #pragma divbyzerocheck on.
 * _gp = 0x00485170. */

class VB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v28() { return VCM0(s32, 0x78); }
    
    
    
    
    
    s32 v34(s32 i) { return VCM(s32, (void *, s32), 0x90, i); }
};

class VA {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    VB * v224() { return VCM0(VB *, 0x388); }
    VB * v225() { return VCM0(VB *, 0x38C); }
};

struct Sub2 { u8 pad00[2]; s8 f02; };
struct P    { u8 pad00[0x10]; Sub2 *f10; };
struct Ctl  { P *f00; };
struct Rec  { void *f00; void *f04; u8 pad08[8]; s32 f10; s32 f14; s32 f18;
              s32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; s16 f30;
              u8 pad32[0xE]; };
struct Ent  { u8 pad00[0xC]; s16 f0C; u8 pad0E[6]; s16 f14; };

extern "C" {
extern void *D_004845CC;            /* _gp - 0xBA4 */
extern void *D_004845C8;            /* _gp - 0xBA8 */
extern void *D_004845D4;            /* _gp - 0xB9C */
extern void *D_004845D0;            /* _gp - 0xBA0 */
extern void *D_004845C4;            /* _gp - 0xBAC */
extern void *D_004845F8;            /* _gp - 0xB78 */
extern Ctl  *D_00484644;            /* _gp - 0xB2C */
extern u8    D_00484640;            /* _gp - 0xB30 */
extern f32   D_0047D460;            /* _gp - 0x7D10 */
extern f32   D_0047D4BC;            /* _gp - 0x7CB4 */
extern f32   D_0047D4C0;            /* _gp - 0x7CB0 */

void  UiSetWidgetsVisibleById_291110(void *w, s32 id, s32 a, s32 b);
void  UiSetWidgetPos_290f60(void *w, s32 id, s32 a, s32 b);
void  UiFadeWidgetAlpha_290690(void *w, s32 id, f32 a, f32 b, f32 c);
void  UiSetWidgetVisible_290010(void *w, s32 id, s32 a, s32 b);
void  MenuDrawWeaponGrowth_2a0600(void *w, void *v, P *p, s32 a, s32 b, s32 c, s32 d);
void  MenuStatCompareColors_2a0490(void *w, void *v, s32 a, s32 b, s16 *h);
void *ItemIsWeapon_3d46c0(P *p);
VA   *ItemFindOwnerChara_3d4d80(P *p, s32 a);
void  UiSetTextString_28f510(void *w, s32 id, void *a, s32 b);
void *MsgTableLookup_28aa30(void *w, s32 id);
void  memset(void *p, s32 c, s32 n);
void *UiGetWidgetSprite_28fe10(void *w, s32 id, s32 c);
void *UiGetWidgetText_28f620(void *w, s32 id, s32 c);
void  UiWindowFitToText_28d0c0(Rec *r, s32 a, s32 b, s32 c);
s32   ShopRowGetPrice_3ce6e0(Ctl *c);
s32   ShopRowGetBasePrice_3ce7f0(Ctl *c);
void  UiSetWidgetSubItemValue_291250(void *w, s32 id, s32 a, s64 v);
void  UiSetSubItemPos_28f200(void *w, s32 id, s32 x, s32 y, s32 k);
void  UiSetSpritePos_28fd10(void *w, s32 id, s32 x, s32 y, s32 k);
void  UiSetSpriteX_28fcd0(void *w, s32 id, s32 a, s32 b);
Ent  *UiEntryListFindByTag_28ea40(void *w, s32 id);
void  StateMachineSetState_28ede0(void *w, s32 id, s32 a);
void  normal_ShopMenuBuyItemStatusLayout_50be30(Ctl *c);
s32   normal_ShopMenuBuyQtyPanelLayout_50bb40(Ctl *c);

s32 normal_ShopMenuBuyQtyOpenState_50d540(s32 a0, s32 go)
{
    Rec  r __attribute__((aligned(16)));
    s16  h[6];
    P   *p;
    VA  *a;
    VB  *b;
    Ent *e;
    s32  i;
    s32  t;
    s32  n;
    s32  x;
    s32  c1;
    s32  c2;
    u8   m;
    bool ok;

    if (go != 0) {
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x48, 1, 1);
        UiFadeWidgetAlpha_290690(D_004845CC, 0x48, 1.0f, D_0047D460, 0.0f);
        UiSetWidgetPos_290f60(D_004845CC, 0x48, 0x7A, 0x6A);
        UiFadeWidgetAlpha_290690(D_004845C8, 0x2F, 0.0f, D_0047D4BC, -1.0f);
        UiFadeWidgetAlpha_290690(D_004845C8, 0x33, 0.0f, D_0047D4C0, -1.0f);
        UiFadeWidgetAlpha_290690(D_004845CC, 0x50, 1.0f, D_0047D460, 0.0f);
        p = D_00484644->f00;
        if (ItemIsWeapon_3d46c0(p) != 0) {
            UiSetWidgetVisible_290010(D_004845CC, 0x67, 1, -1);
            MenuDrawWeaponGrowth_2a0600(D_004845D4, D_004845CC, p, 0x6F, 0x6C, 0x68, 0x6E);
            a = ItemFindOwnerChara_3d4d80(p, 1);
            if (a != 0) {
                t = p->f10->f02;
                b = 0;
                if (t == 0) {
                    b = a->v224();
                } else if (t == 1) {
                    b = a->v225();
                }
                h[0] = b->v28();
                for (i = 0; i < 5; i++) {
                    h[i + 1] = b->v34(i);
                }
                MenuStatCompareColors_2a0490(D_004845D4, D_004845CC, 0x6D, 0x6E, h);
            }
            UiFadeWidgetAlpha_290690(D_004845CC, 0x67, 1.0f, D_0047D460, -1.0f);
            UiSetWidgetPos_290f60(D_004845CC, 0x50, 0x3C, 0x100);
            UiSetWidgetPos_290f60(D_004845CC, 0x67, 0xF9, 0x100);
        } else {
            UiSetWidgetPos_290f60(D_004845CC, 0x50, 0xC2, 0x100);
        }
        m = D_00484640;
        ok = false;
        if (m != 0) {
            switch (m) {
            case 1:
                UiSetTextString_28f510(D_004845CC, 0x46, MsgTableLookup_28aa30(D_004845F8, 0xD), 0);
                ok = true;
                break;
            case 2:
                UiSetTextString_28f510(D_004845CC, 0x46, MsgTableLookup_28aa30(D_004845F8, 0xE), 0);
                ok = true;
                break;
            case 3:
                UiSetTextString_28f510(D_004845CC, 0x46, MsgTableLookup_28aa30(D_004845F8, 0xF), 0);
                ok = true;
                break;
            }
        } else {
            UiSetWidgetsVisibleById_291110(D_004845CC, 0x46, 0, 1);
        }
        if (ok) {
            memset(&r, 0, 0x34);
            r.f00 = UiGetWidgetSprite_28fe10(D_004845CC, 0x46, 0);
            r.f04 = UiGetWidgetText_28f620(D_004845CC, 0x46, 0);
            r.f10 = 0xBC;
            r.f14 = 0xC;
            r.f18 = 0x10;
            r.f1C = 8;
            r.f20 = 0x46;
            r.f24 = -0x26;
            r.f28 = 0x196;
            r.f2C = 0x104;
            r.f30 = 4;
            UiWindowFitToText_28d0c0(&r, 0, 0, 0);
            c1 = ShopRowGetPrice_3ce6e0(D_00484644);
            c2 = ShopRowGetBasePrice_3ce7f0(D_00484644);
            UiSetWidgetSubItemValue_291250(D_004845CC, 0x47, 0, c2);
            UiSetWidgetSubItemValue_291250(D_004845CC, 0x47, 2, c1);
            s16 v[2] = {0};
            v[1] = -2;
            m = D_00484640;
            switch (m) {
            case 1:
                v[0] = 0x16;
                break;
            case 2:
                v[0] = 0x12;
                break;
            case 3:
                v[0] = 0x21;
                break;
            }
            UiSetSubItemPos_28f200(D_004845CC, 0x47, v[0] + 0x122, v[1] + 0x58, 0);
            UiSetSubItemPos_28f200(D_004845CC, 0x47, v[0] + 0x12E, v[1] + 0x58, 1);
            UiSetSubItemPos_28f200(D_004845CC, 0x47, v[0] + 0x140, v[1] + 0x58, 2);
            UiSetSpritePos_28fd10(D_004845CC, 0x46, v[0] + 0x12D, v[1] + 0x56, 0xD);
            n = c1;
            x = v[0] + 0x156;
            while (n >= 10) {
                n /= 10;
                x += 10;
            }
            UiSetSubItemPos_28f200(D_004845CC, 0x47, x - 10, v[1] + 0x58, 3);
            UiSetWidgetsVisibleById_291110(D_004845CC, 0x46, 1, 1);
            UiFadeWidgetAlpha_290690(D_004845CC, 0x46, 1.0f, D_0047D460, 0.0f);
        }
        UiSetSpriteX_28fcd0(D_004845CC, 0x50, -1, 9);
        normal_ShopMenuBuyItemStatusLayout_50be30(D_00484644);
        i = normal_ShopMenuBuyQtyPanelLayout_50bb40(D_00484644);
        e = UiEntryListFindByTag_28ea40(D_004845D0, 0x7533);
        e->f14 = 1;
        if (i > 0) {
            e->f0C = i;
        } else {
            e->f0C = 0x63;
        }
    }
    StateMachineSetState_28ede0(D_004845C4, 0x7539, 0);
    return 1;
}
}
