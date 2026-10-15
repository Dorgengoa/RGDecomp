#include "types.h"
#pragma optimization_level 3
#pragma divbyzerocheck on

typedef struct Ctx {
    u8 pad0[0x14];
    s32 count;
    s32 mode;
    s32 total;
    s32 w;
    u8 pad24[4];
    s32 unk28;
    s32 unk2C;
    u8 pad30[8];
    s32 m38[2][3];
    s32 frame;
    u8 flag;
    u8 pad55[7];
    s32 unk5C;
    s32 m60[2][3];
    u8 pad78[4];
    s32 m7C[2][3];
} Ctx;

typedef struct Strm {
    u8 pad0[8];
    Ctx *ctx;
    u8 padC[0xE4];
    u8 enabled;
    u8 padF1[3];
    s32 size;
    u8 padF8[8];
    s32 rd;
    s32 wr;
    u8 full;
    u8 pad109[3];
    s32 unk10C;
    u8 pad110[4];
    s32 addr;
} Strm;

extern void SoundAdpcmDecodeBlock_1bc030(Ctx *, s32, s32, s32, s32);
extern void SoundStreamSlotRingWrite_1bde90(Strm *, s32, s32, s32, s32);
extern s32 RingBufLoopRewind_1c1430(s32);
extern s32 RingBufGetLoopFlag_1c15b0(s32);
extern s32 RingBufRead_1c1890(s32, s32, s32);
extern s32 RingBufGetEndFlag_1c1b10(s32);

s32 SoundStreamSlotFillFromRingBuf_1bdb80(Strm *arg0, s32 arg1) {
    Ctx *c;
    s32 total;
    s32 count;
    s32 step;
    s32 base;
    s32 w;
    s32 need;
    s32 addr;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    s32 len;
    s32 b2;
    s32 l2;
    s32 wr;
    s32 rd;
    s32 size;

    if (arg0->enabled == 0) {
        return -1;
    }
    c = arg0->ctx;
    total = c->total;
    count = c->count;
    step = total / count;
    base = arg0->unk10C;
    w = c->w;
    need = w * 2;
    for (;;) {
        addr = arg0->addr;
        size = arg0->size;
        wr = arg0->wr;
        rd = arg0->rd;
        if (rd == wr) {
            if (arg0->full) {
                n = *(volatile s32 *)&arg0->size;
            } else {
                n = 0;
            }
        } else {
            n = 0;
            if (rd >= wr) {
                n = n + (size - rd);
                n = n + wr;
            } else {
                n = n + (wr - rd);
            }
        }
        if (n >= need) {
            if (RingBufRead_1c1890(arg1, addr, total) == 0) {
                if (RingBufGetLoopFlag_1c15b0(arg1) != 0) {
                    if (RingBufLoopRewind_1c1430(arg1) != 0) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 3; j++) {
                                c->m7C[i][j] = c->m38[i][j];
                            }
                        }
                        c->frame = c->unk28;
                        c->flag = 1;
                        return 0;
                    }
                } else if (RingBufGetEndFlag_1c1b10(arg1) != 0) {
                    return 2;
                }
                return 1;
            }
            if (c->frame == c->unk28) {
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 3; j++) {
                        c->m38[i][j] = c->m7C[i][j];
                    }
                }
            }
            c->unk5C = c->frame;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    c->m60[i][j] = c->m7C[i][j];
                }
            }
            for (k = 0; k < count; k++) {
                if (c->mode == 1) {
                    SoundAdpcmDecodeBlock_1bc030(c, k, base, addr, w);
                    b2 = base;
                    l2 = need;
                    if (c->flag) {
                        len = c->unk2C * 2;
                        b2 = base + len;
                        l2 = need - len;
                    }
                    SoundStreamSlotRingWrite_1bde90(arg0, k, b2, l2, k == count - 1);
                } else {
                    SoundStreamSlotRingWrite_1bde90(arg0, k, addr, need, k == count - 1);
                }
                addr += step;
            }
            if (c->flag) {
                c->flag = 0;
            }
            c->frame++;
            continue;
        }
        return 0;
    }
}
