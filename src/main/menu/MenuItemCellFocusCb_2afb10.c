#include "types.h"

extern s32 GetGridCellPosOffset_28ecd0(void *, void *, void *, s32, s32);
extern void UiSelFrameSetRect_28db40(void *, s32, s32, s32, s32, s32, s32, s32);
extern void * GetGameData_1fede0(void);
extern s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern s32 MenuItemInfoWidgetsCache_2a65f0(void *);
extern s32 MenuItemInfoPopupShow_2a33e0(s32, s32, s32, s32, void *, s32, s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482374;
extern u8 D_004DB430[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
    s16 m12;
};

struct Obj1 {
    u8 pad000[0x18];
    s32 m18;
};

s32 MenuItemCellFocusCb_2afb10(struct Obj0 *p0)
{
    s32 v3C;
    s32 v38;
    s32 v20[6];
    s32 r0;
    s32 t0;
    s32 t1;
    struct Obj1 *r2;
    s16 t2;
    s16 t3;
    s32 t4;
    s32 r3;
    s32 r4;
    s32 t5;
    s32 r5;

    r0 = GetGridCellPosOffset_28ecd0(p0, &v3C, &v38, 0, 0);
    t0 = v3C;
    t1 = v38;
    UiSelFrameSetRect_28db40(D_004DB430, 0x78, (t0 + -0x25), (t1 + -0x29), 0x2A, 0x30, 0x62, 0x49);
    r2 = GetGameData_1fede0();
    t2 = p0->m10;
    t3 = p0->m12;
    t4 = r2->m18;
    r3 = InvFindByCategoryIndex_3c86e0(t4, 2, 0, t2, t3, 0);
    r4 = MenuItemInfoWidgetsCache_2a65f0(v20);
    t5 = D_00482374;
    r5 = MenuItemInfoPopupShow_2a33e0(t5, r3, 0x1AA, 0x1A9, v20, 0x68, 0x15E, -1, 2.0f);
    return 1;
}
