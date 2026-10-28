/* rgp:protos */
#define RGP_SELF_AiScriptRunEntry_2c1550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB920 __attribute__((section(".bss")));
extern s32 D_004DB928 __attribute__((section(".bss")));
extern s32 D_004DB92C __attribute__((section(".bss")));
extern s32 D_004DB930 __attribute__((section(".bss")));

s32 AiScriptRunEntry_2c1550(s32 arg0, s32 arg1, s32 arg2) {
    s32 t16;
    s32 t2;

    t16 = GetCurrentScene_1f5be0();
    t2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), arg2));
    if (t2 == 0) {
        return 0;
    }
    D_004DB920 = t16;
    D_004DB92C = t2;
    D_004DB930 = ((s32)CharaGetAi_214a10(t2));
    D_004DB928 = arg2;
    return ScriptVmRunEntry_176940(arg0, arg1);
}
