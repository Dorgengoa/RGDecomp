#include "types.h"

extern void GameReqInit_20a570(void *);

struct Obj0 {
    s32 m00;
    s16 m04;
    s16 m06;
};

s32 GameReqListPushBack_20a410(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s16 t1;
    s32 *e;

    if (p1 < 0) {
        return 0;
    }
    t0 = p0->m00;
    if (t0 != 0) {
        t1 = p0->m04;
        if (t1 < p0->m06) {
            goto ok;
        }
    }
    return 0;
ok:
    e = (s32 *)((u8 *)t0 + (t1 * 20));
    GameReqInit_20a570(e);
    e[0] = p1;
    e[1] = p2;
    p0->m04 = p0->m04 + 1;
    return 1;
}
