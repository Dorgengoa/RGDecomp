#include "types.h"
#pragma optimization_level 3
#undef NULL
#define NULL 0

extern "C" {
class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s16 * get(s16 a0) { return VCM(s16 *, (void *, s16), 0x70, a0); }
};
typedef struct Sub { u8 pad[0x14]; Obj *unk14; } Sub;
typedef struct Mid { u8 pad[0xC]; u8 *unkC; u8 pad2[0x34 - 0x10]; Sub *unk34; } Mid;
typedef struct Arg { u8 pad[8]; Mid *unk8; } Arg;
typedef struct Ent { s16 *unk0; s16 unk4; s16 pad6; s16 unk8; } Ent;

extern void HandleEntryInit_3f4230(Ent *);
extern s32 HandleEntryRequest_3f2980(Mid *, Ent *);

s32 PlanetEntryRequestLoadMaybe_3ec600(Arg *arg0, s32 arg1) {
    s16 *temp_2;
    s16 temp_3;
    Ent *var_16;

    if (arg1 < 0) {
        return 0;
    }
    if (arg1 == 1) {
        var_16 = (Ent *)arg0->unk8->unkC;
    } else {
        var_16 = (Ent *)(arg0->unk8->unkC + 0x1C);
    }
    if (var_16 == NULL) {
        return 0;
    }
    temp_2 = var_16->unk0;
    if (temp_2 != NULL && *temp_2 == arg1) {
        temp_3 = var_16->unk4;
        if (temp_3 == 2 || temp_3 == 3 || temp_3 == 4) {
            return 1;
        }
    }
    HandleEntryInit_3f4230(var_16);
    var_16->unk0 = arg0->unk8->unk34->unk14->get((s16)arg1);
    var_16->unk4 = 1;
    var_16->unk8 = (arg1 != 1);
    return HandleEntryRequest_3f2980(arg0->unk8, var_16);
}

}
