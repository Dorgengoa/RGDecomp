/* rgp:protos */
#define RGP_SELF_HeapBlockRefRebind_42e150 1
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

s32 HeapBlockRefRebind_42e150(struct Obj *p, s32 a, s32 b, s32 c)
{
    if (a == 0 || b == 0 || c == 0) {
        return 0;
    }
    MemMove_42cc30(b, p->m04, p->m08);
    p->m00 = a;
    p->m08 = c;
    p->m04 = b;
    return 1;
}
