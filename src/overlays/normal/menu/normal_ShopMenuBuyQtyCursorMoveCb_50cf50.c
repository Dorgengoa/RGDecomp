#include "types.h"

typedef struct CF50A {
    u8  pad00[8];
    s16 f08;
    u8  pad0A[6];
    s16 f10;
} CF50A;

typedef struct CF50C {
    u8  pad00[0x18];
    void *f18;
} CF50C;

typedef struct CF50O {
    s16 f00;
    u8  pad02[0x12];
    s8  f14;
} CF50O;

typedef struct CF50M {
    u8     pad00[0x10];
    CF50O *f10;
} CF50M;

typedef struct CF50S {
    CF50M *f00;
} CF50S;

typedef struct CF50R {
    u8  pad00[0x160];
    s64 f160;
} CF50R;

extern void  *D_004845CC;         /* gp - 0xBA4  */
extern CF50S *D_00484644;         /* gp - 0xB2C  */

extern CF50C *func_1FEDE0(void);
extern void   func_28EF30(void *w, u16 id, s32 a, s32 b, s32 c);
extern void   func_290BD0(void *w, u16 id, s32 a, s32 b, s32 c, s32 d);
extern s32    func_3CE6E0(CF50S *p);
extern s32    func_3C6460(void *ctx, s32 a, s32 b, s32 c, s32 d);
extern void   func_291250(void *w, u16 id, s32 a, s32 b);
extern void   normal_ShopMenuBuyTotalPriceSet_50bb00(s32 a, s32 b);

s32 normal_ShopMenuBuyQtyCursorMoveCb_50cf50(CF50A *a)
{
    s64 lim;
    CF50C *ctx;
    CF50O *o;
    s32 t;

    if (a->f10 <= 0) {
        a->f10 = 1;
    } else if (a->f10 > 0x63) {
        a->f10 = 0x63;
    } else if (a->f08 < a->f10) {
        a->f10 = a->f08;
    }

    ctx = func_1FEDE0();
    func_28EF30(D_004845CC, 0x4F, 0x20, 1, 0);
    func_28EF30(D_004845CC, 0x4F, 0x20, 1, 1);
    func_290BD0(D_004845CC, 0x4F, 8, 1, 2, 0);

    lim = ((CF50R *)ctx->f18)->f160;
    if (lim < a->f10 * func_3CE6E0(D_00484644)) {
        func_28EF30(D_004845CC, 0x4F, 0x20, -1, 1);
        func_290BD0(D_004845CC, 0x4F, 8, -1, 2, 0);
    }
    if (D_00484644->f00 == NULL) {
        return 0;
    }
    o = D_00484644->f00->f10;
    t = 0;
    if (o->f14 >= 0) {
        t = o->f14;
    }
    if (func_3C6460(ctx->f18, o->f00, a->f10, t, 0) == 0) {
        func_28EF30(D_004845CC, 0x4F, 0x20, -1, 0);
    }
    func_291250(D_004845CC, 0x4F, 0, a->f10);
    normal_ShopMenuBuyTotalPriceSet_50bb00(func_3CE6E0(D_00484644), a->f10);
    return 1;
}
