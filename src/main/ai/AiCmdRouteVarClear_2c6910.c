#include "types.h"

extern s32 ScriptSlotGetInt_2cc9c0(void);
extern u8 D_004DB930[0x400];

s32 AiCmdRouteVarClear_2c6910(void)
{
    s32 idx;
    s32 i;
    u8 *base;
    u8 *q;

    if ((*(s32 *)D_004DB930) == 0) {
        return 0;
    }
    idx = ScriptSlotGetInt_2cc9c0();
    if (idx == -1) {
        base = *(u8 **)D_004DB930;
        for (i = 0; i < 8; i++) {
            q = base + i * 12;
            *(s32 *)(q + 0xD0) = -1;
            *(s32 *)(q + 0xD4) = 0;
        }
    } else {
        base = *(u8 **)D_004DB930;
        q = (u8 *)(idx * 12) + (s32)base;
        *(s32 *)(q + 0xD0) = -1;
        *(s32 *)(q + 0xD4) = 0;
    }
    return 1;
}
