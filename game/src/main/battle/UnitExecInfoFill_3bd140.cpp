#include "types.h"

typedef struct Res { u8 pad0[8]; s32 m8; s32 mC; s32 m10; } Res;
typedef struct Src { s16 m0; u8 pad2[0xA]; s32 mC; } Src;
typedef struct Rec {
    u8 pad0[4];
    s16 m4;
    s16 pad6;
    s16 m8;
    s16 padA;
    Src *mC;
    s32 m10;
    u8 pad14[8];
    s16 m1C;
    u8 pad1E[2];
    Res *m20;
    u8 pad24[8];
    s16 m2C;
    s16 pad2E;
    f32 m30;
    f32 m34;
    f32 m38;
    f32 m3C;
    f32 m40;
    s16 m44;
    s16 m46[5];
    s32 m50;
} Rec;
class VS {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Res * v31C(s32 a0, s32 a1) { return VCM(Res *, (void *, s32, s32), 0x31C, a0, a1); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s16 v388(s32 a0) { return VCM(s16, (void *, s32), 0x388, a0); }
    
    f32 v390(s32 a0) { return VCM(f32, (void *, s32), 0x390, a0); }
    
    f32 v398(s32 a0) { return VCM(f32, (void *, s32), 0x398, a0); }
    
    f32 v3A0(s32 a0) { return VCM(f32, (void *, s32), 0x3A0, a0); }
    
    f32 v3A8(s32 a0) { return VCM(f32, (void *, s32), 0x3A8, a0); }
    
    s16 v3B0(s32 a0) { return VCM(s16, (void *, s32), 0x3B0, a0); }
    
    s16 v3B8(s32 a0, s32 a1) { return VCM(s16, (void *, s32, s32), 0x3B8, a0, a1); }
    u8 pad4[8];
    s32 mC;
    u16 m10;
};
class VP {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Res * v70(s32 a0) { return VCM(Res *, (void *, s32), 0x70, a0); }
};

typedef struct Mid { u8 pad0[0xC]; VP *mC; } Mid;
typedef struct Mgr { u8 pad0[0x48]; Mid *m48; } Mgr;

extern "C" {
s32 EquipSlotGetAbilityEffectRef_3a0480(s32);
void ExecEffInfoListAdd_3a6cc0(s16 *, s32);
s32 UnitGetDefAttackIdMaybe_3bd120(VS *);
s32 UnitFindSlotByRecId_3bd840(VS *, s32);
f32 AbilityDataGetFloatRelated_3f58c0(Src *);
f32 AbilityDataGetFloatRelated_3f58f0(Src *);
f32 AbilityDataGetFloatRelated_3f5920(Src *);
f32 AbilityDataGetFloatRelated_3f5950(Src *);
s8 *AbilityDataGetElemAttack_3f5980(Src *);
s16 AbilityDataRemapInt_3f5a10(Src *, u16, s16);
extern s32 D_00483818;
extern Mgr *D_0048381C;

s32 UnitExecInfoFill_3bd140(VS *self, Rec *r)
{
    Src *src;
    Res *res;
    s8 *q;
    s32 v;
    s32 w;
    s32 i;

    if (r == 0) return 0;
    if (D_00483818 == 0) return 0;
    if (D_0048381C == 0) return 0;
    r->m1C = 0;
    switch (r->m4) {
    case 2:
        r->m1C = 2;
        r->m8 = self->mC;
        r->m20 = 0;
        v = UnitGetDefAttackIdMaybe_3bd120(self);
        if (v == 0) return 0;
        w = 0;
        if (r->mC != 0) w = r->mC->mC;
        if ((res = self->v31C(v, w)) == 0) res = D_0048381C->m48->mC->v70(0x7D0);
        r->m20 = res;
        r->m50 = res->m8;
        ExecEffInfoListAdd_3a6cc0(&r->m1C, res->m10);
        r->m2C = self->v388(1);
        r->m30 = 1.0f;
        r->m34 = self->v390(1);
        r->m38 = self->v398(1);
        r->m3C = self->v3A0(1);
        r->m40 = self->v3A8(1);
        r->m44 = self->v3B0(1);
        for (i = 0; i < 5; i++) r->m46[i] = self->v3B8(i, 1);
        break;
    case 3:
        r->m1C = 3;
        r->m8 = self->mC;
        r->m20 = 0;
        src = r->mC;
        if (src == 0) return 0;
        v = UnitFindSlotByRecId_3bd840(self, src->m0);
        if (v == 0) return 0;
        v = EquipSlotGetAbilityEffectRef_3a0480(v);
        if (v == 0) return 0;
        res = self->v31C(v, 0);
        if (res == 0) res = D_0048381C->m48->mC->v70(0x7D0);
        r->m20 = res;
        r->m50 = res->m8;
        ExecEffInfoListAdd_3a6cc0(&r->m1C, res->m10);
        r->m2C = AbilityDataRemapInt_3f5a10(src, self->m10, self->v388(1));
        r->m30 = 1.0f;
        r->m34 = AbilityDataGetFloatRelated_3f5950(src);
        r->m38 = AbilityDataGetFloatRelated_3f5920(src);
        r->m3C = AbilityDataGetFloatRelated_3f58f0(src);
        r->m40 = AbilityDataGetFloatRelated_3f58c0(src);
        r->m44 = self->v3B0(1);
        q = AbilityDataGetElemAttack_3f5980(src);
        if (q != 0) {
            for (i = 0; i < 5; i++) r->m46[i] = q[i];
        }
        if (r->m10 == 0 && res != 0) r->m10 = res->mC;
        break;
    }
    return 1;
}
}
