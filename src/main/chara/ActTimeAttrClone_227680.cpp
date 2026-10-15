#include "types.h"
#undef NULL
#define NULL 0
#pragma opt_propagation off
struct V2 {
    f32 x;
    f32 y;
};
struct R {
    V2 a;
    V2 b;
};
static inline bool rd2(V2 *d, const V2 *s, s32 a2, s32 a3)
{
    f32 x;
    f32 y;
    if (a2 == 0 || a3 == 0 || s == NULL) {
        return false;
    }
    x = s->x;
    y = s->y;
    d->x = x;
    d->y = y;
    return true;
}
extern "C" bool ActTimeAttrClone_227680(R *d, const R *s, s32 a2, s32 a3)
{
    V2 *db;
    const V2 *sb;
    d->a.x = -1.0f;
    d->a.y = -1.0f;
    d->b.x = 0.0f;
    d->b.y = 0.0f;
    if (a2 == 0 || a3 == 0 || s == NULL) {
        return false;
    }
    db = &d->b;
    sb = &s->b;
    d->a.x = s->a.x;
    d->a.y = s->a.y;
    *(s32 *)&d->b.x = 0;
    *(s32 *)&d->b.y = 0;
    return rd2(db, sb, a2, a3);
}
