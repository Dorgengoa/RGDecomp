#include "types.h"

typedef struct N50O {
    u8  pad00[8];
    s16 f08;
    u8  pad0A[6];
    s16 f10;
} N50O;

typedef struct N50W {
    u8  pad00[0x14];
    s32 f14;
} N50W;

extern f32   D_0047D4AC;          /* gp - 0x7CC4 */
extern N50W *D_004845D0;          /* gp - 0xBA0  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_0048467C;          /* gp - 0xAF4  */
extern u8    D_004B2570[];

extern void  func_28EA90(void *w, s32 id, s32 a);
extern s32   func_28E170(void *w, void *p, s32 a, s32 b);
extern N50O *func_28EC60(void *w);
extern void  func_289EF0(s32 a);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_291250(void *w, u16 id, s32 a, s32 b);
extern void *func_3D4320(void *p);
extern void  normal_ShopMenuSellTotalPriceSet_50ec80(void *p, s32 a);

s32 normal_ShopMenuSellQtyState_510050(s32 a, s32 b)
{
    N50O *o;
    s32   m;

    if (b != 0) {
        func_28EA90(D_004845D0, 0x7535, 0);
    }
    m = func_28E170(D_004845D0, D_004B2570, 1, 0);
    o = func_28EC60(D_004845D0);
    if (m == 1) {
        func_289EF0(5);
        func_290690(D_004845CC, 0x48, 0.0f, D_0047D4AC, -1.0f);
        func_28EDE0(D_004845C4, 0x7548, 0);
    } else if (m == 2) {
        func_289EF0(6);
        func_28EDE0(D_004845C4, 0x7547, 0);
    } else if (D_004845D0->f14 == 1) {
        o->f10 += 0xA;
        if (o->f08 < o->f10) {
            o->f10 = o->f08;
        }
        func_291250(D_004845CC, 0x4F, 0, o->f10);
        normal_ShopMenuSellTotalPriceSet_50ec80(func_3D4320(D_0048467C), o->f10);
    } else if (D_004845D0->f14 == 2) {
        o->f10 -= 0xA;
        if (o->f10 <= 0) {
            o->f10 = 1;
        }
        func_291250(D_004845CC, 0x4F, 0, o->f10);
        normal_ShopMenuSellTotalPriceSet_50ec80(func_3D4320(D_0048467C), o->f10);
    }
    return 1;
}
