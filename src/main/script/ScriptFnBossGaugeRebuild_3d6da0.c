#include "types.h"

extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

extern void VariantSetS32_36f040(void *a, s32 b, s32 c);
extern void func_507170(void);

void ScriptFnBossGaugeRebuild_3d6da0(void *a0)
{
    if (a0 == 0) {
        return;
    }
    VariantSetS32_36f040(a0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    func_507170();
    VariantSetS32_36f040(a0, 1, 1);
}
