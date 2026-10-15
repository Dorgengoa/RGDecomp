#include "types.h"

extern void * MenuGetCursorPos_29fae0(s32);
extern void MenuSetCharaSel_29fa20(s32, s32);
extern void * GetGameData_1fede0(void);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyGetSlotId_3c3120(s32, s32);
extern void PartySetLeaderId_3c27c0(s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiFadeWidgetColor_2904e0(s32, s32, f32, f32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D35C;
extern f32 D_0047D678;
extern f32 D_0047D680;
extern s32 D_0047ECF0;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482370;

struct Obj0;
struct Obj1;

struct Obj0 {
    s8 m00;
    s8 m01;
};

struct Obj1 {
    u8 pad000[0x18];
    s32 m18;
};

s32 MenuLeaderChangeApplyState_2b4da0(s32 p0, s32 p1)
{
    s32 t0;
    struct Obj0 *r0;
    s8 t1;
    s32 t2;
    struct Obj1 *r2;
    s32 t3;
    s32 r3;
    s8 t4;
    s8 t5;
    s32 t6;
    s32 r4;
    s32 t7;
    s8 t8;
    s32 t9;
    s16 t10;
    f32 t11;
    s32 t12;
    f32 t13;
    s32 t14;
    f32 r8;
    f32 t15;
    s32 t16;
    f32 t17;
    s32 t18;

    if (p1 != 0) {
        t0 = D_00482370;
        r0 = (struct Obj0 *)MenuGetCursorPos_29fae0(t0);
        t1 = r0->m00;
        t2 = D_00482370;
        MenuSetCharaSel_29fa20(t2, t1);
        r2 = (struct Obj1 *)GetGameData_1fede0();
        t3 = r2->m18;
        r3 = PartyCountMembers_3c2010(t3, 1, 1);
        t4 = r0->m01;
        t5 = r0->m00;
        t6 = r2->m18;
        r4 = PartyGetSlotId_3c3120(t6, (t5 + (t4 * r3)));
        t7 = r2->m18;
        PartySetLeaderId_3c27c0(t7, r4);
        t8 = r0->m00;
        t9 = D_00482360;
        t10 = *(s16 *)((u8 *)&D_0047ECF0 + (t8 << 1));
        UiSetWidgetPos_290f60(t9, 0x132, t10, -3);
        t11 = D_0047D35C;
        t12 = D_00482360;
        t13 = D_0047D678;
        UiFadeWidgetColor_2904e0(t12, 0x132, t11, t11, t11, t11, t13);
    } else {
        t14 = D_00482360;
        r8 = UiGetWidgetAlpha_290770(t14, 0x132);
        t15 = D_0047D35C;
        if (r8 >= t15) {
            t16 = D_00482360;
            t17 = D_0047D680;
            UiFadeWidgetColor_2904e0(t16, 0x132, 1.0f, 1.0f, 1.0f, 1.0f, t17);
        } else {
            if (r8 <= 1.0f) {
                t18 = D_0048235C;
                StateMachineSetState_28ede0(t18, 0x69, 0);
            }
        }
    }
    return 1;
}
