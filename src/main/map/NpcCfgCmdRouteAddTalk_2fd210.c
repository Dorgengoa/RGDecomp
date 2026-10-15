#include "types.h"

extern void *D_004E6628[];
extern s16 D_004E6634[];
extern u8 *volatile D_004E662C[];
extern s16 D_004E6632[];

extern s16 VariantGetInt_15f780(void);

s32 NpcCfgCmdRouteAddTalk_2fd210(s32 arg0, s32 arg1) {
    u8 *e0;
    u8 *e;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004E6628[0] == 0) {
        return 0;
    }
    if (D_004E6634[0] != 0) {
        return 0;
    }
    *(s16 *)(D_004E662C[0] + 0x26) = 4;
    *(s16 *)(D_004E662C[0] + 0x24) = VariantGetInt_15f780();
    e0 = D_004E662C[0];
    *(u8 **)(e0 + 0x20) = e0 + 0x30;
    e = D_004E662C[0];
    D_004E662C[0] = e + 0x30;
    D_004E6632[0] = D_004E6632[0] + 1;
    *(s16 *)(e + 0x56) = 5;
    *(s32 *)(D_004E662C[0] + 0x20) = 0;
    return 1;
}
