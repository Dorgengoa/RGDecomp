#include "types.h"
#pragma divbyzerocheck on

extern "C" void ViBufSetD4Chcr_1d47a0(u32);
extern "C" void ViBufSetD3Chcr_1d4800(s32);
extern "C" s32 ViBufGetFifoIndex_1d4860(struct Ipu *, u32);
extern "C" s32 SignalSema(s32);
extern "C" s32 WaitSema(s32);

extern "C" {
typedef struct Ipu {
    u32 base;
    s32 phys;
    s32 count;
    s32 idx;
    s32 num;
    u8 pad14[8];
    u32 cur;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    u32 bits;
    s32 unk3C;
    s32 sema;
    s32 unk44;
} Ipu;

#define RAW(c, T, o) (*(T *)((u8 *)(c) + (o)))
#define LOW28(x) ((x) & 0x0FFFFFFF)

s32 ViBufRestartDma_1d3e70(Ipu *c) {
    u32 bits;
    s32 n;
    u32 addr;
    u32 qwc;
    u32 madr;
    u32 tag;
    u32 fbrst;
    s32 mode;
    bool flag;
    s32 r;
    s32 a;
    s32 b;
    s32 cnt;
    s32 lo;
    u32 cur;
    s32 hi;

    bits = c->bits;
    fbrst = bits & 0x7F;
    hi = (bits >> 8) & 0xF;
    lo = (bits >> 16) & 3;
    n = lo + hi;
    addr = c->cur - n * 16;
    qwc = c->unk24 + n;
    madr = c->unk20;
    tag = c->unk28 | 0x100;
    WaitSema(c->sema);
    if (addr < c->base) {
        cnt = c->count;
        qwc = (c->base - addr) >> 4;
        addr += cnt << 11;
        madr = LOW28(c->phys);
        flag = true;
        if (c->cur != c->base && c->cur != c->base + (cnt << 11)) {
            flag = false;
        }
        if (flag) {
            mode = 0;
        } else {
            mode = 3;
        }
        tag = LOW28(c->unk28) | (mode << 28) | 0x100;
        r = c->idx;
        r = (RAW(c, s32, 8) - r) % RAW(c, s32, 8);
        if (r < 0 || r >= c->num) {
            c->idx = cnt - 1;
            c->num++;
        }
    } else {
        a = ViBufGetFifoIndex_1d4860(c, c->cur);
        b = ViBufGetFifoIndex_1d4860(c, addr);
        if (a != b) {
            madr = LOW28(c->phys + a * 16);
            qwc = (c->base + (a << 11) - addr) >> 4;
            if (c->base + (c->cur - c->base) % (u32)(c->count << 11) == c->base + (((c->idx + c->num) % c->count) << 11)) {
                mode = 0;
            } else {
                mode = 3;
            }
            tag = LOW28(c->unk28) | (mode << 28) | 0x100;
            r = (b + RAW(c, s32, 8) - c->idx) % RAW(c, s32, 8);
            if (r < 0 || r >= c->num) {
                c->idx = b;
                c->num++;
            }
        }
    }
    if (c->unk2C != 0 && c->unk30 != 0) {
        *(volatile s32 *)0x1000B010 = *(volatile s32 *)&c->unk2C;
        *(volatile s32 *)0x1000B020 = c->unk30;
        ViBufSetD3Chcr_1d4800(c->unk34 | 0x100);
    }
    if (c->num != 0) {
        while (*(volatile s32 *)0x10002010 < 0) {
        }
        *(volatile s32 *)0x10002000 = fbrst;
        while (*(volatile s32 *)0x10002010 < 0) {
        }
    }
    *(volatile u32 *)0x1000B410 = addr;
    *(volatile u32 *)0x1000B430 = madr;
    *(volatile u32 *)0x1000B420 = qwc;
    if (c->num != 0) {
        ViBufSetD4Chcr_1d47a0(tag);
    }
    *(volatile s32 *)0x10002010 = c->unk3C;
    c->unk44 = 1;
    SignalSema(c->sema);
    return 1;
}
}
