#include "types.h"

typedef struct { s32 a, b; } T_001abeb0;
typedef struct { u8 pad[0x4A0]; f32 f4A0, f4A4, f4A8, f4AC; } G_001abeb0;

extern struct { G_001abeb0 *p; s32 pad[3]; } D_0049D418;
extern f32 VariantGetFloat_15f740(T_001abeb0 *);
extern void ModelSetScale_150ff0(G_001abeb0 *, f32 *);

s32 InfoCfgScaleCmd_1abeb0(T_001abeb0 *q)
{
    G_001abeb0 *g;

    g = D_0049D418.p;
    if (g == 0) return 0;
    g->f4A0 = VariantGetFloat_15f740(q++);
    g->f4A4 = VariantGetFloat_15f740(q++);
    g->f4A8 = VariantGetFloat_15f740(q);
    g->f4AC = 1.0f;
    ModelSetScale_150ff0(g, &g->f4A0);
    return 1;
}
