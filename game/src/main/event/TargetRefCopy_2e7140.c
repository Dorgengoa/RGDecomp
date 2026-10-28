/* rgp:protos */
#define RGP_SELF_TargetRefCopy_2e7140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 { s16 m00; s16 m02; };
struct Obj1 { s16 m00; s16 m02; };

/*rgp*/

s32 TargetRefCopy_2e7140(struct Obj1 *p0, struct Obj0 *p1, s32 p2)
{
    s32 *src;
    s32 *dst;
    s32 n;

    TargetRefClear_2e71d0(p0);
    if (p1 != 0) {
        if (p2 != 0) {
            goto ok;
        }
    }
    return 0;
ok:
    p0->m00 = p1->m00;
    p0->m02 = p1->m02;
    src = (s32 *)((u8 *)p1 + 4);
    dst = (s32 *)((u8 *)p0 + 4);
    n = 0xB;
    do {
        *dst = *src;
        n = n - 1;
        src = src + 1;
        dst = dst + 1;
    } while (n > 0);
    return 1;
}
