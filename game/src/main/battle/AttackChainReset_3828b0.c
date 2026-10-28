/* rgp:protos */
#define RGP_SELF_AttackChainReset_3828b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00527020[];

void AttackChainReset_3828b0(void *p)
{
    void *a;
    void *b;

    a = GetCurrentScene_1f5be0();
    b = GameFlowGetChainTargetId_285f40();
    ParamTableSetAlpha_1cfb10(a, b, *(f32 *)((s32)p + 0x28));
    GetGameData_1fede0();
    func_4F6AB0(D_00527020);
    AttackChainStateInit_382ed0(p);
}
