#include "types.h"
#pragma divbyzerocheck on

typedef struct Ent {
    u8 pad0[4];
    s16 m4;
    s8 m6;
    s8 m7;
    s8 m8;
    s8 m9;
    s8 mA;
    u8 padB;
} Ent;

typedef struct Chan {
    u8 pad0[0x18];
    s32 m18;
    Ent *m1C;
    u8 pad20[0x10];
    s32 m30;
    Ent *m34;
} Chan;

typedef struct Slot {
    s16 m0;
    s16 m2;
    s8 m4;
    s8 m5;
    s8 m6;
    s8 m7;
} Slot;

typedef struct Tbl {
    u8 pad0[8];
    s32 m8;
    u8 padC[0xC];
    u8 chans[5][0x38];
    u8 pad130[0x20];
    s32 m150;
    s32 m154;
    s32 m158;
    s32 m15C;
    Slot slots[16];
    u8 pad1E0[0];
} Tbl;

typedef struct Res {
    s32 m0;
    s32 m4;
    Ent *m8;
} Res;

extern s32 SoundSendCmd_1b6cc0();
extern s32 SoundSeqPlayerAlloc_1b7bf0(u32, Ent *, s32);
extern void SoundPlayEntryKeyOn_1b81e0(u32, s32, s32, s32, s32, s32, s32, s32);
extern void SoundResolveKey_1b9970(Res *, u32, s32);
extern u8 D_0049EB10[0x400];
extern s32 D_004A1E40[16];

static inline Tbl *getTbl(s32 i)
{
    if (i < 0 || i > 16) return 0;
    return (Tbl *)(D_0049EB10 + i * 0x1E0);
}

static inline Chan *getChan(Tbl *t, s32 i)
{
    if (i < 0 || i >= 5) return 0;
    return (Chan *)((u8 *)t + i * 0x38 + 0x18);
}

static inline Ent *getEnt(Chan *c, s32 i)
{
    if (i < 0 || i >= c->m18) return 0;
    return &c->m1C[i];
}

static inline Ent *getEnt2(Chan *c, s32 i)
{
    if (i < 0 || i >= c->m30) return 0;
    return &c->m34[i];
}

static inline Slot *freeSlot(Tbl *t)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        if (t->slots[i].m0 < 0) return &t->slots[i];
    }
    return 0;
}

static inline s32 scaleVol(s32 ch, s32 vol)
{
    if (ch >= 0 && (u32)ch < 16) vol = vol * D_004A1E40[ch] / 127;
    return vol;
}

#pragma optimization_level 3
void SoundPlayEntry_1b8f90(u32 id, s32 idx, s32 a2, s32 vol, s32 a4, s32 a5, s32 a6)
{
    Res res;
    Tbl *tbl;
    Chan *chan;
    Ent *ent;
    Ent *e2;
    Slot *slot;
    s32 t;
    s32 ch;
    s32 n;
    s32 st;
    s16 r;

    if (id != -1) {
        SoundResolveKey_1b9970(&res, id, idx);
        if (res.m8 != 0 && res.m8->m6 == 4 && res.m8->mA >= 0) {
            idx = res.m8->m4;
            id = (u8)res.m8->mA << 24;
        }
    }
    if (id == -1) return;
    t = (id >> 24) & 0xFF;
    ch = (id >> 16) & 0xFF;
    tbl = getTbl(t);
    if (tbl == 0) return;
    chan = getChan(tbl, ch);
    if (chan == 0) return;
    ent = getEnt(chan, idx);
    if (ent == 0) return;
    if (vol < 0) vol = ent->m8;
    if (ent->m6 == 0) return;
    if (ent->m6 == 2) {
        st = tbl->m154;
        if (st == 1) goto skip;
        if (st == 2) goto caseA;
        if (st == 3) {
        caseA:
            SoundSendCmd_1b6cc0(0xE, 2, tbl->m8, ent->m4);
            SoundSendCmd_1b6cc0(0x12, 2, tbl->m8, scaleVol(tbl->m8, tbl->m158));
        } else {
            if (ent->m9 >= 0) {
                SoundSendCmd_1b6cc0(0x18, 1, tbl->m8);
                SoundSendCmd_1b6cc0(6, 2, tbl->m8, ent->m9);
            }
            n = tbl->m8;
            SoundSendCmd_1b6cc0(0xE, 2, n, 0);
            SoundSendCmd_1b6cc0(0x12, 2, n, scaleVol(n, vol));
        }
        tbl->m158 = vol;
        tbl->m154 = 1;
        tbl->m150 = ent->m4;
        tbl->m15C = idx;
    }
skip:
    if (ent->m6 == 1) {
        SoundPlayEntryKeyOn_1b81e0(id, ent->m4, ent->m7, a2, vol, a4, a5, a6);
    }
    if (ent->m6 == 3) {
        slot = freeSlot(tbl);
        e2 = getEnt2(chan, ent->m4);
        if (slot != 0 && e2 != 0) {
            r = SoundSeqPlayerAlloc_1b7bf0(id, e2, vol);
            slot->m0 = r;
            if (r >= 0) {
                slot->m4 = ch;
                slot->m2 = idx;
                slot->m5 = a6;
                slot->m6 = 1;
            }
        }
    }
}
