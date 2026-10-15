#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 TargetSlotDraw_320b00(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

void TargetMngDraw2_31edb0(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;
    s32 r1;

    t0 = p0->m08;
    if (t0 != 0) {
        r0 = GetCurrentScene_1f5be0();
        r1 = TargetSlotDraw_320b00((struct Obj0 *)((u8 *)p0 + 0x10), r0);
        return;
    }
}
