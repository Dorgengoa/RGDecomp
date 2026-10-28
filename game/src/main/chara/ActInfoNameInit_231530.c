/* rgp:protos */
#define RGP_SELF_ActInfoNameInit_231530 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct Obj1 { s8 m00; };
struct Obj0 { s32 m00; struct Obj1 *m04; };

void ActInfoNameInit_231530(struct Obj0 *p0, s32 p1, struct Obj1 *p2)
{
    p0->m00 = -1;
    p0->m04 = 0;
    if (p2 != 0) {
        if (p2->m00 != 0) {
            goto ok;
        }
        return;
    }
    return;
ok:
    p0->m00 = p1;
    p0->m04 = p2;
}
