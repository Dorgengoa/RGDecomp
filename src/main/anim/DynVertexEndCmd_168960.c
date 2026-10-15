#include "types.h"
#pragma opt_loop_invariants off
#include "vec.h"

typedef struct {
    u8 pad0[0x90];
    s32 n90;
    void **p94;
    u8 pad98[0x8];
    s32 nA0;
    Vec4 *pA4;
    Vec4 *pA8;
    Vec4 *pAC;
} Mgr;

extern Mgr *D_00481154;

static inline s32 inRange(Mgr *m, s32 i) {
    s32 r;
    if (!(i >= 0 && i < m->nA0)) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

static inline void getA4(Mgr *m, s32 i, Vec4 *v) {
    if (inRange(m, i)) {
        *v = m->pA4[i];
    }
}

static inline void setAC(Mgr *m, s32 i, Vec4 *v) {
    if (inRange(m, i)) {
        *(u128 *)&m->pAC[i] = *(u128 *)v;
    }
}

static inline void setA8(Mgr *m, s32 i, Vec4 *v) {
    if (inRange(m, i)) {
        *(u128 *)&m->pA8[i] = *(u128 *)v;
    }
}

s32 DynVertexEndCmd_168960(void) {
    Vec4 v;
    Mgr *m;
    s32 n;
    s32 i;

    m = D_00481154;
    n = m->nA0;
    i = 0;
    if (n > 0) {
    while (i < n) {
        getA4(m, i, &v);
        setAC(m, i, &v);
        setA8(m, i, &v);
        i++;
    }
    }
    return 1;
}
