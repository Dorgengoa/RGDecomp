#include "types.h"

extern void VecNormalize_13bd90(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x120];
    f32 m120;
};

void DynClothSetWind_169410(struct Obj0 *p0, f32 fa0)
{
    p0->m120 = fa0;
    VecNormalize_13bd90((struct Obj0 *)((u8 *)p0 + 0x130));
}
