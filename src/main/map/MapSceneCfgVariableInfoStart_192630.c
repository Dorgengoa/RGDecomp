#include "types.h"

typedef struct G_FUN_00192630 {
    u8 pad000[0x200];
    s32 f200;
    void *f204;
} G_FUN_00192630;

extern s32 D_0048130C;
extern G_FUN_00192630 *D_004812F4;
extern s32 D_004812F8;
extern s32 VariantGetInt_15f780(void);
extern void *MemStackNew_14e1b0(s32 sz, s32 tag);
extern void *ConstructNewArray_100710(void *m, void *f, s32 b, s32 c, s32 d);
extern void MapSceneVarInfoRecCtor_1926b0(void);

s32 MapSceneCfgVariableInfoStart_192630(void)
{
    s32 n;
    G_FUN_00192630 *g;
    void *r;

    D_0048130C = 0;
    n = VariantGetInt_15f780();
    if (n <= 0) {
        return 1;
    }
    g = D_004812F4;
    r = ConstructNewArray_100710(MemStackNew_14e1b0(n * 8 + 0x10, D_004812F8),
                     (void *)MapSceneVarInfoRecCtor_1926b0, 0, 8, n);
    g->f204 = r;
    if (r != 0) {
        g->f200 = n;
    }
    return 1;
}
