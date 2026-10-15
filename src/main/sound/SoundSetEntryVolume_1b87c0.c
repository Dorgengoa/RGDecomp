#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 pad0[0x18];
    s32 n;
    s8 *notes;
    u8 pad20[0x18];
} Part;

typedef struct {
    s16 id;
    s16 note;
    s8 part;
    s8 key;
    s16 pad;
} Voice;

typedef struct {
    u8 pad0[4];
    s32 x4;
    s32 ch;
    u8 padC[0xC];
    Part parts[5];
    u8 pad130[0x24];
    s32 x154;
    s32 vol;
    u8 pad15C[4];
    Voice voices[16];
} Bank;

typedef struct {
    u8 pad0[0x18];
    s32 vol;
    u8 pad1C[0x74];
} Chan;

typedef struct {
    s32 a;
    s32 b;
    s8 *p;
    s32 c;
} Info;

extern void SoundSeqPlayerResendVolumePan_1b5400(Chan *, s32);
extern void SoundSendCmd_1b6cc0();
extern void SoundResolveKey_1b9970(Info *, u32, s32);
extern Bank D_0049EB10[];
extern Chan D_004A0910[];
extern s32 D_004A1E40[];

static inline Bank *GetBank(s32 i) {
    if (i < 0 || i > 16) {
        return 0;
    }
    return &D_0049EB10[i];
}

static inline Part *GetPart(Bank *b, s32 j) {
    if (j < 0 || j >= 5) {
        return 0;
    }
    return &b->parts[j];
}

static inline s8 *GetNote(Part *p, s32 k) {
    if (k < 0 || k >= p->n) {
        return 0;
    }
    return p->notes + k * 12;
}

static inline Chan *GetChan(s32 i) {
    if (i < 0 || i >= 32) {
        return 0;
    }
    return &D_004A0910[i];
}

static inline s32 GetCh(s32 bi, s32 pi, s32 *out) {
    Bank *b = GetBank(bi);
    if (b == 0) {
        return 0;
    }
    if (GetPart(b, pi) == 0) {
        return 0;
    }
    *out = b->x4;
    return 1;
}

void SoundSetEntryVolume_1b87c0(u32 id, s32 note, s32 vol, s32 key) {
    Info info;
    s8 *e;
    s32 bi;
    s32 pi;
    Bank *bank;
    Part *part;
    s8 *ent;
    s32 ch;
    s32 v;
    Voice *vc;
    Voice *p;
    s32 i;
    Chan *c;
    s32 id2;
    s32 ch2;
    s8 t;
    s32 k7;

    if (id != -1) {
        SoundResolveKey_1b9970(&info, id, note);
        e = info.p;
        if (e != 0 && e[6] == 4) {
            t = e[10];
            if (t >= 0) {
                note = *(s16 *)(e + 4);
                id = (t & 0xFF) << 24;
            }
        }
    }
    if (id == -1) {
        return;
    }
    bi = (id >> 24) & 0xFF;
    pi = (id >> 16) & 0xFF;
    bank = GetBank(bi);
    if (bank == 0) {
        return;
    }
    part = GetPart(bank, pi);
    if (part == 0) {
        return;
    }
    ent = GetNote(part, note);
    if (ent == 0) {
        return;
    }
    if (vol < 0) {
        vol = ent[8];
    }
    if (ent[6] == 0) {
        return;
    }
    if (ent[6] == 2) {
        if (bank->vol != vol && vol >= 0 && vol < 0x80 && bank->x154 != 0) {
            bank->vol = vol;
            ch = bank->ch;
            v = vol;
            if (ch >= 0 && (u32)ch < 16) {
                v = vol * D_004A1E40[ch] / 127;
            }
            SoundSendCmd_1b6cc0(0x12, 2, ch, v);
        }
    }
    if (ent[6] == 1) {
        k7 = ent[7];
        if (id != -1 && GetCh(bi, pi, &ch2)) {
            v = vol;
            if (vol < 0) {
                v = 0x7F;
            }
            if (ch2 >= 0 && (u32)ch2 < 16) {
                v = v * D_004A1E40[ch2] / 127;
            }
            SoundSendCmd_1b6cc0(0x1D, 5, ch2, key, 0, k7, v);
        }
    }
    if (ent[6] != 3) {
        return;
    }
    for (i = 0; i < 16; i++) {
        p = &bank->voices[i];
        if (p->id >= 0 && p->part == pi && p->note == note && p->key == key) {
            vc = p;
            goto found;
        }
    }
    vc = 0;
found:
    if (vc == 0) {
        return;
    }
    id2 = vc->id;
    c = GetChan(id2);
    if (vol < 0) {
        vol = 0x7F;
    }
    if (c == 0) {
        return;
    }
    c->vol = vol;
    SoundSeqPlayerResendVolumePan_1b5400(c, id2);
}
