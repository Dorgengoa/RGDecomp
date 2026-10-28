/* rgp:protos */
#define RGP_SELF_MenuItemCommandFadeState_2ad070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;
extern struct Obj0 * D_00482374;
extern u8 D_00482498;
extern u8 D_0048249C;

struct Obj0;

struct Obj0 {
    u8 pad000[0x40];
    u8 m40;
    u8 pad041[0x1];
    s16 m42;
};

s32 MenuItemCommandFadeState_2ad070(void)
{
    s32 r0;
    s32 rv9;
    struct Obj0 * t0;
    s16 t1;
    s32 rv8;
    s32 t2;
    s32 r1;
    s32 rv7;
    s32 t3;
    s32 r2;
    s32 rv6;
    s32 t4;
    s32 r3;
    s32 rv5;
    s32 t5;
    s32 r4;

    r0 = MenuItemCmdFadeSequenceStep_2adce0(0x86);
    rv9 = r0;
    if (r0 != 0) {
        t0 = D_00482374;
        t1 = D_00482374->m42;
        rv8 = rv7;
        if (t1 == 0) {
            D_00482374->m40 = 1;
            t2 = D_0048235C;
            D_0048249C = 0;
            r1 = StateMachineSetState_28ede0(t2, 0x33, 0);
            rv8 = r1;
        } else {
            rv7 = rv6;
            if (t1 == 1) {
                D_00482374->m40 = 2;
                t3 = D_0048235C;
                r2 = StateMachineSetState_28ede0(t3, 0x36, 0);
                rv7 = r2;
            } else {
                rv6 = rv5;
                if (t1 == 4) {
                    t4 = D_0048235C;
                    D_00482498 = 0;
                    r3 = StateMachineSetState_28ede0(t4, 0xB2, 0);
                    rv6 = r3;
                } else {
                    rv5 = 3;
                    if (t1 == 3) {
                        t5 = D_0048235C;
                        r4 = StateMachineSetState_28ede0(t5, 0x39, 0);
                        rv5 = r4;
                    }
                    rv6 = rv5;
                }
                rv7 = rv6;
            }
            rv8 = rv7;
        }
        rv9 = rv8;
    }
    return 1;
}
