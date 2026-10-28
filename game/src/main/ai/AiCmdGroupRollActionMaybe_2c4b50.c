/* rgp:protos */
#define RGP_SELF_AiCmdGroupRollActionMaybe_2c4b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB928[0x10];

s32 AiCmdGroupRollActionMaybe_2c4b50(s64 *arg0, s32 arg1)
{
    s32 sp260[0x80] __attribute__((aligned(16)));
    s32 sp60[0x80] __attribute__((aligned(16)));
    s32 n;
    s32 h;
    s32 i;
    s32 e;
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    if (arg1 == 1) {
        n = AiCollectIdsByGroup_2cd1a0(D_004DB928[0], ScriptSlotGetInt_2cc9c0(arg0), sp260, 0x80);
        h = ((s32)GetActionMgr_1fdb50());
        for (i = 0; i < n; i++) {
            e = ((s32)ActionMgrFindById_233b50(h, sp260[i]));
            if (e != 0) {
                AiRollIdleOnContactMaybe_2bb770(((s32)CharaGetAi_214a10(e)), D_004DB928[0], 0);
            }
        }
    } else {
        a = ScriptSlotGetInt_2cc9c0(arg0++);
        b = ScriptSlotGetInt_2cc9c0(arg0++);
        c = 0;
        if (arg1 >= 3) {
            c = ScriptSlotGetInt_2cc9c0(arg0);
        }
        n = AiCollectIdsByGroup_2cd1a0(D_004DB928[0], a, sp60, 0x80);
        d = D_004DB928[0];
        for (i = 0; i < n; i++) {
            e = CharaGetAiById_2cedd0(sp60[i]);
            if (e != 0) {
                AiRollActionChanceMaybe_2bb630(e, d, b, c);
            }
        }
    }
    return 1;
}
