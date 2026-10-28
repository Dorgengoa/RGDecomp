/* rgp:protos */
#define RGP_SELF_MapCfgPieceTime_18bf70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_0018bf70;

extern void *D_00481258;
/*rgp*/
/*rgp*/
/*rgp*/

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
