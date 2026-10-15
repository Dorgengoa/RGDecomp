#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern void * GetLetterbox_27bd80(void);
extern s32 LetterboxSetFade_277ea0(void *, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 EvCmdLetterboxFade_260310(s32 p0)
{
    s32 r0;
    struct Obj0 *r1;
    s32 rv4;
    s32 r2;
    s32 r3;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = GetLetterbox_27bd80();
    if (r0 != 0) {
        r1->m18 = -0x20;
        r2 = LetterboxSetFade_277ea0(r1, 1.0f, 10.0f, 0.0f);
        rv4 = r2;
    } else {
        r3 = LetterboxSetFade_277ea0(r1, 0.0f, 10.0f, 0.0f);
        rv4 = r3;
    }
    return 1;
}
