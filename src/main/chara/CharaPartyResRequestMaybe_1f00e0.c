#include "types.h"

typedef struct {
    s32 a;
    s32 b;
    s32 v[7];
} Sel;

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    void *f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
} Desc;

typedef struct {
    u8 pad0[0x18];
    s32 f18;
} Ctx;

void Sprintf_1343b8(void *, void *, void *);
void LoaderQueueAppendSeparator_1cd670(s32);
void CharaDataReleaseById_1ed850(s32, s32);
void CharaDataLoadSubRecById_1eda70(s32, Desc *);
s32 CharaDataCreate_1edab0(s32, Sel *);
void CharaResReleaseById_1f1160(s32, s32, s32);
s32 PcIdToResIndexMaybe_1f4f90(s32);
s32 GetLoaderMgr_1f59d0(void);
s32 GetCharaDataMgr_1fdb70(void);
s32 GetNpcDataHeap_1fdd70(void);
Ctx *GetGameData_1fede0(void);
s32 GetEffectMgr_2d9040(void);
void EffectRequestByName_2e29d0(void *, s32, s32, void *, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
extern u8 D_0045B770[0x20];
extern u8 D_0045B778[0x20];
extern u8 D_0045B790[0x10];
extern u8 D_0045B7A0[0x10];

void CharaPartyResRequestMaybe_1f00e0(s32 arg0, s32 arg1)
{
    Sel sel;
    Desc d;
    u8 b80[0x20];
    u8 b70[0x10];
    u8 b60[0x10];
    s32 h;
    Ctx *c;
    s32 id;
    s32 i;
    s32 t;

    h = GetLoaderMgr_1f59d0();
    c = GetGameData_1fede0();
    id = GetCharaDataMgr_1fdb70();
    PartyCountMembers_3c2010(c->f18, 1, 1);
    for (i = 1; i < 12; i++) {
        CharaResReleaseById_1f1160(arg0, arg1, i);
    }
    for (i = 0x3EB; i < 0x3F2; i++) {
        CharaDataReleaseById_1ed850(id, i);
    }
    t = GetEffectMgr_2d9040();
    EffectRequestByName_2e29d0(b70, t, GetNpcDataHeap_1fdd70(), D_0045B770, 12);
    EffectRequestByName_2e29d0(b60, t, GetNpcDataHeap_1fdd70(), D_0045B778, 12);
    sel.a = -1;
    sel.b = -1;
    for (i = 0; i < 7; i++) {
        sel.v[i] = -1;
    }
    sel.b = 3;
    sel.a = 12;
    sel.v[4] = 0x7C98;
    CharaDataReleaseById_1ed850(id, 12);
    if (CharaDataCreate_1edab0(id, &sel) == 0) {
        return;
    }
    d.f0 = 12;
    d.f1C = -1;
    d.f4 = 3;
    d.f24 = -1;
    d.f8 = 4;
    d.f30 = -1;
    d.fC = 2;
    d.f10 = -1;
    d.f14 = 0x3E9;
    d.f18 = 0;
    d.f20 = 0;
    d.f28 = 0;
    d.f2C = 0;
    d.f34 = 0;
    d.f1C = PcIdToResIndexMaybe_1f4f90(0x2AF9);
    d.f18 = b80;
    Sprintf_1343b8(b80, D_0045B790, D_0045B7A0);
    CharaDataLoadSubRecById_1eda70(id, &d);
    LoaderQueueAppendSeparator_1cd670(h);
}
