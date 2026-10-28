/* rgp:protos */
#define RGP_SELF_BladeLineSetTex_2d5bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00461630[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x40];
    s32 m40;
    s16 m44;
};

s32 BladeLineSetTex_2d5bf0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = GetDrawCtxNameTable_15de40();
    r1 = ((s32)NameTableFindByName_159fb0(r0, D_00461630, p1));
    p0->m40 = r1;
    p0->m44 = p1;
    return r1;
}
