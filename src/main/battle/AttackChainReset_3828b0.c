#include "types.h"

extern void *GetCurrentScene_1f5be0(void);
extern void *GameFlowGetChainTargetId_285f40(void);
extern void ParamTableSetAlpha_1cfb10(void *, void *, f32);
extern void GetGameData_1fede0(void);
extern void func_4F6AB0(const u8 *);
extern void AttackChainStateInit_382ed0(void *);
extern const u8 D_00527020[];

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
