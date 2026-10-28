#include "types.h"

struct A2 {
    u8 pad[0x28];
    s32 x28;
    inline s32 ok() { return x28 != 0; }
};


extern "C" s32 ConstructNewArray_100710(s32, s32, s32, s32, s32);
extern "C" s32 MemStackNew_14e1b0(s32, A2 *);
extern "C" void BattleEffectBurstInit_2d3f30(s32);

extern "C" void BattleEffectPoolAlloc_2d3cc0(void *arg0, s32 arg1, A2 *arg2, s32 arg3)
{
    s32 i;
    s32 temp;

    if (arg2 == NULL || !arg2->ok()) {
        return;
    }
    switch (arg1) {
    case 0:
        break;
    case 1:
        temp = ConstructNewArray_100710(MemStackNew_14e1b0((arg3 * 0x1020) + 0x10, arg2), 0, 0, 0x1020, arg3);
        *(s32 *)((u8 *)arg0 + 0x0) = temp;
        if (temp == 0) {
            return;
        }
        for (i = 0; i < arg3; i++) {
            BattleEffectBurstInit_2d3f30(*(s32 *)((u8 *)arg0 + 0x0) + (i * 0x1020));
        }
        *(s16 *)((u8 *)arg0 + 0x4) = arg3;
        break;
    case 2:
        break;
    }
}
