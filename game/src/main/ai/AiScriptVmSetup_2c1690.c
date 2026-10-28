/* rgp:protos */
#define RGP_SELF_AiScriptVmSetup_2c1690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T2c1690 {
    u8  pad00[0x34];
    s32 unk34;
} T2c1690;

/*rgp*/
/*rgp*/
/*rgp*/

s32 AiScriptVmSetup_2c1690(void *a, void *b, T2c1690 *c)
{
    f32 v;
    s32 n;
    s32 m;
    void *p;
    void *q;

    v = (f32)(c->unk34 << 4) / 5.0f;
    n = (s32)(v / 12.0f);
    m = (s32)(4.0f * v / 12.0f);
    p = MemStackAllocQw_14d950(c, (u32)(n << 3) >> 4);
    q = MemStackAllocQw_14d950(c, (u32)(m * 12) >> 4);
    ScriptVmInit_176af0(a, b, p, n, q, m);
    AiScriptVmBuildCmdTable_2c1780(a);
    return 1;
}
