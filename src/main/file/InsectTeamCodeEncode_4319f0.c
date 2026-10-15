#include "types.h"

typedef struct BitS {
    s16 pos;
    s16 end;
    s32 f4;
    s32 f8;
    s32 fC;
} BitS;

typedef struct Ent {
    u8 name[0xD];
    u8 fD;
    u8 fE;
    u8 fF;
    u8 f10;
    u8 f11;
    u8 f12;
    u8 f13;
    u8 f14;
    u8 f15;
    u8 pad16[2];
    u8 f18;
    u8 pad19;
    u16 f1A;
    u16 f1C;
    u16 f1E;
    u8 f20;
    u8 f21;
    u8 f22;
    u8 pad23[5];
} Ent;

typedef struct Save {
    u8 name[9];
    u8 f9[6];
    s8 fF;
    u8 f10;
    u8 pad11[7];
    Ent ent[5];
} Save;

extern void BitWriterWriteBits_3709a0(BitS *, s32, s32);
extern void BitWriterWriteAlnum6_370a30(BitS *, void *, s32);
extern void BitWriterWriteAlpha5_370b90(BitS *, void *, s32);
extern void BitWriterSetBit_370cc0(BitS *, s32, u64);
extern void BitWriterInit_370d20(BitS *, void *, s32);
extern s32 CodeStringEncode_42ed00(void *, s32, char *, s32, u8 *, s32);
extern void *memcpy(void *, void *, s32);
extern void *memset(void *, s32, s32);
extern s32 strlen(char *);
extern char *D_00480168;

s32 InsectTeamCodeEncode_4319f0(s32 pad0, u8 *out, Save *sv)
{
    BitS bs;
    u8 buf[0x100];
    u8 enc[0x100];
    Ent *e;
    s32 i;
    s32 n;
    s32 len;
    s32 ok;

    if (out == 0 || sv == 0) {
        return 0;
    }
    BitWriterInit_370d20(&bs, buf, 0x100);
    BitWriterInit_370d20(&bs, 0, 0);
    BitWriterWriteAlnum6_370a30(&bs, sv->name, 8);
    BitWriterWriteAlpha5_370b90(&bs, sv->f9, 5);
    BitWriterWriteBits_3709a0(&bs, sv->fF, 3);
    BitWriterSetBit_370cc0(&bs, bs.pos++, (u64)sv->f10 << 62 >> 63);
    BitWriterSetBit_370cc0(&bs, bs.pos++, (u64)sv->f10 << 61 >> 63);
    e = sv->ent;
    for (i = 0; i < 5; i++) {
        BitWriterWriteAlpha5_370b90(&bs, e->name, 0xC);
        BitWriterWriteBits_3709a0(&bs, e->fD, 5);
        BitWriterWriteBits_3709a0(&bs, e->fE, 3);
        BitWriterWriteBits_3709a0(&bs, e->fF, 4);
        BitWriterWriteBits_3709a0(&bs, e->f10, 7);
        BitWriterWriteBits_3709a0(&bs, e->f11, 7);
        BitWriterWriteBits_3709a0(&bs, e->f12, 7);
        BitWriterWriteBits_3709a0(&bs, e->f13, 7);
        BitWriterWriteBits_3709a0(&bs, e->f14, 7);
        BitWriterWriteBits_3709a0(&bs, e->f15, 7);
        BitWriterWriteBits_3709a0(&bs, e->f18, 3);
        BitWriterWriteBits_3709a0(&bs, e->f1A, 10);
        BitWriterWriteBits_3709a0(&bs, e->f1C, 7);
        BitWriterWriteBits_3709a0(&bs, e->f1E, 7);
        BitWriterSetBit_370cc0(&bs, bs.pos++, (u64)e->f20 & 1);
        BitWriterSetBit_370cc0(&bs, bs.pos++, (u64)e->f20 << 62 >> 63);
        BitWriterWriteBits_3709a0(&bs, e->f21, 3);
        BitWriterWriteBits_3709a0(&bs, e->f22, 1);
        e++;
    }
    bs.end = bs.pos;
    n = bs.pos % 8 > 0;
    n = ((bs.pos / 8 + n) + 9) & ~7;
    len = (n / 8) * 11 + 1;
    memset(enc, 0, 0x100);
    memcpy(enc, buf, n);
    ok = CodeStringEncode_42ed00(enc, n, D_00480168, strlen(D_00480168), out, len) != 0;
    if (!ok) {
        return 0;
    }
    out[len] = 0;
    return 1;
}
