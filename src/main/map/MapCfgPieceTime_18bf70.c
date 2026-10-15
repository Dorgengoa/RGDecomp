#include "types.h"

typedef struct { s32 a, b; } T_0018bf70;

extern void *D_00481258;
extern void *ListNodeGetData_18bff0(void *);
extern f32 VariantGetFloat_15f740(T_0018bf70 *);
extern void NodeObjBasicSetTimeRange_196d60(void *, f32, f32);

s32 MapCfgPieceTime_18bf70(T_0018bf70 *q)
{
    void *g;
    void *r;
    f32 a;
    f32 b;

    g = D_00481258;
    if (g == 0) return 0;
    r = ListNodeGetData_18bff0(g);
    a = VariantGetFloat_15f740(q++);
    b = VariantGetFloat_15f740(q);
    NodeObjBasicSetTimeRange_196d60(r, a, b);
    return 1;
}
