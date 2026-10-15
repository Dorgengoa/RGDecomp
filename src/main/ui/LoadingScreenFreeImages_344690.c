#include "types.h"

extern void * GetDrawCtx_15de80(void);
extern void NameTableFreeGroup_158ac0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004E896C;

struct Obj0;

struct Obj0 {
    u8 pad000[0x3BA0];
    s32 m3BA0;
};

void LoadingScreenFreeImages_344690(void)
{
    struct Obj0 *r0;
    s32 t0;
    s32 t1;

    r0 = GetDrawCtx_15de80();
    t0 = r0->m3BA0;
    t1 = D_004E896C;
    NameTableFreeGroup_158ac0(t0, t1);
}
