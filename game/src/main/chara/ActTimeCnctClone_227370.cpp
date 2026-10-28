#include "types.h"

struct C227 { s32 c; f32 v; };
struct A227 { f32 x, y, z; C227 c; };


static inline bool setA(A227 *d, A227 *s, s32 a2, s32 a3) {
    d->x = -1.0f;
    d->y = -1.0f;
    d->z = -1.0f;
    d->c.c = 0;
    d->c.v = 1.0f;
    if (a2 == 0 || a3 == 0 || s == 0 || s->c.c == 0) return false;
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
    {
        C227 *dc = &d->c;
        C227 *sc = &s->c;
        dc->c = 0;
        dc->v = 1.0f;
        if (a2 == 0 || a3 == 0 || sc == 0 || sc->c == 0) return false;
        dc->c = sc->c;
        dc->v = sc->v;
        return true;
    }
}
extern "C" u32 ActTimeCnctClone_227370(A227 *a0, A227 *a1, s32 a2, s32 a3) {
    return (bool)(setA(a0, a1, a2, a3));
}
