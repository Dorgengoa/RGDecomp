#include "types.h"
#undef NULL
#define NULL 0
#pragma opt_propagation off
struct V2 {
    f32 x;
    f32 y;
};
struct V3 {
    f32 x;
    f32 y;
    f32 z;
};
struct R {
    V2 a;
    V3 b;
};
static inline bool rd2(V2 *d, const V2 *s, s32 a2, s32 a3)
{
    if (a2 == 0 || a3 == 0 || s == NULL) {
        return false;
    }
    d->x = s->x;
    d->y = s->y;
    return true;
}
static inline bool rd3(V3 *d, const V3 *s, s32 a2, s32 a3)
{
    f32 x;
    f32 y;
    f32 z;
    d->x = 0.0f;
    d->y = 0.0f;
    d->z = 0.0f;
    if (a2 == 0 || a3 == 0 || s == NULL) {
        return false;
    }
    x = s->x;
    y = s->y;
    z = s->z;
    d->x = x;
    d->y = y;
    d->z = z;
    return true;
}
extern "C" u32 ActTimeMoveClone_2278d0(R *d, const R *s, s32 a2, s32 a3)
{
    V3 *db;
    const V3 *sb;
    d->a.x = -1.0f;
    d->a.y = -1.0f;
    d->b.x = 0.0f;
    d->b.y = 0.0f;
    d->b.z = 0.0f;
    if (a2 == 0 || a3 == 0 || s == NULL) {
        return (bool)(false);
    }
    db = &d->b;
    sb = &s->b;
    d->a.x = s->a.x;
    d->a.y = s->a.y;
    return (bool)(rd3(db, sb, a2, a3));
}
