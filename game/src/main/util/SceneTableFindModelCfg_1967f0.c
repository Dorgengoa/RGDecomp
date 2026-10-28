/* rgp:protos */
#define RGP_SELF_SceneTableFindModelCfg_1967f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 SceneTableFindModelCfg_1967f0(struct Obj0 *p0, s32 p1)
{
    s32 l0;
    s32 t0;
    s32 rv2;
    s32 r1;

    if (p1 == 0) {
        return 0;
    }
    l0 = 0;
    while (l0 < p0->m00) {
        t0 = *(s32 *)((u8 *)p0 + (l0 << 4) + 0x10);
        rv2 = (l0 << 4);
        if (t0 != 0) {
            r1 = strcmp(t0, p1);
            if (r1 == 0) {
                return (s32)(struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l0 << 4)) + 0x10);
            }
            rv2 = r1;
        }
        l0 = (l0 + 1);
    }
    return 0;
}
