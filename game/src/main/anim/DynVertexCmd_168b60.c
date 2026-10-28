/* rgp:protos */
#define RGP_SELF_DynVertexCmd_168b60 1
#define RGP_SELF_getItem 1
#define RGP_SELF_inRange 1
#define RGP_SELF_setA4 1
#define RGP_SELF_setB8 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
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

s32 DynVertexCmd_168b60(s64 *arg0)
{
    Vec4 b __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    s32 idx;
    void *e;

    idx = VariantGetInt_15f780((s32)arg0++);
    VariantReadVec3_15f6c0(&b, (s32)arg0);
    e = getItem(D_00481154, idx);
    if (e != 0) {
        FrameGetWorldPos_148f30(e,&a);
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        a.w = 1.0f;
        setB8(D_00481154, D_00481164, D_0048117C);
        setA4(D_00481154, D_00481164++, &a);
    }
    return 1;
}
