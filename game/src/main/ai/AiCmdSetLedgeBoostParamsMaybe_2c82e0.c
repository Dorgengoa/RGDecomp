/* rgp:protos */
#define RGP_SELF_AiCmdSetLedgeBoostParamsMaybe_2c82e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_002c82e0;
typedef struct { u8 pad[0x17C]; f32 f17C; f32 f180; s32 f184; f32 f188; } G_002c82e0;

extern struct { G_002c82e0 *p; s32 pad[3]; } D_004DB930;
/*rgp*/

s32 AiCmdSetLedgeBoostParamsMaybe_2c82e0(T_002c82e0 *q)
{
    D_004DB930.p->f180 = ScriptSlotGetFloat_2cc9a0(q++);
    D_004DB930.p->f17C = ScriptSlotGetFloat_2cc9a0(q++);
    D_004DB930.p->f188 = ScriptSlotGetFloat_2cc9a0(q);
    return 1;
}
