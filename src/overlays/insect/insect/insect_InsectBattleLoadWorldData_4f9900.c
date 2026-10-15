#include "types.h"
/* insect 0x004F9900 -- 212 bytes, 53 instructions. */

extern void *func_1FEDF0(void);
extern s32 func_3EEF10(void *p);
extern void func_3F0960(void *p, s32 k);
extern s32 insect_InsectBattleGetStep_50d6a0(void *a, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(void *a, s32 b, s32 c, s32 d);
extern void insect_InsectBattleSetState_50d8c0(void *a, s32 b, s32 c, s32 d);
extern s32 insect_InsectBattleTestFlag_50da40(void *a, s32 k);

void insect_InsectBattleLoadWorldData_4f9900(void *a)
{
    void *p;

    p = func_1FEDF0();
    if (p != 0) {
        switch (insect_InsectBattleGetStep_50d6a0(a, 1)) {
        case 1:
            func_3F0960(p, 6);
            insect_InsectBattleSetStep_50d7a0(a, 0xA, 1, -1);
            break;
        case 0xA:
            if (func_3EEF10(p) != 0) {
                insect_InsectBattleSetStep_50d7a0(a, 0, 1, -1);
                if (insect_InsectBattleTestFlag_50da40(a, 5) != 0) {
                    insect_InsectBattleSetState_50d8c0(a, 0, 1, -1);
                }
            }
            break;
        }
    }
}
