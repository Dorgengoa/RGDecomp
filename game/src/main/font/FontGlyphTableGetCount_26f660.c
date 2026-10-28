/* rgp:protos */
#define RGP_SELF_FontGlyphTableGetCount_26f660 1
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
    u8 pad000[0x4];
    u16 m04;
};

u16 FontGlyphTableGetCount_26f660(s32 p0)
{
    struct Obj0 *r0;
    u16 t0;

    r0 = FontGetGlyphTable_26f6a0(p0, 0);
    t0 = r0->m04;
    return t0;
}
