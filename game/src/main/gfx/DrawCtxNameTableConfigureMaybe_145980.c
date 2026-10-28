/* rgp:protos */
#define RGP_SELF_DrawCtxNameTableConfigureMaybe_145980 1
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

void DrawCtxNameTableConfigureMaybe_145980(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 t0;
    s32 t1;
    struct Obj1 * t2;
    s32 t3;
    s32 t4;

    t0 = p0->m3BA0;
    if (t0 != 0) {
        NameTableAllocArrays_15a3b0(t0, p1, p2, p3);
        t1 = p0->m3BA0;
        if (t1 != 0) {
            t2 = p0->m270;
            t3 = p0->m270->m174;
            t4 = p0->m270->m170;
            NameTableSetupMaybe_15a240(t1, t4, t3);
        }
    }
}
