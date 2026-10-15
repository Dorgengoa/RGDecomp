/* PARKED s17a: SaveDataSerialize_3e6100 -- m2c decompilation FAILED outright:
 * "Found jr instruction at SaveDataSerialize_3e6100.s line 87, but the corresponding
 * jump table is not provided." This is a computed-jump/switch whose jump
 * table is not present in the retail listing or was not located by
 * scripts/rgd.py decomp. Needs the jump table supplied (or located in the
 * .data section and added) before m2c can even produce a draft. Per the
 * BRIEF's own note: 'a jr $31 mid-function followed by more code no branch
 * reaches' can mean the symbol's declared size in config/main.symbols.txt
 * absorbed a second unlabeled function -- flagging per BRIEF instructions
 * rather than guessing at a split point. Not attempted. */
/* s49m: len 0x22C vs 0x230 ED 34 */
#include "types.h"
#pragma optimization_level 3

typedef unsigned __int128 u128;

typedef struct Sub {
    s64 size;
    s64 pad;
    u128 hash;
} Sub;

typedef struct Buf {
    u8 pad0[0x10];
    Sub sub;
    u8 pad30[0x310];
    s64 m340;
    u8 pad348[8];
} Buf;

class Part {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual s32 write(u8 *p, s32 n);
};

typedef struct Self {
    u8 pad0[0xC];
    Part *p0C;
    Part *p10;
    Part *p14;
    Part *p18;
    u8 pad1C[4];
    Part *p20;
    Part *p24;
} Self;

extern "C" {
extern s32 D_004658F0[0x400];
extern s32 D_004658F8[0x400];
void SaveDataClearError_3e6350(void);
void SaveDataSetError_3e6340(Self *, s32, s32, s32);
void InvFreeCategory8Items_3c8d70(Part *);
void InvPurgeRemoved_3c8cc0(Part *);
void SlotRecordReset_3eeca0(Buf *);
void SaveHeaderBuild_3e5520(Self *, Buf *, s32);
void memset(void *, s32, s32);
void memcpy(void *, void *, s32);
s32 SerialWriteChunkHeader_370e50(u8 *, s32, s32, s32, s32 **);
u128 Md5DigestQword_369050(void *, s32);
}

extern "C" s32 SaveDataSerialize_3e6100(Self *self, u8 *dst, s32 size, s32 arg3)
{
    Buf buf;
    s32 *cnt;
    s32 max;
    s32 total;
    u8 *p;
    s32 n;
    s32 remain;
    s32 i;
    s32 hdr;
    Part *part;
    Sub *sub;

    if (dst == 0 || size <= 0) {
        return 0;
    }
    SaveDataClearError_3e6350();
    max = D_004658F8[0];
    if (size <= max) {
        SaveDataSetError_3e6340(self, 1, size, 0);
        return 0;
    }
    InvFreeCategory8Items_3c8d70(self->p18);
    InvPurgeRemoved_3c8cc0(self->p18);
    buf.m340 = 0;
    total = 0;
    SlotRecordReset_3eeca0(&buf);
    SaveHeaderBuild_3e5520(self, &buf, arg3);
    hdr = D_004658F0[0];
    memset(dst, 0, hdr);
    memcpy(dst, &buf, 0x350);
    size -= hdr;
    total += hdr;
    p = dst + hdr;
    cnt = 0;
    n = SerialWriteChunkHeader_370e50(p, size, 0, 0, &cnt);
    total += n;
    p += n;
    remain = size - n;
    for (i = 1; i <= 6; i++) {
        part = 0;
        switch (i) {
        case 1:
            part = self->p0C;
            break;
        case 2:
            part = self->p10;
            break;
        case 3:
            part = self->p14;
            break;
        case 4:
            part = self->p18;
            break;
        case 5:
            part = self->p20;
            break;
        case 6:
            part = self->p24;
            break;
        }
        if (part == 0) {
            break;
        }
        n = part->write(p, remain);
        total += n;
        p += n;
        remain -= n;
        if (cnt != 0) {
            *cnt += n;
        }
    }
    sub = &buf.sub;
    sub->size = total - 0x50;
    sub->hash = Md5DigestQword_369050(dst + 0x50, *(s32 *)&sub->size);
    memcpy(dst, &buf, 0x50);
    n = max - total;
    if (n > 0) {
        memset(p, 0, n);
        total += n;
    }
    return total;
}
