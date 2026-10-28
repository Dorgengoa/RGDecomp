/* rgp:protos */
#define RGP_SELF_ActionResultSumByKind_3a6d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct Obj0 { u8 pad000[0x1A]; s16 m1A; };
struct Obj1 { s8 m00; u8 pad001[0x3]; s32 m04; };
s32 ActionResultSumByKind_3a6d30(struct Obj0 *p0, s32 p1)
{
    s32 n;
    struct Obj1 *e;
    s32 sum;
    s32 i;
    n = p0->m1A;
    e = (struct Obj1 *)((u8 *)p0 + 0x1C);
    sum = 0;
    i = 0;
    while (i < n) {
        if (e->m00 == p1) {
            sum = sum + e->m04;
        }
        i = i + 1;
        e = (struct Obj1 *)((u8 *)e + 8);
    }
    return sum;
}
