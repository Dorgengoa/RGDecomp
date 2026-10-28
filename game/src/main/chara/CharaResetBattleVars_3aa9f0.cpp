/* rgp:protos */
#line 1
#include "types.h"

extern "C" {
extern void PlayStatBumpBattlesJoinedMaybe_3a1ba0(void *, s32);
extern s32 CharaIsPartyMember_3ae110(void *);
extern s32 CharaIsInParty_3ae1d0(void *);
extern s32 D_00465CD0[4];
extern s32 D_00465D28[4];
extern u8 *D_00483818;
}

struct Sub3aa9f0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void h() { VCM0(void, 0x60); }
    u8 pad[0x24];
};

class Obj3aa9f0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x47C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 g() { return VCM0(s32, 0x4C8); }
    u8 pad4[8];
    s32 unkC;
    u8 pad10[0x1B0];
    u8 a0 : 1;
    u8 a1 : 7;
    u8 pad1C1[3];
    f32 unk1C4;
    u8 c0 : 1;
    u8 c1 : 7;
    u8 pad1C9[0xB];
    s16 unk1D4;
    s16 unk1D6;
    u8 pad1D8[4];
    s32 unk1DC;
    f32 unk1E0;
    f32 unk1E4;
    f32 unk1E8;
    s32 unk1EC;
    u8 pad1F0[0x40];
    u8 *unk230;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 3;
    u8 pad235[0xD3];
    Sub3aa9f0 subs[10];
    u8 pad498[8];
    s32 unk4A0;
    u8 pad4A4[8];
    u8 unk4AC;
    u8 pad4AD;
    s16 unk4AE;
    s16 unk4B0;
    s16 unk4B2;
    u8 pad4B4[8];
    s8 unk4BC;
    u8 pad4BD[2];
    u8 unk4BF;
};

extern "C" s32 CharaResetBattleVars_3aa9f0(Obj3aa9f0 *o)
{
    s32 i;

    if (D_00483818 == 0) {
        return 0;
    }
    if (*(u8 *)(*(u8 **)(D_00483818 + 0x20) + 0x24C) & 1) {
        return 0;
    }
    o->unk1EC = 0;
    o->unk1DC = 0;
    if (CharaIsPartyMember_3ae110((void *)o) != 0) {
        o->b4 = true;
        o->b3 = true;
    } else {
        o->b4 = false;
        o->b3 = false;
    }
    if (CharaIsInParty_3ae1d0(o) != 0 && !o->b2) {
        PlayStatBumpBattlesJoinedMaybe_3a1ba0(*(u8 **)(D_00483818 + 0x20), o->unkC);
    }
    o->unk1E0 = *(s16 *)(o->unk230 + 0x20);
    o->unk1E4 = *(s16 *)(o->unk230 + 0x22);
    o->unk1E8 = *(s16 *)(o->unk230 + 0x24);
    o->a0 = true;
    o->unk1C4 = D_00465CD0[0];
    o->c0 = false;
    o->unk4BC = D_00465D28[0];
    o->unk4A0 = 0;
    o->unk1D6 = 0;
    o->unk1D4 = 0;
    o->unk4AC = 0;
    o->unk4AE = 0;
    o->unk4B0 = 0;
    o->unk4B2 = 0;
    for (i = 0; i < 10; i++) {
        o->subs[i].h();
    }
    if (o->g() != 0 && o->unk4BF < 2) {
        o->unk4BF = 2;
    }
    o->f();
    return 1;
}
