/* rgp:protos */
#define RGP_SELF_ItemSetGameData_3d5130 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004838E8;
extern s32 D_004838EC;
extern s32 D_004838F0;
extern s32 D_004838F4;

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    u8 pad00C[0xC];
    s32 m18;
    u8 pad01C[0x4];
    s32 m20;
};

s32 ItemSetGameData_3d5130(struct Obj0 *p0)
{
    s32 rv0;
    s32 t0;
    s32 t1;
    s32 t2;

    rv0 = 1;
    if (p0 == 0) {
        rv0 = 0;
    } else {
        D_004838E8 = p0;
        t0 = p0->m08;
        D_004838EC = t0;
        t1 = p0->m18;
        D_004838F0 = t1;
        t2 = p0->m20;
        D_004838F4 = t2;
        rv0 = 1;
    }
    return rv0;
}
