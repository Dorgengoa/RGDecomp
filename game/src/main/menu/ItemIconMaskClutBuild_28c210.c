/* rgp:protos */
#define RGP_SELF_ItemIconMaskClutBuild_28c210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 memcpy(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004610D0[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x60];
    s32 m60;
};

struct Obj1 {
    s32 m00;
};

void ItemIconMaskClutBuild_28c210(s32 p0, s32 p1)
{
    s32 r0;
    struct Obj0 *r1;
    s32 t0;
    s32 r2;
    s32 l3;
    struct Obj1 *l4;
    s32 t1;

    if (p0 != 0) {
        r0 = GetDrawCtxNameTable_15de40();
        r1 = NameTableFindByName_159fb0(r0, D_004610D0, p1);
        if (r1 == 0) {
            return;
        }
        t0 = r1->m60;
        r2 = ((s32)memcpy(p0, t0, 0x400));
        l3 = 0;
        l4 = (struct Obj1 *)p0;
        do {
            t1 = l4->m00;
            if (t1 != 0) {
                l4->m00 = -0x80;
            }
            l3 = (l3 + 1);
            l4 = (struct Obj1 *)((u8 *)l4 + 4);
        } while (l3 < 0x100);
        return;
    }
}
