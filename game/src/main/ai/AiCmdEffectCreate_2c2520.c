/* rgp:protos */
#define RGP_SELF_AiCmdEffectCreate_2c2520 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_2c2520;
typedef struct { s32 a, b; s32 pad[6]; } L_2c2520;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern struct { s32 v; s32 pad[3]; } D_004DB928;

s32 AiCmdEffectCreate_2c2520(E8_2c2520 *p0)
{
    L_2c2520 v __attribute__((aligned(16)));
    s32 a;
    s32 b;

    a = ((s32)GetEffectMgr_2d9040());
    b = ScriptSlotGetCodeAddr_2cc980(p0++);
    EffectCreateByName_2e1020((E8_2c2520 *)&v, a, b, -1);
    EffectSetIdById_2e0080(a, v.b, D_004DB928.v);
    ScriptSlotStoreIntRef_2cc900(p0, v.b);
    return 1;
}
