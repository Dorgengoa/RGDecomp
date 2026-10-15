#include "types.h"
#include "vec.h"

typedef struct {
    u8 pad0[0x90];
    s32 n90;
    void **p94;
    u8 pad98[0x8];
    s32 nA0;
    Vec4 *pA4;
    u8 padA8[0x10];
    s32 *pB8;
} Mgr;

extern void FrameTransformPoint_148f60(void *, Vec4 *, Vec4 *);
extern void VariantReadVec3_15f6c0(Vec4 *, s32);
extern s32 VariantGetInt_15f780(s32);
extern Mgr *D_00481154;
extern s32 D_00481164;
extern s32 D_0048117C;

static inline void *getItem(Mgr *m, s32 i) {
    if (!(i >= 0 && i < m->n90)) {
        return 0;
    }
    return m->p94[i];
}

static inline s32 inRange(Mgr *m, s32 i) {
    s32 r;
    if (!(i >= 0 && i < m->nA0)) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

static inline void setB8(Mgr *m, s32 i, s32 v) {
    if (inRange(m, i)) {
        m->pB8[i] = v;
    }
}

static inline void setA4(Mgr *m, s32 i, Vec4 *v) {
    if (inRange(m, i)) {
        *(u128 *)&m->pA4[i] = *(u128 *)v;
    }
}

s32 DynVertexLCmd_168a40(s64 *arg0)
{
    Vec4 b;
    Vec4 a;
    s32 idx;
    void *e;

    idx = VariantGetInt_15f780((s32)arg0++);
    VariantReadVec3_15f6c0(&b, (s32)arg0);
    e = getItem(D_00481154, idx);
    if (e != 0) {
        b.w = 1.0f;
        FrameTransformPoint_148f60(e, &a, &b);
        a.w = 1.0f;
        setB8(D_00481154, D_00481164, D_0048117C);
        setA4(D_00481154, D_00481164++, &a);
    }
    return 1;
}
