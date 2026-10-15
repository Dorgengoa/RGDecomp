#include "types.h"
/* insect 0x005036B0 -- C++ virtual dispatch, vptr at +0x1B0, slots 0x44 and
 * 0x54 = virtuals #15 and #19.  [[jalr-is-cpp-virtual]]
 * The `beql`-into-the-arm chain is a `switch`; arm ADDRESS order gives the
 * source case order 1, 0x1B, 0x1C, 0xB, and case 0x1B FALLS THROUGH into
 * case 0x1C.  [[m2c-switch-arm-order]] */

class VE {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(f32 t);          /* slot 0x44 */
    virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(s32 n);          /* slot 0x54 */
};

struct O {
    u8    pad000[0x870];
    void *f870;
};

extern "C" u8 D_00524E70[];
extern "C" u8 D_00524CA0[];
extern "C" s32 insect_InsectBattleGetStep_50d6a0(O *o, s32 k);
extern "C" void insect_InsectBattleSetFlag_50dad0(O *o, s32 k);
extern "C" s32 insect_InsectBattleTestFlag_50da40(O *o, s32 k);
extern "C" void insect_InsectBattleSetStep_50d7a0(O *o, s32 a, s32 b, s32 c);
extern "C" void insect_InsectBattleSetState_50d8c0(O *o, s32 a, s32 b, s32 c);
extern "C" s32 insect_InsectBattleEffectsAnySpecialActive_51d3c0(void *p);
extern "C" s32 insect_InsectBattleCamEyeSettled_4f19f0(O *o);
extern "C" s32 insect_InsectBattleCamTargetSettled_4f1980(O *o);
extern "C" VE *func_1C4A90(void *h, s32 n);
extern "C" void func_1867A0(VE *p, void *s, s32 f);
extern "C" s32 func_171D90(void *p, s32 n);

extern "C" void insect_InsectBattleFlowVictoryPose_5036b0(O *o)
{
    VE *p;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleSetFlag_50dad0(o, 0x41);
        *((u8 *)o + 0x4FBC) = *((u8 *)o + 0x4FBC) | 2;
        if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 0x17, 2, -1);
        } else if (insect_InsectBattleEffectsAnySpecialActive_51d3c0((u8 *)o + 0x5178) == 0) {
            insect_InsectBattleSetState_50d8c0(o, 0xA, 1, -1);
            insect_InsectBattleSetStep_50d7a0(o, 6, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0, 2, -1);
        }
        break;
    case 0x1B:
        if (insect_InsectBattleCamEyeSettled_4f19f0(o) != 0 && insect_InsectBattleCamTargetSettled_4f1980(o) != 0) {
            func_1867A0(func_1C4A90(o->f870, 0), D_00524E70, 6);
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        }
    case 0x1C:
        p = func_1C4A90(o->f870, 0);
        if (func_171D90((u8 *)p + 0x1F0, -1) != 0) {
            func_1867A0(p, D_00524CA0, 0);
            p->s15(1.0f);
            p->s19(0xF);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 0x17, 2, -1);
        }
        break;
    case 0xB:
        break;
    }
}
