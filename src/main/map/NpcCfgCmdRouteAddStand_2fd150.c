#include "types.h"

s32 VariantGetInt_15f780();
extern s32 D_004E6628[];
extern u8 *volatile D_004E662C[];
extern s16 D_004E6632[];
extern s16 D_004E6634[];

s32 NpcCfgCmdRouteAddStand_2fd150(s32 unused0, s32 arg1) {
    u8 *t;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004E6628[0] == 0) {
        return 0;
    }
    if (D_004E6634[0] != 0) {
        return 0;
    }
    *(s16 *)(D_004E662C[0] + 0x26) = 0;
    *(s16 *)(D_004E662C[0] + 0x24) = VariantGetInt_15f780();
    t = D_004E662C[0];
    *(u8 **)(t + 0x20) = t + 0x30;
    t = D_004E662C[0];
    D_004E662C[0] = t + 0x30;
    D_004E6632[0] += 1;
    *(s16 *)(t + 0x56) = 5;
    *(s32 *)(D_004E662C[0] + 0x20) = 0;
    return 1;
}
