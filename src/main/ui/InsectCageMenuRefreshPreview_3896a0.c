#include "types.h"

extern void InsectInfoWindowSetup_3919b0(s32, s32);
extern void InsectCagePreviewModelSetup_389370(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483308;

struct Obj0;

struct Obj0 {
    u8 pad000[0x96C];
    s32 m96C;
};

void InsectCageMenuRefreshPreview_3896a0(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 t2;

    if (p0 == 0) {
        t0 = D_00483308;
        InsectInfoWindowSetup_3919b0(t0, 0);
        InsectCagePreviewModelSetup_389370(p0, 0);
    } else {
        t1 = D_00483308;
        t2 = p0->m96C;
        InsectInfoWindowSetup_3919b0(t1, t2);
        InsectCagePreviewModelSetup_389370(p0, 0);
    }
}
