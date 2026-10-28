/* rgp:protos */
#define RGP_SELF_TransMenuItemMoveEndState_37df80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048470C;
extern s32 D_00484710;
extern struct Obj0 * D_00484740;

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
    s32 m24;
    s32 m28;
};

s32 TransMenuItemMoveEndState_37df80(s32 p0, s32 p1)
{
    s32 t0;
    struct Obj0 * t1;
    struct Obj0 * t2;
    struct Obj0 * t3;
    s32 t4;

    if (p1 != 0) {
        t0 = D_00484710;
        UiSetWidgetsVisibleById_291110(t0, 0x7607, 0, 1);
        t1 = D_00484740;
        D_00484740->m20 = -1;
        t2 = D_00484740;
        D_00484740->m24 = -1;
        t3 = D_00484740;
        D_00484740->m28 = -1;
    }
    t4 = D_0048470C;
    StateMachineSetState_28ede0(t4, 0x20, 1);
    return 1;
}
