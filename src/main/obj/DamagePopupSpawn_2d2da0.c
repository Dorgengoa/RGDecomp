#include "types.h"

typedef struct Struct002d2da0 {
    u8 pad0[0x4];
    s32 unk4;
} Struct002d2da0;

extern void DamagePopupSetup_2d38d0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, f32 g);
extern void DamagePopupInit_2d3bf0(s32 a);
extern s32 PoolTryAllocElem_2d7ad0(s32 a, s32 b);

s32 DamagePopupSpawn_2d2da0(Struct002d2da0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 fparg0)
{
    s32 temp_2;
    s32 temp_5;

    temp_5 = arg0->unk4;
    if (temp_5 == 0) {
        return 0;
    }
    temp_2 = PoolTryAllocElem_2d7ad0(0x40, temp_5);
    if (temp_2 != 0) {
        DamagePopupInit_2d3bf0(temp_2);
        DamagePopupSetup_2d38d0(temp_2, arg1, arg2, arg3, arg4, arg5, fparg0);
    }
    return 1;
}
