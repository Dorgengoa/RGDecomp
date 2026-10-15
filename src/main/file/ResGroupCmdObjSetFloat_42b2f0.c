#include "types.h"

extern void * ResGroupListCurElem_42a5d0(void);
extern f32 VariantGetFloat_15f740(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x3C];
    f32 m3C;
};

s32 ResGroupCmdObjSetFloat_42b2f0(s32 p0)
{
    struct Obj0 *r0;
    f32 r1;

    r0 = ResGroupListCurElem_42a5d0();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetFloat_15f740(p0);
    r0->m3C = r1;
    return 1;
}
