#include "types.h"

extern s32 CharaSysBattleEndRequest_3a1f80(void *, s32, s32);
extern s32 D_004837C0;

s32 CharaSysOnBattleEndCode_3a1140(void *arg0, s32 arg1)
{
    if (D_004837C0 == 0) {
        return 0;
    }
    if (!(*(u8 *)((u8 *)arg0 + 0x24C) & 1)) {
        return 0;
    }
    switch (arg1) {
    case 1:
        CharaSysBattleEndRequest_3a1f80(arg0, 1, 0);
        break;
    case 2:
        CharaSysBattleEndRequest_3a1f80(arg0, 2, 0);
        break;
    case 4:
        CharaSysBattleEndRequest_3a1f80(arg0, 4, 0);
        break;
    case 3:
    default:
        CharaSysBattleEndRequest_3a1f80(arg0, 3, 0);
        break;
    }
    return 1;
}
