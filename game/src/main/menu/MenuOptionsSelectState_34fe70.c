/* rgp:protos */
#define RGP_SELF_MenuOptionsSelectState_34fe70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;
extern s32 D_00482364;
extern s16 D_00482E84;
extern s16 D_00482E86;
extern s16 D_00482EA8;
extern s32 D_00482EAC;
extern u8 D_004B2570[];

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x14];
    s16 m14;
    s16 m16;
};

struct Obj1 {
    u8 pad000[0x10];
    s16 m10;
    s16 m12;
};

struct Obj2 {
    u8 pad000[0xC];
    struct Obj3 *m0C;
    u8 pad010[0x8];
    s32 m18;
};

struct Obj3 {
    u8 pad000[0x26];
    s16 m26;
};

s32 MenuOptionsSelectState_34fe70(s32 p0, s32 p1)
{
    s32 t0;
    struct Obj0 *r0;
    s16 t1;
    s32 t2;
    s16 t3;
    s32 r1;
    s32 t4;
    s32 r2;
    s32 t5;
    struct Obj1 *r3;
    s16 t6;
    struct Obj2 *r4;
    struct Obj3 * t7;
    s16 t8;
    struct Obj2 * rv6;
    s32 rv7;
    s32 t9;
    s16 t10;
    s32 r5;
    s32 t11;
    s32 t12;
    s16 t13;
    s16 t14;

    if (p1 != 0) {
        t0 = D_00482364;
        r0 = (struct Obj0 *)UiEntryListFindByTag_28ea40(t0, 0x1D);
        t1 = r0->m14;
        t2 = D_00482364;
        D_00482E84 = t1;
        t3 = r0->m16;
        D_00482E86 = t3;
        r1 = UiEntryListSelectByTag_28ea90(t2, 0x1D, 0);
    }
    t4 = D_00482364;
    r2 = MenuGridCursorInput_28e170(t4, D_004B2570, 4, 0);
    t5 = D_00482364;
    r3 = UiEntryListGetCurrentData_28ec60(t5);
    if (r2 == 2) {
        D_00482EAC = 0;
        t6 = r3->m12;
        D_00482EA8 = t6;
        r4 = (struct Obj2 *)GetGameData_1fede0();
        t7 = r4->m0C;
        t8 = r4->m0C->m26;
        rv6 = (struct Obj2 *)r4;
        if (t8 == 1) {
            t9 = r4->m18;
            t10 = D_00482EA8;
            r5 = (PartyMenuCursorSet_3c0710(t9, 0x13, t10), (s32)0);
            t11 = D_0048235C;
            rv6 = (struct Obj2 *)r5;
            rv7 = t11;
        } else {
            t12 = D_0048235C;
            rv6 = (struct Obj2 *)r4;
            rv7 = t12;
        }
        StateMachineSetState_28ede0(rv7, 0x81, 0);
    } else {
        if (r2 == 1) {
            t13 = r3->m12;
            t14 = r3->m10;
            MenuOptionsSetItem_34f5c0(t14, t13);
        }
    }
    return 1;
}
