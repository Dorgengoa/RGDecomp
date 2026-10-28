/* rgp:protos */
#define RGP_SELF_EvTargetInit_352be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x30];
    s32 m30;
    s32 m34;
    u8 pad038[0xF8];
    s32 m130;
};

void EvTargetInit_352be0(struct Obj0 *p0)
{
    s32 l3;
    s32 l4;

    TargetRefClear_2e71d0(p0);
    p0->m30 = 0;
    p0->m34 = 0;
    XformInitIdentity_2e7970((struct Obj0 *)((u8 *)p0 + 0x38));
    XformInitIdentity_2e7970((struct Obj0 *)((u8 *)p0 + 0x80));
    l4 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l4 << 4) + 0xD0) = 0;
        *(s32 *)((u8 *)p0 + (l4 << 4) + 0xD4) = 0;
        *(s32 *)((u8 *)p0 + (l4 << 4) + 0xD8) = 0;
        *(s32 *)((u8 *)p0 + (l4 << 4) + 0xDC) = 0x3F800000;
        l3 = ((l4 + 1) < 6);
        l4 = (l4 + 1);
    } while (l3 != 0);
    p0->m130 = 0;
}
