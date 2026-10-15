#include "types.h"

struct Obj1 {
    s32 m00;
    s32 m04;
    s32 m08;
};

struct Obj0 {
    u8  pad000[0x270];
    struct Obj1 *m270;
};

struct Rect {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

/* Both halves are divided BEFORE either negation, and m04 is divided
   first -- so the two quotients are named locals in that order. */
void DrawEnvGetCenteredRect_145060(struct Obj0 *p0, struct Rect *p1)
{
    struct Obj1 *t;
    s32 hy;
    s32 hx;

    t = p0->m270;
    hy = t->m04 / 2;
    hx = t->m08 / 2;
    p1->m00 = -hx;
    p1->m04 = -hy;
    p1->m08 = p1->m00 + t->m08;
    p1->m0C = p1->m04 + t->m04;
}
