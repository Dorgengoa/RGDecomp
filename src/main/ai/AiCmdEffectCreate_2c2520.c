#include "types.h"
typedef struct { s32 a, b; } E8_2c2520;
typedef struct { s32 a, b; s32 pad[6]; } L_2c2520;
extern s32 GetEffectMgr_2d9040(E8_2c2520 *);
extern s32 ScriptSlotGetCodeAddr_2cc980(E8_2c2520 *);
extern void EffectCreateByName_2e1020(E8_2c2520 *, s32, s32, s32);
extern void EffectSetIdById_2e0080(s32, s32, s32);
extern void ScriptSlotStoreIntRef_2cc900(E8_2c2520 *, s32);
extern struct { s32 v; s32 pad[3]; } D_004DB928;

s32 AiCmdEffectCreate_2c2520(E8_2c2520 *p0)
{
    L_2c2520 v;
    s32 a;
    s32 b;

    a = GetEffectMgr_2d9040(p0);
    b = ScriptSlotGetCodeAddr_2cc980(p0++);
    EffectCreateByName_2e1020((E8_2c2520 *)&v, a, b, -1);
    EffectSetIdById_2e0080(a, v.b, D_004DB928.v);
    ScriptSlotStoreIntRef_2cc900(p0, v.b);
    return 1;
}
