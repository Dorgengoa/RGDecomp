#include "types.h"

extern void UiSelFrameSetRect_28db40(void *, s32, s32, s32, s32, s32, s32, s32);
extern void * GetGameData_1fede0(void);
extern s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern s32 MenuItemInfoWidgetsCache_2a65f0(void *);
extern s32 MenuItemInfoPopupShow_2a33e0(s32, s32, s32, s32, void *, s32, s32, s32, f32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482374;
extern u8 D_004DB430[];

struct Obj0;
struct Obj1;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    u8 pad006[0xA];
    s16 m10;
};

struct Obj1 {
    u8 pad000[0x18];
    s32 m18;
};

s32 MenuItemCellFocusCb_2aef30(struct Obj0 *p0)
{
    u128 v20;
    s16 t0;
    s16 t1;
    s16 t2;
    s16 t3;
    struct Obj1 *r1;
    s16 t4;
    s32 t5;
    s32 r2;
    s32 r3;
    s32 t6;
    s32 r4;

    t0 = p0->m10;
    t1 = p0->m04;
    t2 = p0->m02;
    t3 = p0->m00;
    UiSelFrameSetRect_28db40(D_004DB430, 0x78, ((t3 + (t0 * t1)) + -0x24), (t2 + -0x27), 0x28, 0x2E, 0x62, 0x49);
    r1 = GetGameData_1fede0();
    t4 = p0->m10;
    t5 = r1->m18;
    r2 = InvFindByCategoryIndex_3c86e0(t5, 4, 0, t4, 0, 0);
    r3 = MenuItemInfoWidgetsCache_2a65f0(&v20);
    t6 = D_00482374;
    r4 = MenuItemInfoPopupShow_2a33e0(t6, r2, 0x1AA, 0x1A9, &v20, 0x68, 0x15E, -1, 2.0f);
    return 1;
}
