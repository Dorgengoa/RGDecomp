#include "types.h"

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Ctx002BA420;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
} Obj002BA420;

Ctx002BA420 *GetGameData_1fede0();                        /* extern */
s32 PartyCountReserve_3c1c20(s32, s32, s32);                    /* extern */
s32 PartyCountMembers_3c2010(s32, s32, s32);                    /* extern */
extern s16 D_0048253C;
extern s16 D_0048253E;

s32 MenuPartyCursorClampMaybe_2ba420(Obj002BA420 *arg0) {
    s16 temp_3;
    s16 temp_4;
    s16 var_2;
    s32 temp_16;
    s32 temp_2_2;
    u32 temp_4_3;
    s32 var_3;
    s64 temp_4_2;
    Ctx002BA420 *temp_2;

    temp_2 = GetGameData_1fede0();
    temp_16 = PartyCountMembers_3c2010(temp_2->unk18, 1, 1);
    temp_2_2 = PartyCountReserve_3c1c20(temp_2->unk18, 1, 1);
    temp_4 = arg0->unk12;
    if (temp_4 == 1) {
        if (temp_2_2 == 0) {
            arg0->unk12 = 0;
        } else {
            if (D_0048253E != temp_4) {
                temp_3 = arg0->unk10;
                D_0048253C = temp_3;
                if (temp_16 == 1) {
                    arg0->unk10 = 0;
                } else if (temp_3 == temp_16 - 1) {
                    arg0->unk10 = temp_2_2 - 1;
                } else if (temp_3 == 1) {
                    arg0->unk10 = (temp_2_2 - 1) / 2;
                }
            }
            if (arg0->unk10 >= temp_2_2) {
                var_2 = temp_2_2 - 1;
                arg0->unk10 = var_2;
            }
        }
    } else if (temp_4 == 0) {
        if (D_0048253E != temp_4) {
            arg0->unk10 = (s16) D_0048253C;
        }
        if (arg0->unk10 >= temp_16) {
            var_2 = temp_16 - 1;
            arg0->unk10 = var_2;
        }
    }
    return 1;
}
