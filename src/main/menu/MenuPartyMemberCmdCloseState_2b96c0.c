#include "types.h"

extern void * MenuGetCursorPos_29fae0(s32);
extern void MenuWidgetFadeInOut_29fb00(s32, s32, s32, s32);
extern s32 StateMachineSetState_28ede0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004614C0[];
extern s32 D_0048235C;
extern s32 D_00482370;

struct Obj0;

struct Obj0 {
    u8 pad000[0x1];
    s8 m01;
};

s32 MenuPartyMemberCmdCloseState_2b96c0(void)
{
    s32 t0;
    struct Obj0 *r0;
    s8 t1;
    s32 t2;
    u16 t3;
    s32 t4;
    s32 r2;

    t0 = D_00482370;
    r0 = MenuGetCursorPos_29fae0(t0);
    t1 = r0->m01;
    t2 = D_00482370;
    t3 = *(u16 *)((u8 *)D_004614C0 + (t1 << 1));
    MenuWidgetFadeInOut_29fb00(t2, t3, 0, 0);
    t4 = D_0048235C;
    r2 = StateMachineSetState_28ede0(t4, 0x4B, 0);
    return 1;
}
