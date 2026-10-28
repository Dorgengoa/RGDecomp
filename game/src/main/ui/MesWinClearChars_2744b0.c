/* rgp:protos */
#define RGP_SELF_MesWinClearChars_2744b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1924];
    s16 m1924;
    u8 pad1926[0x16];
    s32 m193C;
};

void MesWinClearChars_2744b0(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;
    s32 l2;

    l1 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l1 << 3) + 0xC4) = 0;
        *(s16 *)((u8 *)p0 + (l1 << 3) + 0xC6) = 0;
        *(s16 *)((u8 *)p0 + (l1 << 3) + 0xC8) = 0;
        *(u8 *)((u8 *)p0 + (l1 << 3) + 0xCB) = 0;
        *(u8 *)((u8 *)p0 + (l1 << 3) + 0xCA) = 0;
        l0 = ((l1 + 1) < 0x300);
        l1 = (l1 + 1);
    } while (l0 != 0);
    l2 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l2 << 1) + 0x18C4) = -1;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x18E4) = 0;
        l2 = (l2 + 1);
    } while (l2 < 0x10);
    p0->m1924 = 0;
    MesWinSetCharCount_274c80(p0, 0);
    MesWinSetScrollY_271710(p0, 0);
    MesWinSetScrollTarget_2716e0(p0, 0);
    MesWinSetPenX_272af0(p0, 0);
    MesWinSetPenY_272ac0(p0, 0);
    p0->m193C = 0;
}
