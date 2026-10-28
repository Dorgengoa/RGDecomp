/* rgp:protos */
#define RGP_SELF_NpcCfgCmdRouteBegin_2fd4d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                                 /* extern */
/*rgp*/                               /* extern */
/*rgp*/                 /* extern */
extern s16 D_004E6626[];
extern u8 *D_004E6628[];
extern u8 *volatile D_004E662C[];
extern s16 D_004E6632[];
extern s16 D_004E6634[];

s32 NpcCfgCmdRouteBegin_2fd4d0(s32 unused0, s32 arg1) {
    s64 temp_16;
    u8 *temp_2;

    if (arg1 != 1) {
        return 0;
    }
    temp_16 = VariantGetInt_15f780((void *)unused0);
    temp_2 = ((u8 *)GroupGetRecordById_41c2a0(*(s32 *)(*(u8 **)(((u8 *)GetGameData_1fede0()) + 0x8) + 0x6C), (long long)((s16)temp_16), (long long)(-1), 1));
    if (temp_2 == 0) {
        D_004E6634[0] = 1;
        return 0;
    }
    D_004E6634[0] = 0;
    if (D_004E6626[0] != -1) {
        D_004E662C[0] = D_004E662C[0] + 0x30;
        D_004E6632[0] = D_004E6632[0] + 1;
    }
    D_004E6626[0] = (s16) temp_16;
    D_004E6628[0] = temp_2;
    *(s32 *)(temp_2 + 0x4C) = (s32) D_004E662C[0];
    *(u16 *)(D_004E662C[0] + 0x26) = 5;
    *(s32 *)(D_004E662C[0] + 0x20) = 0;
    return 1;
}
