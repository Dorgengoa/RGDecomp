#pragma opt_propagation off
#include "types.h"

struct P8 {
    s32 a;
    s32 b;
};

struct P4 {
    s16 a;
    s16 b;
};

struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

struct State {
    P8 w[6];
    V4 v;
    P4 h[5];
    s32 x54;
};

struct Self {
    u8 pad0[0x80];
    s32 x80;
    s32 x84;
    s32 x88;
    u8 pad8C[0xE0 - 0x8C];
    u8 xE0[0x30];
    State s0;
    u8 pad168[8];
    State s1;
    u8 pad1C8[8];
    State s2;
    u8 pad228[8];
    State s3;
    u8 pad288[8];
    State s4;
    u8 pad2E8[8];
    State s5;
    u8 pad348[8];
    u8 pad350[0x3D0 - 0x350];
    s64 x3D0;
    s32 x3D8;
    u8 pad3DC[0x40C - 0x3DC];
    s16 x40C;
    s16 x40E;
    s16 x410;
    s16 x412;
};

struct Arg {
    u8 pad0[0x10];
    s32 x10;
};

extern "C" void VecSub_1cbd00(void *, void *, void *);

static inline bool test(s32 f, s32 m) {
    bool b = (f & m) != 0;
    return b;
}

extern "C" void CharaMoveRolloverMaybe_236930(Self *self, Arg *arg1) {
    s32 f;
    s64 m;

    self->s1 = self->s0;
    self->s3 = self->s2;
    self->s5 = self->s4;
    f = self->x3D8;
    if (test(f, 1)) {
        f |= 2;
    } else {
        f &= ~2;
    }
    self->x3D8 = f;
    if (test(f, 4)) {
        f |= 8;
    } else {
        f &= ~8;
    }
    self->x3D8 = f;
    if (test(f, 0x10)) {
        f |= 0x20;
    } else {
        f &= ~0x20;
    }
    self->x3D8 = f;
    if (test(f, 0x40)) {
        f |= 0x80;
    } else {
        f &= ~0x80;
    }
    self->x3D8 = f;
    f &= ~1;
    self->x3D8 = f;
    f &= ~4;
    self->x3D8 = f;
    f &= ~0x10;
    self->x3D8 = f;
    f &= ~0x40;
    self->x3D8 = f;
    self->x412 = 0;
    VecSub_1cbd00(&self->x80, &self->x80, self->xE0);
    if ((self->x3D0 & (0x20LL << 32)) || (self->x3D0 & (0x80LL << 32))) {
        self->x84 = 0;
    }
    if ((self->x3D0 & (0x10LL << 32)) || (self->x3D0 & (0x40LL << 32))) {
        self->x88 = 0;
        self->x80 = 0;
    }
    self->x40C = 0;
    if (arg1 != 0) {
        self->x40C = arg1->x10;
    }
    self->x410--;
    if (self->x410 < 0) {
        self->x410 = 0;
    } else {
        self->x40E |= 0x1000;
    }
}
