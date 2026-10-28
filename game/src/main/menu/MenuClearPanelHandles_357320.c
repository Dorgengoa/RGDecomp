/* rgp:protos */
#define RGP_SELF_MenuClearPanelHandles_357320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x5C];
    s32 m5C;
    s32 m60;
    s32 m64;
};

s32 MenuClearPanelHandles_357320(struct Obj0 *p0)
{
    s32 r0;

    r0 = ((s32)memset((struct Obj0 *)((u8 *)p0 + 0x6C), 0, 8));
    p0->m5C = 0;
    p0->m60 = 0;
    p0->m64 = 0;
    return 1;
}
