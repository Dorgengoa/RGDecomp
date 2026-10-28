/* rgp:protos */
#define RGP_SELF_DrawCtxNameTableResetMaybe_1459d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x270];
    struct Obj1 *m270;
    u8 pad274[0x392C];
    s32 m3BA0;
};

struct Obj1 {
    u8 pad000[0x170];
    s32 m170;
    s32 m174;
};

void DrawCtxNameTableResetMaybe_1459d0(struct Obj0 *p0)
{
    if (p0->m3BA0 != 0) {
        NameTableSetupMaybe_15a240(p0->m3BA0, p0->m270->m170, p0->m270->m174);
    }
}
