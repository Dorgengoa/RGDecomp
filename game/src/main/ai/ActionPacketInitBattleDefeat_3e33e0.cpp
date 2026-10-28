/* rgp:protos */
#line 1
#include "types.h"
#include "vec.h"

class VC_3e33e0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f40() { return VCM0(s32, 0x40); }
    
    s32 f48() { return VCM0(s32, 0x48); }
};

extern "C" {

typedef struct {
    u8 pad0[0xC];
    s16 unkC;
} Sub238_003E33E0;

typedef struct {
    u8 pad0[0x238];
    Sub238_003E33E0 *unk238;
} Sub20b_003E33E0;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 pad6[0xC - 6];
    s32 unkC;
    s32 unk10;
    VC_3e33e0 *unk14;
    s32 unk18;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
} Out003E33E0;

s32 CharaSysGetEncounterIdMaybe_3a36d0(Sub20b_003E33E0 *);
int CharaSysGetEncounterEntryIdMaybe_3a36f0(Sub20b_003E33E0 *);
void ActionPacketClear_3e3e90(void *);
typedef struct { u8 pad0[0x20]; Sub20b_003E33E0 *unk20; } Ctx00483990;
extern Ctx00483990 *D_00483990;

Out003E33E0 *ActionPacketInitBattleDefeat_3e33e0(Out003E33E0 *arg0, s32 arg1, s32 arg2, VC_3e33e0 *arg3, s32 arg4, s32 arg5) {
    u128 spA0;
    s32 temp_19;
    s32 var_20;
    s32 var_21;
    Sub238_003E33E0 *temp_2;
    Sub20b_003E33E0 *temp_4;

    ActionPacketClear_3e3e90((void *)arg0);
    if (D_00483990 == NULL) {
        return 0;
    }
    temp_4 = D_00483990->unk20;
    temp_2 = temp_4->unk238;
    if (temp_2 != NULL) {
        var_20 = temp_2->unkC;
    } else {
        var_20 = -1;
    }
    spA0 = CharaSysGetEncounterEntryIdMaybe_3a36f0(temp_4);
    temp_19 = CharaSysGetEncounterIdMaybe_3a36d0(D_00483990->unk20);
    arg0->unk2 = 6;
    var_21 = -1;
    arg0->unk0 = 1;
    if (arg3 != NULL) {
        if (arg3->f40() != 0) {
            var_21 = 0x22;
        } else if (arg3->f48() != 0) {
            var_21 = 0x21;
        }
    }
    if (var_21 < 0) {
        return 0;
    }
    arg0->unk3 = var_21;
    arg0->unk4 = 0x23;
    if (arg5 != 0) {
        arg0->unk5 = 0x1E;
    } else {
        arg0->unk5 = 0x1F;
    }
    arg0->unk0 = 4;
    arg0->unkC = arg1;
    arg0->unk1C = var_20;
    arg0->unk1E = (s16)spA0;
    arg0->unk20 = temp_19;
    arg0->unk10 = arg2;
    arg0->unk14 = arg3;
    arg0->unk18 = arg4;
    return arg0;
}

}
