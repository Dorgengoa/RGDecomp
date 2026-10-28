/* rgp:protos */
#define RGP_SELF_GuardWaveEffectSetTex_2d56a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00461620[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x3C];
    s32 m3C;
    u8 pad040[0x4];
    s32 m44;
};

s32 GuardWaveEffectSetTex_2d56a0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = GetDrawCtxNameTable_15de40();
    r1 = ((s32)NameTableFindByName_159fb0(r0, D_00461620, p1));
    p0->m44 = r1;
    p0->m3C = p1;
    return r1;
}
