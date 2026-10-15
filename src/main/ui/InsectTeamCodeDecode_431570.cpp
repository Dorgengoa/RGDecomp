#include "types.h"
#pragma divbyzerocheck on

struct BitReader {
    s16 pos;
    s16 len;
    s32 _4;
    u8 *buf;
    s32 _c;
};

struct PwEntry {
    char name[0xD];
    u8 xD;
    u8 xE;
    s8 xF;
    s8 x10;
    s8 x11;
    s8 x12;
    s8 x13;
    s8 x14;
    s8 x15;
    s8 x16;
    s8 x17;
    s8 x18;
    s8 _19;
    s16 x1A;
    s16 x1C;
    s16 x1E;
    u8 f0 : 1;
    u8 f1 : 1;
    s8 x21;
    s8 x22;
    s32 x24;
};

struct PwData {
    char name[9];
    char x9[6];
    s8 xF;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    s16 x12;
    s16 x14;
    s8 _16[2];
    PwEntry ent[5];
};

extern "C" {
void BitReaderReadBits_3706e0(BitReader *, s32 *, s32);
void BitReaderReadAlnum6_370750(BitReader *, char *, s32);
void BitReaderReadAlpha5_3708a0(BitReader *, char *, s32);
void BitWriterInit_370d20(BitReader *, u8 *, s32);
s32 ItemDefFindInsect_40c690(s32, u32, u32);
s32 CodeStringDecode_42ec30(char *, u8 *, s32, char *, s32);
void *memcpy(void *, const void *, u32);
void *memset(void *, s32, u32);
s32 strlen(const char *);
extern const s32 D_00465D80[];
extern char *D_00480168;
extern u8 *D_004840D8;
s32 InsectTeamCodeDecode_431570(s32 arg0, char *name, PwData *out);
}

static inline s32 readBits(BitReader *r, s32 n) {
    s32 v = 0;
    BitReaderReadBits_3706e0(r, &v, n);
    return v;
}

static inline bool readBit(BitReader *r) {
    s16 p = r->pos;
    r->pos = p + 1;
    u8 b = r->buf[p >> 3];
    return (b & (u8)(1 << (p & 7))) != 0;
}

s32 InsectTeamCodeDecode_431570(s32 arg0, char *name, PwData *out) {
    BitReader r;
    u8 dec[0x100];
    u8 raw[0x100];
    s32 n;
    PwEntry *e;
    s32 i;
    s32 k;

    if (name == 0 || out == 0) {
        return 0;
    }
    memset(dec, 0, 0x100);
    bool ok = CodeStringDecode_42ec30(name, dec, 0x100, D_00480168, strlen(D_00480168)) != 0;
    if (!ok) {
        return 0;
    }
    BitWriterInit_370d20(&r, raw, 0x100);
    n = (strlen(name) + 1) / 11 * 8;
    memcpy(raw, dec, n);
    r.len = n;
    r.pos = 0;
    BitReaderReadAlnum6_370750(&r, out->name, 8);
    BitReaderReadAlpha5_3708a0(&r, out->x9, 5);
    out->xF = readBits(&r, 3);
    out->b0 = true;
    out->b1 = readBit(&r);
    out->b2 = readBit(&r);
    e = out->ent;
    i = 0;
    out->b3 = false;
    k = D_00465D80[0];
    out->x12 = 0;
    out->x14 = 0;
    do {
        BitReaderReadAlpha5_3708a0(&r, e->name, 0xC);
        e->xD = readBits(&r, 5);
        e->xE = readBits(&r, 3);
        e->xF = readBits(&r, 4);
        e->x10 = readBits(&r, 7);
        e->x11 = readBits(&r, 7);
        e->x12 = readBits(&r, 7);
        e->x13 = readBits(&r, 7);
        e->x14 = readBits(&r, 7);
        e->x15 = readBits(&r, 7);
        e->x16 = 2;
        e->x17 = k;
        e->x18 = readBits(&r, 3);
        e->x1A = readBits(&r, 10);
        e->x1C = readBits(&r, 7);
        e->x1E = readBits(&r, 7);
        e->f0 = readBit(&r);
        e->f1 = readBit(&r);
        e->x21 = readBits(&r, 3);
        e->x22 = readBits(&r, 1);
        e->x24 = ItemDefFindInsect_40c690(*(s32 *)(*(u8 **)(*(u8 **)(D_004840D8 + 8) + 0x40) + 8), e->xD, e->xE);
        i++;
        e++;
    } while (i < 5);
    return 1;
}
