#include "types.h"

typedef struct Sub_FUN_002d6750 {
    u8 pad000[0x4];
} Sub_FUN_002d6750;

typedef struct Obj_FUN_002d6750 {
    u8 pad000[0xA0];
    Sub_FUN_002d6750 fA0;
    u8 pad0A4[0x1E];
    s16 fC2;
} Obj_FUN_002d6750;

extern void TrailRibbonReset_32c880(Sub_FUN_002d6750 *s);
extern void TrailRibbonSetEnabled_32c820(Sub_FUN_002d6750 *s, s32 n);
extern void TrailRibbonSetVertexColor_32c7d0(Sub_FUN_002d6750 *s, s32 n);
extern void TrailRibbonSetTextured_32c780(Sub_FUN_002d6750 *s, s32 n);

void LightningBoltInit_2d6750(Obj_FUN_002d6750 *o)
{
    o->fC2 = 0;
    TrailRibbonReset_32c880(&o->fA0);
    TrailRibbonSetEnabled_32c820(&o->fA0, 1);
    TrailRibbonSetVertexColor_32c7d0(&o->fA0, 0);
    TrailRibbonSetTextured_32c780(&o->fA0, 1);
}
