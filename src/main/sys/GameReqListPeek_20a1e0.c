#include "types.h"

struct Obj1 { s32 m00; s32 m04; };
struct Obj0 { struct Obj1 *m00; s16 m04; };
struct Obj2 { s32 m00; };
struct Obj3 { s32 m00; };

#define BODY \
    if (p1 != 0) { \
        p1->m00 = p0->m00->m00; \
    } \
    if (p2 != 0) { \
        p2->m00 = p0->m00->m04; \
    } \
    return 1;

s32 GameReqListPeek_20a1e0(struct Obj0 *p0, struct Obj2 *p1, struct Obj3 *p2)
{
    if (p0->m00 != 0) {
        if (p0->m04 > 0) {
            goto ok;
        }
    }
    return 0;
ok:
    BODY
}
