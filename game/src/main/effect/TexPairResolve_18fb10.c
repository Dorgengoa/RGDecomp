/* rgp:protos */
#define RGP_SELF_TexPairResolve_18fb10 1
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

struct Obj0;

struct Obj0 {
    u8 pad000[0x54];
    s32 m54;
    s32 m58;
};

s32 TexPairResolve_18fb10(struct Obj0 *p0)
{
    s32 r1;
    s32 r2;
    s32 r3;

    GetDrawCtx_15de80();
    r1 = GetDrawCtxNameTable_15de40();
    r2 = ((s32)NameTableFindByName_159fb0(r1, p0, -1));
    p0->m54 = r2;
    r3 = ((s32)NameTableFindByName_159fb0(r1, (struct Obj0 *)((u8 *)p0 + 0x20), -1));
    p0->m58 = r3;
    return r3;
}
