#pragma opt_lifetimes off
#define KV 1
#define KC 1
#define KB 2
#define KF 1
#include "types.h"
#pragma opt_propagation off
#ifndef KA
#define KA 0
#endif

typedef unsigned __int128 u128;
struct Vec4 { f32 x, y, z, w; };

class Chr {
public:
#define VS(n) virtual void n()
    VS(v00); VS(v01); VS(v02); VS(v03); VS(v04); VS(v05); VS(v06); VS(v07); VS(v08); VS(v09);
    VS(v10); VS(v11); VS(v12); VS(v13); VS(v14); VS(v15); VS(v16); VS(v17); VS(v18); VS(v19);
    VS(v20);
    virtual s16 getId();
    virtual char *getName();
    VS(v23); VS(v24); VS(v25); VS(v26); VS(v27); VS(v28); VS(v29);
    VS(v30); VS(v31); VS(v32); VS(v33); VS(v34); VS(v35); VS(v36); VS(v37); VS(v38); VS(v39);
    VS(v40); VS(v41); VS(v42); VS(v43); VS(v44); VS(v45); VS(v46); VS(v47); VS(v48); VS(v49);
    VS(v50); VS(v51); VS(v52); VS(v53); VS(v54); VS(v55);
    virtual s16 getLv();
};

class Actor {
public:
    u8 pad[0xC0];
    VS(v00); VS(v01); VS(v02); VS(v03); VS(v04); VS(v05); VS(v06); VS(v07); VS(v08); VS(v09);
    VS(v10); VS(v11); VS(v12); VS(v13); VS(v14); VS(v15); VS(v16); VS(v17); VS(v18); VS(v19);
    VS(v20); VS(v21); VS(v22); VS(v23); VS(v24); VS(v25); VS(v26); VS(v27); VS(v28); VS(v29);
    VS(v30); VS(v31); VS(v32); VS(v33); VS(v34); VS(v35); VS(v36); VS(v37); VS(v38);
    virtual void getPos(Vec4 *);
    virtual void getRot(Vec4 *);
};

struct Ent {
    char name[16];
    s16 id;
    s16 v12;
    s16 lv;
    s16 pad16;
    f32 x, y, z, ang;
};

struct Hdr {
    s64 t0;
    s64 t8;
    s16 n;
    s16 pad12;
    Ent ents[10];
    f32 pp[6];
    s16 h1bc;
    s16 h1be;
    s16 h1c0;
    s16 h1c2;
    char name[0x80];
    s16 h244;
};

extern "C" {
void SlotRecordReset_3eeca0(u8 *);
u8 *GetCurrentScene_1f5be0(void);
u8 *GroupGetRecordById_425590(s32, s16);
s32 DoubleToU64_13ab28(s64);
s64 U64ToDouble_100370(s32);
s32 PartyCountMembers_3c2010(u8 *, s32, s32);
s32 PartyCountReserve_3c1c20(u8 *, s32, s32);
s32 PartyGetLeaderIndex_3c2850(u8 *);
Chr *PartyGetSlotChara_3c2fb0(u8 *, s32);
u8 *CharaGetIconRecMaybe_3ae3e0(Chr *);
void strcpy(char *, const char *);
void PartyFormationPosCalcMaybe_1fff00(Vec4 *, Vec4 *, s32, s32);
void PartyGetSavedMemberPos_3cafa0(u8 *, s32, Vec4 *);
f32 PartyGetSavedMemberRot_3caf70(u8 *, s32);
Actor *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
s16 StateGetChapter_3cd5b0(s32);
s16 ProgressValueGet_3cd2c0(s32, s16, s16);
s32 InvHasItemInCategory_3c7f40(u8 *, s32, s32, s32);
u8 *ProgressGetChapterRec_3cd550(s32);
s16 StateVarGet_3ccac0(s32, s32);
s32 PartyGetLocationGroupIdMaybe_3cb150(u8 *);
s32 PartyGetFloorNum_3cb000(u8 *);
void Sprintf_1343b8(char *, void *, s32, s32);
s32 StateFlagTest_3ccd70(s32, s32);
void SaveHeaderFormatLocationMaybe_3ee800(u8 *, u8 *);
void UnlockMaskBuildFromInv_3e4020(u8 *, u8 *);
s32 InvGetCageItem_3c8040(u8 *, s32);
u8 InsectRecSlotCountItems_3cfb80(s32, s32);
char *MsgGetTextByIndex_279040(s32);
u128 Md5DigestQword_369050(u8 *, s32);
extern const s32 D_004658D8[];
extern const s32 D_004658E0[];
extern u8 D_00466B70[0x400];
extern const f32 D_0047D248 __attribute__((section(".sdata")));
extern const f32 D_0047D364 __attribute__((section(".sdata")));
extern const f32 D_0047D368 __attribute__((section(".sdata")));
extern const f32 D_0047D36C __attribute__((section(".sdata")));
extern const f32 D_0047D370 __attribute__((section(".sdata")));
extern const f32 D_0047D374 __attribute__((section(".sdata")));
extern const f32 D_0047D378 __attribute__((section(".sdata")));
extern const f32 D_0047D37C __attribute__((section(".sdata")));
extern const f32 D_0047D380 __attribute__((section(".sdata")));
extern const f32 D_0047D384 __attribute__((section(".sdata")));
extern const f32 D_0047D388 __attribute__((section(".sdata")));
extern const f32 D_0047D38C __attribute__((section(".sdata")));
extern const f32 D_0047D390 __attribute__((section(".sdata")));
extern const f32 D_0047D394 __attribute__((section(".sdata")));
extern const f32 D_0047D398 __attribute__((section(".sdata")));
extern const f32 D_0047D39C __attribute__((section(".sdata")));
extern const f32 D_0047D3A0 __attribute__((section(".sdata")));
extern const f32 D_0047D3A4 __attribute__((section(".sdata")));
extern const f32 D_0047D3A8 __attribute__((section(".sdata")));
extern const f32 D_0047D3AC __attribute__((section(".sdata")));
extern const f32 D_0047D3B0 __attribute__((section(".sdata")));
}

