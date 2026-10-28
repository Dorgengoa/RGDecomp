/* rgp:protos */
#define RGP_SELF_HeapBlockRefSet_42e1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Obj;

struct Obj {
    s32 m00;
    s32 m04;
    s32 m08;
};

s32 HeapBlockRefSet_42e1d0(struct Obj *p, s32 a, s32 b, s32 c)
{
    HeapBlockRefRelease_42e250(p);
    if (a == 0 || b == 0 || c == 0) {
        return 0;
    }
    p->m00 = a;
    p->m04 = b;
    p->m08 = c;
    return 1;
}
