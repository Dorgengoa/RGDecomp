#include "types.h"


typedef struct {
    s8 t;
    u8 v[4];
} Val;

typedef struct {
    s32 unk0;
    Val *tbl;
    s32 count;
} Tbl;

s32 ScriptCallGetArgInt_3029d0(Tbl *t, s32 idx)
{
    s32 iv;
    f32 fv;
    Val *e;
    s8 ty;
    s32 res;

    if (t->tbl == 0 || idx < 0 || t->count <= idx) {
        e = 0;
    } else {
        e = &t->tbl[idx];
    }
    if (e == 0) {
        return 0;
    }
    ty = e->t;
    if (ty == 0) {
        ((u8 *)&iv)[0] = e->v[0];
        ((u8 *)&iv)[1] = e->v[1];
        ((u8 *)&iv)[2] = e->v[2];
        ((u8 *)&iv)[3] = e->v[3];
        res = iv;
    } else if (ty == 1) {
        ((u8 *)&fv)[0] = e->v[0];
        ((u8 *)&fv)[1] = e->v[1];
        ((u8 *)&fv)[2] = e->v[2];
        ((u8 *)&fv)[3] = e->v[3];
        res = (s32)fv;
    } else {
        res = 0;
    }
    return res;
}
