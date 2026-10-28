/* rgp:protos */
#define RGP_SELF_MinimapResetScroll_324900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x30];
    f32 m30;
    f32 m34;
    f32 m38;
    u8 pad03C[0x4];
    f32 m40;
    f32 m44;
    f32 m48;
};

s32 MinimapResetScroll_324900(struct Obj0 *p0)
{
    f32 t0;
    f32 t1;
    f32 t2;
    s32 r0;

    p0->m40 = 0;
    p0->m44 = 0;
    p0->m48 = 0;
    t0 = p0->m40;
    p0->m30 = t0;
    t1 = p0->m44;
    p0->m34 = t1;
    t2 = p0->m48;
    p0->m38 = t2;
    r0 = MinimapScrollToClamped_324530(p0, (struct Obj0 *)((u8 *)p0 + 0x40), 1, 0);
    return 1;
}
