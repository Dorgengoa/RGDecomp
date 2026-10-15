#include "types.h"

extern void * GetDrawCtx_15de80(void);
extern void NameTableFindByName_159fb0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x3BA0];
    s32 m3BA0;
};

void CBlurTexFindTex_1791a0(s32 p0)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = GetDrawCtx_15de80();
    t0 = r0->m3BA0;
    NameTableFindByName_159fb0(t0, (p0 + 8), -1);
}
