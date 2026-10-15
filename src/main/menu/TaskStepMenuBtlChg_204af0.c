#include "types.h"

extern u8 D_00481C24;
extern u8 D_0047E5C4;
extern void func_4F9FB0(u8 a, u8 b);

void TaskStepMenuBtlChg_204af0(void)
{
    u8 a;
    u8 b;

    a = 0;
    b = 0;
    if (D_00481C24 == 1) {
        a = 1;
    }
    if (D_0047E5C4 == 1) {
        b = 1;
    }
    func_4F9FB0(a, b);
}
