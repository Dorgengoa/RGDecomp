/* rgp:protos */
#define RGP_SELF_GetBank 1
#define RGP_SELF_GetCh 1
#define RGP_SELF_GetChan 1
#define RGP_SELF_GetNote 1
#define RGP_SELF_GetPart 1
#define RGP_SELF_SoundStopEntry_1b8bc0 1
#define RGP_SELF_func_001B8BD0 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
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

static inline s32 GetCh(s32 bi, s32 pi, s32 *out, s32 *out2) {
    Bank *b = GetBank(bi);
    if (b == 0) {
        return 0;
    }
    if (GetPart(b, pi) == 0) {
        return 0;
    }
    *out = b->x4;
    *out2 = pi;
    return 1;
}

void func_001B8BD0(u32 id, s32 note, s32 key, s32 flag);

void SoundStopEntry_1b8bc0(u32 id, s32 note, s32 key) {
    func_001B8BD0(id, note, key, 1);
}

void func_001B8BD0(u32 id, s32 note, s32 key, s32 flag) {
    s32 ch;
    Bank *bank;
    s8 *ent;
    s8 t;
    Part *part;
    s32 i;
    s32 bi;
    Voice *vc;
    s32 pi;
    s32 ch2;
    Info info __attribute__((aligned(16)));
    Voice *p;
    s8 *e;
    s32 pi2;
    Chan *c;

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
    if (bi < 0 || bi > 16) {
        bank = 0;
    } else {
        bank = &D_0049EB10[bi];
    }
    if (bank == 0) {
        return;
    }
    if (pi < 0 || pi >= 5) {
        part = 0;
    } else {
        part = &bank->parts[pi];
    }
    if (part == 0) {
        return;
    }
    if (note < 0 || note >= part->n) {
        ent = 0;
    } else {
        ent = part->notes + note * 12;
    }
    if (ent == 0) {
        return;
    }
    if (ent[6] == 0) {
        return;
    }
    if (ent[6] == 2) {
        if (bank->x154 != 0) {
            if (flag != 0) {
                ch = bank->ch;
                SoundSendCmd_1b6cc0(0x12, 2, ch, 0);
                SoundSendCmd_1b6cc0(1, 1, ch);
                SoundSendCmd_1b6cc0(2, 1, ch);
                SoundSendCmd_1b6cc0(0xF, 1, ch);
                SoundSendCmd_1b6cc0(2, 1, ch);
            } else {
                ch = bank->ch;
                SoundSendCmd_1b6cc0(0xF, 1, ch);
                SoundSendCmd_1b6cc0(1, 1, ch);
            }
            bank->x154 = 0;
        }
    }
    if (ent[6] == 1) {
        s32 k7;
        s32 k4;
        k7 = ent[7];
        k4 = *(s16 *)(ent + 4);
        if (id != -1 && GetCh(bi, pi, &ch2, &pi2)) {
            SoundSendCmd_1b6cc0(0x1B, 6, ch2, key, pi2, k4, 0, k7);
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
    c = GetChan(vc->id);
    if (c != 0) {
        SoundSeqStop_1b5980(c);
    }
    vc->id = -1;
}
