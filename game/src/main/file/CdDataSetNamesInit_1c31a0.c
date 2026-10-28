/* rgp:protos */
#define RGP_SELF_CdDataSetNamesInit_1c31a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void Sprintf_1343b8(void *, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045B040[];
extern u8 D_0045B050[];
extern s32 D_00481560;

struct Obj0;

struct Obj0 {
    u8 pad000[0x40];
    s32 m40;
    s32 m44;
};

void CdDataSetNamesInit_1c31a0(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = D_00481560;
    Sprintf_1343b8(p0, D_0045B040, t0);
    t1 = D_00481560;
    Sprintf_1343b8((struct Obj0 *)((u8 *)p0 + 0x20), D_0045B050, t1);
    p0->m40 = 0x46000;
    p0->m44 = 0x1A000;
}
