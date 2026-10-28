/* rgp:protos */
#define RGP_SELF_InfoCfgBodySizeCmd_1abf30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_001abf30;
typedef struct { u8 pad[0x4C8]; f32 f4C8; f32 f4CC; f32 f4D0; } G_001abf30;

extern struct { G_001abf30 *p; s32 pad[3]; } D_0049D418;
/*rgp*/

s32 InfoCfgBodySizeCmd_1abf30(T_001abf30 *q)
{
    G_001abf30 *g;

    g = D_0049D418.p;
    if (g == 0) return 0;
    g->f4CC = (f32)VariantGetInt_15f780(q++);
    g->f4C8 = (f32)VariantGetInt_15f780(q++);
    g->f4D0 = (f32)VariantGetInt_15f780(q);
    return 1;
}
