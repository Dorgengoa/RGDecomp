#include "types.h"
#pragma divbyzerocheck on
#pragma optimization_level 3
#pragma opt_propagation off
#pragma opt_pulloutconstants off

struct PadState {
    s32 buttons;
    s32 lx;
    s32 ly;
    s32 rx;
    s32 ry;
    s32 w5;
    s32 w6;
    s32 w7;
    s32 w8;
    s32 w9;
    s8 a[6];
    s8 b[6];
    s8 c[6];
    s8 d[6];
    s32 e[6];
};

struct Rep {
    s32 mask;
    s32 held;
    s32 cnt[32];
    s32 lim1[32];
    s32 lim2[32];
};

struct Pad {
    s32 f0;
    PadState cur;
    PadState prev;
    s32 fB4;
    s32 fB8;
    s32 fBC;
    Rep rep;
    s32 thr;
    u8 p24C[0x25C - 0x24C];
    s32 mode;
    s32 idx;
};

struct RecEnt {
    u16 buttons;
    u8 lx;
    u8 ly;
    u8 rx;
    u8 ry;
};

extern "C" {
void PadUpdateConnection_184a50(PadState *, s32, s32, s32);
extern s32 D_0048122C __attribute__((section(".sdata")));
void PadUpdate_1843a0(Pad *self);
}

#define REC ((RecEnt *)0x3000000)

static inline s32 axis(s32 x) {
    s32 v = x - 0x80;
    if (v < 50 && v > -50) {
        return 0;
    }
    if (v > 0) {
        v = ((v - 49) << 7) / 78;
    } else {
        v = ((v + 50) << 7) / 78;
    }
    return v;
}

void PadUpdate_1843a0(Pad *self) {
    s32 i; s32 thr; s32 k; s32 bit; Rep *rp; RecEnt *re; RecEnt *rec; s32 m1; s32 m2;

    self->prev = self->cur;
    PadUpdateConnection_184a50(&self->cur, self->fB4, self->fB8, self->fBC);
    switch (self->mode) {
    case 1:
        rec = REC;
        i = self->idx;
        if ((u32)i < 0x2AAAA) {
            re = &rec[i];
            re->buttons = self->cur.buttons;
            re->lx = self->cur.lx;
            re->ly = self->cur.ly;
            re->rx = self->cur.rx;
            re->ry = self->cur.ry;
            self->idx++;
        }
        break;
    case 2:
        i = self->idx;
        if ((u32)i < 0x2AAAA) {
            rec = REC;
            re = &rec[i];
            self->cur.buttons = re->buttons;
            self->cur.lx = re->lx;
            self->cur.ly = re->ly;
            self->cur.rx = re->rx;
            self->cur.ry = re->ry;
            self->idx++;
        }
        break;
    }
    thr = self->thr;
    if (thr < 0) {
        thr = 0;
    }
    if (thr > 0) {
        if (thr < axis(self->cur.ly)) {
            self->cur.buttons |= 0x2000;
        }
        if (axis(self->cur.ly) < -thr) {
            self->cur.buttons |= 0x8000;
        }
        if (thr < axis(self->cur.lx)) {
            self->cur.buttons |= 0x4000;
        }
        if (axis(self->cur.lx) < -thr) {
            self->cur.buttons |= 0x1000;
        }
    }
    bit = 1;
    rp = &self->rep;
    k = 0;
    do {
        if (rp->mask & bit) {
            if (bit & (self->cur.buttons & rp->mask)) {
                if (!(++*(s32 *)((u8 *)rp + 8 + k * 4) < rp->lim1[k])) {
                    rp->held |= bit;
                }
            } else {
                *(s32 *)((u8 *)rp + 8 + k * 4) = 0;
                rp->held &= ~bit;
            }
            if (!(*(s32 *)((u8 *)rp + 8 + k * 4) < *(s32 *)((u8 *)rp + 0x108 + (s32)k * 4)) && (rp->held & bit)) {
                self->cur.buttons &= ~bit;
                *(s32 *)((u8 *)rp + 8 + k * 4) = 0;
            }
        }
        k++;
        bit <<= 1;
    } while (k < 32);
    k = 0;
    do {
        if ((self->cur.buttons & 0x1000) && (self->cur.buttons & 0x4000)) {
            self->cur.buttons &= ~0x5000;
        }
        if ((self->cur.buttons & 0x2000) && (self->cur.buttons & 0x8000)) {
            self->cur.buttons &= ~0xA000;
        }
        k++;
    } while (k < 2);
    *(s32 *)&D_0048122C = !D_0048122C;
}
