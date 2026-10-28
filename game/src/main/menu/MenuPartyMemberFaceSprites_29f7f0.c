/* rgp:protos */
#define RGP_SELF_MenuPartyMemberFaceSprites_29f7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} Elem0029F7F0;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Ctx0029F7F0;

typedef struct {
    u8 pad0[0x2C];
    s16 unk2C;
} Obj3AE3E0_0029F7F0;

typedef struct {
    u8 pad0[0x4C4];
    s32 unk4C4;
} Obj0029F7F0;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} TableElem0029F7F0;

/*rgp*/                        /* extern */
/*rgp*/          /* extern */
/*rgp*/              /* extern */
/*rgp*/                    /* extern */
/*rgp*/                         /* extern */
extern TableElem0029F7F0 D_00450820[10];

s32 MenuPartyMemberFaceSprites_29f7f0(Obj0029F7F0 *arg0, s32 arg1) {
    s32 temp_2_3;
    u32 var_20;
    u32 temp_19;
    s32 temp_18;
    s32 var_8;
    u32 var_16;
    s16 temp_7;
    Ctx0029F7F0 *temp_17;
    Elem0029F7F0 *temp_2;
    Elem0029F7F0 *temp_2_2;
    Obj3AE3E0_0029F7F0 *temp_5;

    temp_18 = arg1 & 0xFFFF;
    temp_17 = ((Ctx0029F7F0 *)GetGameData_1fede0());
    var_16 = 0;
    while ((s32)var_16 < 3) {
        temp_2 = ((Elem0029F7F0 *)UiGetWidgetSprite_28fe10(arg0->unk4C4, (temp_18 + var_16) & 0xFFFF, 0));
        if (temp_2 == NULL) {
            return 0;
        }
        temp_2->unkC = 0;
        var_16 += 1;
        temp_2->unk4 = 0;
        temp_2->unkE = 0;
        temp_2->unk6 = 0;
    }
    temp_19 = PartyCountMembers_3c2010(temp_17->unk18, 1, 1);
    var_20 = 0;
    while ((s32)var_20 < (s32)temp_19) {
        temp_2_2 = ((Elem0029F7F0 *)UiGetWidgetSprite_28fe10(arg0->unk4C4, (temp_18 + var_20) & 0xFFFF, 0));
        if (temp_2_2 == NULL) {
            return 0;
        }
        temp_2_3 = PartyGetMemberChara_3c2420(temp_17->unk18, var_20);
        if (temp_2_3 == 0) {
            return 0;
        }
        temp_5 = ((Obj3AE3E0_0029F7F0 *)CharaGetIconRecMaybe_3ae3e0(temp_2_3));
        temp_7 = temp_5->unk2C;
        var_8 = 0;
        temp_2_2->unk8 = 0;
        temp_2_2->unkA = 0;
        do {
            if (temp_7 == D_00450820[var_8].unk0) {
                temp_2_2->unk8 = D_00450820[var_8].unk2;
                temp_2_2->unkA = D_00450820[var_8].unk4;
                temp_2_2->unkC = 0x36;
                temp_2_2->unk4 = 0x36;
                temp_2_2->unkE = 0x42;
                temp_2_2->unk6 = 0x42;
            }
            var_8 += 1;
        } while (var_8 < 0xA);
        var_20 += 1;
    }
    return 1;
}
