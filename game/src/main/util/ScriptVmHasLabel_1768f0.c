/* rgp:protos */
#define RGP_SELF_ScriptVmHasLabel_1768f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct Obj1 { u8 pad000[0xC]; s32 m0C; s32 m10; };
struct Obj0 { u8 pad000[0x44]; struct Obj1 *m44; };
struct Obj2 { s32 m00; };

s32 ScriptVmHasLabel_1768f0(struct Obj0 *p0, s32 p1)
{
    struct Obj1 *t0;
    s32 t1, t2;
    struct Obj2 *l0;
    s32 l1;

    t0 = p0->m44;
    t1 = t0->m0C;
    l0 = (struct Obj2 *)((u8 *)t0 + t1);
    t2 = t0->m10;
    l1 = 0;
    while (l1 < t2) {
        if (l0->m00 == p1) {
            return 1;
        }
        l1 = l1 + 1;
        l0 = (struct Obj2 *)((u8 *)l0 + 8);
    }
    return 0;
}
