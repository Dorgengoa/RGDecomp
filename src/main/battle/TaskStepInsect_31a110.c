#include "types.h"

extern void InsectBattleLoadStep_319780(void);
extern s32 InsectBattleGet_31a8d0(void);
extern void func_50A810(s32 arg0);
extern void func_50A9F0(s32 arg0);
extern void func_50B5E0(s32 arg0);
extern void func_50B630(s32 arg0);
extern void func_50B6C0(s32 arg0);
extern void func_50B8D0(s32 arg0);
extern void func_50C100(s32 arg0);
extern void func_50C4B0(s32 arg0);
extern s32 func_50DA40(s32 arg0, s32 arg1);

void TaskStepInsect_31a110(void)
{
    s32 v;

    v = InsectBattleGet_31a8d0();
    if (v != 0) {
        func_50A810(v);
        func_50C4B0(v);
        if (func_50DA40(v, 0x2B) != 0) {
            func_50A9F0(v);
        } else {
            func_50B5E0(v);
            func_50B8D0(v);
            func_50C100(v);
            func_50B6C0(v);
            func_50B630(v);
        }
    }
    InsectBattleLoadStep_319780();
}