#define F(p, T, o) (*(T *)((u8 *)(p) + (o)))
struct Rec { s16 id; s16 pad2; char *name; u8 pad8[0xE]; s16 m16; u8 pad18[8]; f32 x, y, z, w; };
struct Self { u8 pad0[8]; u8 *m8; u8 *mc; s32 m10; u8 pad14[4]; u8 *m18; u8 pad1c[8]; u8 *m24; };

#if KF
extern "C" s32 SaveHeaderBuild_3e5520(Self *self, u8 *sv, bool flag)
#else
extern "C" s32 SaveHeaderBuild_3e5520(Self *self, u8 *sv, u8 flag)
#endif
{
    Vec4 pos;
    Vec4 rot;
    Vec4 a;
    Vec4 b;
#if KV
    s32 lead;
    s32 i5;
#else
    s32 i5;
    s32 lead;
#endif
    u8 *r;
    u8 *sys;
    Rec *rec;
    Hdr *hdr;
    s32 k;
    s32 k2;
    s32 k1;
    s32 i;
    s32 cnt;
#if KC
    Ent *ent;
    Chr *ch;
#else
    Chr *ch;
    Ent *ent;
#endif
    Actor *actor;
    f32 *pp;
    u8 *q;
    u8 *nm;
    s32 n;
    u16 *fl;
    u8 *bb;
    s32 k3;
    s32 m;

    if (sv == 0) return 0;
    SlotRecordReset_3eeca0(sv);
    sys = GetCurrentScene_1f5be0();
    i5 = F(self->m18, s16, 0xF8);
    rec = (Rec *)GroupGetRecordById_425590(F(self->m8, s32, 0x74), i5);
    F(sv, s16, 0) = -1;
    F(sv, s16, 2) = -1;
    F(sv, s16, 4) = D_004658D8[0];
    F(sv, s16, 6) = D_004658E0[0];
    F(sv, s32, 8) = 0;
    hdr = (Hdr *)(sv + 0x50);
    hdr->t0 = U64ToDouble_100370(DoubleToU64_13ab28(F(self->mc, s64, 8)));
    hdr->t8 = F(self->m18, s64, 0x160);
    k1 = 0;
    do {
        ent = &hdr->ents[k1];
        ent->name[0] = 0;
        ent->id = -1;
        ent->v12 = -1;
        ent->lv = 0;
        *(s32 *)&ent->x = 0;
        *(s32 *)&ent->y = 0;
        *(s32 *)&ent->z = 0;
        *(s32 *)&ent->ang = 0;
        k1++;
    } while (k1 < 3);
    {
        u8 *g = self->m18;
        n = PartyCountMembers_3c2010(g, 1, 1);
        hdr->n = n + PartyCountReserve_3c1c20(g, 1, 1);
    }
    { s32 t2 = PartyGetLeaderIndex_3c2850(self->m18); lead = t2; }
    cnt = 0;
    for (i = 0; i < hdr->n; i++) {
        ch = PartyGetSlotChara_3c2fb0(self->m18, i);
        if (ch == 0) continue;
        r = CharaGetIconRecMaybe_3ae3e0(ch);
        if (r == 0) continue;
        ent = &hdr->ents[i];
        strcpy(ent->name, ch->getName());
        ent->id = ch->getId();
        ent->v12 = F(r, s16, 0x2C);
        ent->lv = ch->getLv();
        if (rec != 0) {
            if (i == lead) {
                pos.x = rec->x;
                pos.y = rec->y;
                pos.z = rec->z;
                rot.y = rec->w;
            } else {
                PartyFormationPosCalcMaybe_1fff00(&pos, &rot, i5, cnt);
                cnt++;
            }
        } else {
            PartyGetSavedMemberPos_3cafa0(self->m18, i, &pos);
            rot.y = PartyGetSavedMemberRot_3caf70(self->m18, i);
        }
        ent->x = pos.x;
        ent->y = pos.y;
        ent->z = pos.z;
        ent->ang = rot.y;
    }
    pp = (f32 *)(sv + 0x1F4);
    actor = 0;
    if (sys != 0) actor = ObjRecGetLiveObject_1c3bc0(sys, F(sys, s32, 0x4344));
    if (actor != 0) {
        actor->getPos(&a);
        actor->getRot(&b);
        pp[0] = a.x;
        pp[1] = a.y;
        pp[2] = a.z;
        pp[3] = b.x;
        pp[4] = b.y;
        pp[5] = b.z;
    } else {
        *(s32 *)&pp[0] = 0;
        *(s32 *)&pp[1] = 0;
        *(s32 *)&pp[2] = 0;
        *(s32 *)&pp[3] = 0;
        *(s32 *)&pp[4] = 0;
        *(s32 *)&pp[5] = 0;
    }
    hdr->h1bc = StateGetChapter_3cd5b0(self->m10);
    hdr->h1be = 0;
    {
        s16 t = hdr->h1bc;
        hdr->h1c0 = ProgressValueGet_3cd2c0(self->m10, t, hdr->h1be);
    }
    hdr->h1c2 = 0;
    if (InvHasItemInCategory_3c7f40(self->m18, 0x4178, 3, 0) != 0) hdr->h1c2 |= 1;
    if (InvHasItemInCategory_3c7f40(self->m18, 0x4179, 3, 0) != 0) hdr->h1c2 |= 2;
    if (InvHasItemInCategory_3c7f40(self->m18, 0x417A, 3, 0) != 0) hdr->h1c2 |= 4;
    nm = ProgressGetChapterRec_3cd550(self->m10);
    if (nm != 0) strcpy(hdr->name, F(nm, char *, 0x10));
    hdr->h244 = StateVarGet_3ccac0(self->m10, 0xD);
    q = sv + 0x298;
    if (rec != 0) {
        F(q, s16, 0) = rec->id;
        strcpy((char *)(q + 2), rec->name);
        if (PartyGetLocationGroupIdMaybe_3cb150(self->m18) == 10) {
            n = PartyGetFloorNum_3cb000(self->m18);
            if (n > 0) Sprintf_1343b8((char *)(q + 2), D_00466B70, (s32)rec->name, n);
        }
        F(q, s16, 0x82) = rec->m16;
        F(q, s16, 0x84) = F(self->m18, s16, 4);
        F(q, s16, 0x86) = F(self->m18, s16, 6);
        F(q, s16, 0x88) = F(self->m18, s16, 0xA);
        F(q, f32, 0x8C) = rec->x;
        F(q, f32, 0x90) = rec->y;
        F(q, f32, 0x94) = rec->z;
        F(q, f32, 0x98) = rec->w;
    }
    F(sv, u16, 0x338) = 0;
    fl = (u16 *)(sv + 0x338);
    k2 = 0;
    do {
        if (StateFlagTest_3ccd70(self->m10, k2 + 0x1EA) != 0) fl[0] |= (u16)(1 << k2);
        k2++;
    } while (k2 < 8);
    fl[1] = StateVarGet_3ccac0(self->m10, 5);
    fl[2] = StateVarGet_3ccac0(self->m10, 6);
    fl[3] = StateVarGet_3ccac0(self->m10, 7);
    SaveHeaderFormatLocationMaybe_3ee800(sv, sv + 0x254);
    UnlockMaskBuildFromInv_3e4020((u8 *)self, (u8 *)(fl + 4));
    bb = sv + 0x348;
    k3 = 0;
    do {
        struct BF { u8 on : 1; u8 rest : 7; };
        m = InvGetCageItem_3c8040(self->m18, k3);
#if KB == 2
        {
            bool ok_;
            if (m != 0) {
                ok_ = true;
                ((BF *)bb)->on = ok_;
                bb[1] = InsectRecSlotCountItems_3cfb80(m, ok_);
            } else {
                ok_ = false;
                ((BF *)bb)->on = false;
                bb[1] = 0;
            }
        }
#elif KB == 3
        if (m != 0) {
            ((BF *)bb)->on = m != 0;
            bb[1] = InsectRecSlotCountItems_3cfb80(m, 1);
        } else {
            ((BF *)bb)->on = m != 0;
            bb[1] = 0;
        }
#elif KB == 4
        {
            bool ok_ = m != 0;
            ((BF *)bb)->on = ok_;
            if (ok_) {
                bb[1] = InsectRecSlotCountItems_3cfb80(m, ok_);
            } else {
                bb[1] = 0;
            }
        }
#elif KB
        {
            bool ok_ = m != 0;
            if (ok_) {
                ((BF *)bb)->on = ok_;
                bb[1] = InsectRecSlotCountItems_3cfb80(m, ok_);
            } else {
                ((BF *)bb)->on = ok_;
                bb[1] = 0;
            }
        }
#else
        ((BF *)bb)->on = (m != 0);
        if (m != 0) {
            bb[1] = InsectRecSlotCountItems_3cfb80(m, 1);
        } else {
            bb[1] = 0;
        }
#endif
        k3++; bb += 2;
    } while (k3 < 3);
    F(sv, u8, 0x34E) = F(self->m24, s32, 4);
    if (flag) {
        F(sv, f32, 0x7C) = D_0047D364;
        F(sv, f32, 0x80) = D_0047D368;
        F(sv, f32, 0x84) = D_0047D36C;
        F(sv, f32, 0x88) = D_0047D248;
        F(sv, f32, 0xA4) = D_0047D370;
        F(sv, f32, 0xA8) = D_0047D374;
        F(sv, f32, 0xAC) = D_0047D378;
        F(sv, f32, 0xB0) = D_0047D37C;
        F(sv, f32, 0xCC) = D_0047D380;
        F(sv, f32, 0xD0) = D_0047D384;
        F(sv, f32, 0xD4) = D_0047D388;
        F(sv, f32, 0xD8) = D_0047D38C;
        F(sv, f32, 0x1F4) = D_0047D390;
        F(sv, f32, 0x1F8) = D_0047D394;
        F(sv, f32, 0x1FC) = D_0047D398;
        F(sv, f32, 0x200) = D_0047D364;
        F(sv, f32, 0x204) = D_0047D39C;
        F(sv, f32, 0x208) = D_0047D3A0;
        F(sv, s16, 0x298) = 0x265;
        F(sv, s16, 0x31A) = 0x193;
        F(sv, s16, 0x31C) = 6;
        F(sv, s16, 0x31E) = 0x258;
        F(sv, s16, 0x320) = 0x258;
        F(sv, f32, 0x324) = D_0047D3A4;
        F(sv, f32, 0x328) = D_0047D3A8;
        F(sv, f32, 0x32C) = D_0047D3AC;
        F(sv, f32, 0x330) = D_0047D3B0;
        q = sv + 0x298;
        nm = GroupGetRecordById_425590(F(self->m8, s32, 0x74), F(q, s16, 0));
        if (nm != 0) {
            strcpy((char *)(q + 2), F(nm, char *, 4));
        } else {
            strcpy((char *)(q + 2), MsgGetTextByIndex_279040(0x2C));
        }
    }
    F(sv, s64, 0x10) = 0;
    F(sv, u128, 0x20) = 0;
    F(sv, s64, 0x30) = 0x300;
    {
        u8 *d = sv + 0x10;
        F(d, u128, 0x30) = Md5DigestQword_369050(sv + 0x50, F(sv, s32, 0x30));
    }
    return 1;
}
