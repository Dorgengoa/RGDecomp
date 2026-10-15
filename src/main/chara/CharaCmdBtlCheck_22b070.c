#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 IsInBattle_288420(void);
extern s32 CharaCmdRunIfElseEvnt_22e480(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 CharaCmdBtlCheck_22b070(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    s32 t0;
    s32 r2;

    if (p2 != 1 && p2 != 2) {
        return 1;
    }
    r0 = GetCurrentScene_1f5be0();
    r1 = IsInBattle_288420();
    t0 = p0->m00;
    r2 = CharaCmdRunIfElseEvnt_22e480(t0, (r1 & 0xFF), p1, p2);
    return r2;
}
