/* rgp:protos */
#define RGP_SELF_MenuTacticsCmdInputCb_354520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;
extern struct Obj1 * D_0048237C;
extern u8 D_004B2570[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x16];
    s16 m16;
};

struct Obj1 {
    u8 pad000[0x70];
    s16 m70;
};

s32 MenuTacticsCmdInputCb_354520(struct Obj0 *p0)
{
    s32 r0;
    s32 rv5;
    s32 r1;
    s16 t0;
    s32 rv4;
    struct Obj1 * t1;
    s16 t2;
    s32 rv3;
    s32 t3;
    s32 r2;

    r0 = PadIsTriggered_1839f0(D_004B2570, 0xA000);
    rv5 = rv4;
    if (r0 != 0) {
        r1 = MenuCycleCharaSel_3537c0(p0, 0);
        rv5 = r1;
    } else {
        t0 = p0->m16;
        rv4 = 1;
        if (t0 == 1) {
            t1 = D_0048237C;
            t2 = D_0048237C->m70;
            rv3 = t2;
            if (t2 > 0) {
                t3 = D_0048235C;
                r2 = StateMachineSetState_28ede0(t3, 0x9F, 0);
                p0->m16 = 0;
                rv3 = r2;
            } else {
                p0->m16 = 0;
                rv3 = t2;
            }
            rv4 = rv3;
        }
        rv5 = rv4;
    }
    return 1;
}
