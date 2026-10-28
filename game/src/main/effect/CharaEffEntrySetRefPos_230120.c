/* rgp:protos */
#define RGP_SELF_CharaEffEntrySetRefPos_230120 1
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
    u8 pad000[0x60];
    u16 m60;
    u8 pad062[0xC];
    s16 m6E;
};

void CharaEffEntrySetRefPos_230120(struct Obj0 *p0, s32 p1, s32 p2)
{
    u16 t0;

    t0 = p0->m60;
    p0->m60 = (t0 | 0x100);
    p0->m6E = p1;
    StoreU32Bytes_302ef0((struct Obj0 *)((u8 *)p0 + 0x6A), p2);
}
