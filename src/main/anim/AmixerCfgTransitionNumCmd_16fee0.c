#include "types.h"

struct Obj {
    u8 pad00[0x8];
    s32 m08;
    void *m0C;
};

extern struct Obj *D_00481188 __attribute__((section(".sdata")));
extern void *D_0048118C __attribute__((section(".sdata")));
extern s32 VariantGetInt_15f780(void);
extern void *MemStackNew_14e1b0(s32 size, void *pool);
extern void *ConstructNewArray_100710(void *p, void *fn, s32 c, s32 d, s32 n);
extern void AmixerTransCtor_16ff60(void);

s32 AmixerCfgTransitionNumCmd_16fee0(void)
{
    s32 n;
    struct Obj *o;
    void *pool;
    void *p;
    void *r;

    n = VariantGetInt_15f780();
    pool = D_0048118C;
    o = D_00481188;
    if (n > 0) {
        p = MemStackNew_14e1b0(n * 20 + 0x10, pool);
        r = ConstructNewArray_100710(p, (void *)AmixerTransCtor_16ff60, 0, 0x14, n);
        o->m0C = r;
        if (r != 0) {
            o->m08 = n;
        }
    }
    return 1;
}
