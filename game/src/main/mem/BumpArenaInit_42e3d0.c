/* rgp:protos */
#define RGP_SELF_BumpArenaInit_42e3d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj;

struct Obj {
    u8 pad000[0x20];
    u32 m20;
    u32 m24;
    u32 m28;
};

s32 BumpArenaInit_42e3d0(struct Obj *p, s32 a, s32 b)
{
    u32 lo;
    u32 hi;

    p->m20 = 0;
    p->m24 = 0;
    p->m28 = 0;
    if (a == 0) {
        return 0;
    }
    lo = AlignUp_42e2d0(a, 0x10);
    hi = AlignDownAdd_42e2b0(a, b, 0x10);
    /* [[at-compare-class]]: the branch-taken condition must NOT be a bare
       `<` with the tested value on the left, or the compare lands in a GPR
       instead of retail's $at.  `hi <= lo` makes it `hi > lo`. */
    if (hi <= lo) {
        return 0;
    }
    p->m20 = lo;
    p->m24 = hi - lo;
    return 1;
}
