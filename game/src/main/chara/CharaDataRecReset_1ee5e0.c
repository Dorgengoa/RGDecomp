/* rgp:protos */
#define RGP_SELF_CharaDataRecReset_1ee5e0 1
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
    s16 m60;
    s16 m62;
    s16 m64;
    s16 m66;
    s32 m68;
    s16 m6C;
    u8 pad06E[0x2];
    s32 m70;
};

void CharaDataRecReset_1ee5e0(struct Obj0 *p0)
{
    p0->m62 = -1;
    p0->m60 = 0;
    p0->m66 = 0;
    p0->m68 = 0;
    p0->m64 = -1;
    p0->m6C = 0;
    p0->m70 = -1;
    MemStackClear_14dff0((struct Obj0 *)((u8 *)p0 + 8));
}
