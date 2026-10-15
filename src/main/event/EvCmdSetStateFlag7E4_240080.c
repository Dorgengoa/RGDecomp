#include "types.h"

typedef struct R00240080 {
    u8 pad0[0x10];
    s32 unk10;
} R00240080;

extern R00240080 *GetGameData_1fede0(void);
extern s32 ScriptGetInt_2490f0(void);
extern void StateFlagSet_3ccb70(s32, s32, s32, s32);

s32 EvCmdSetStateFlag7E4_240080(void)
{
    s32 flag;

    flag = ScriptGetInt_2490f0() != 0;
    StateFlagSet_3ccb70(GetGameData_1fede0()->unk10, 0x7E4, flag, 1);
    return 1;
}
