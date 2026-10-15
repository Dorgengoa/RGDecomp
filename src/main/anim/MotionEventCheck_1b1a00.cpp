#include "types.h"

struct Trig001b1a00;

class Lsn001b1a00 {
public:
    virtual void v08(Trig001b1a00 *, s32);
    virtual void v0C(Trig001b1a00 *, s32);
    virtual void v10(Trig001b1a00 *, s32);
};

struct Rng001b1a00 {
    u8 pad0[0x24];
    f32 lo;
    f32 hi;
};

struct Trig001b1a00 {
    Lsn001b1a00 *lsn;
    u8 pad4[4];
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
    Rng001b1a00 *unk14;
    s32 unk18;
    u8 pad1C[4];
    f32 unk20;
};

static inline s32 isPos(f32 x) { if (x < 0.0f) return 0; return 1; }
static inline s32 isPos2(f32 x) { s32 r = 1; if (x < 0.0f) r = 0; return r; }
extern "C" s32 MotionEventCheck_1b1a00(Trig001b1a00 *self, Rng001b1a00 *arg1, s32 arg2, f32 t, f32 prev)
{
    Lsn001b1a00 *l;
    Rng001b1a00 *r;
    u8 kind;
    u8 pos;
    s32 tmp;
    s32 hit;
    f32 a;
    f32 b;

    l = self->lsn;
    if (l == 0) {
        return 0;
    }
    if (self->unk18 != 0) {
        arg2 = 1;
    }
    kind = self->unk10;
    if (kind != 0) {
        l->v0C(self, arg2);
        return 1;
    }
    r = self->unk14;
    if (r == 0) {
        return 0;
    }
    if (arg1 != r) {
        arg2 = 1;
    }
    if (t < r->lo) {
        arg2 = 1;
    }
    if (!(t <= r->hi)) {
        arg2 = 1;
    }
    tmp = 1;
    if (self->unk20 < 0.0f) {
        tmp = 0;
    }
    pos = tmp;
    if (pos == 0 && kind == 0) {
        if (arg2 != 0) {
            return 0;
        }
        if (t == prev) {
            return 0;
        }
        hit = 0;
        if (!(t <= prev)) {
            a = self->unk8;
            if (a < t && !(a < prev)) {
                hit = 1;
            }
        } else {
            a = self->unk8;
            if (a <= t) {
                hit = 1;
            } else if (!(a < prev)) {
                hit = 1;
            }
        }
        if (hit != 0) {
            l->v08(self, arg2);
        }
    } else {
        if (arg2 == 0) {
            b = self->unkC;
            a = self->unk8;
            arg2 = 1;
            if (a < b) {
                if (a <= t && !(b < t)) {
                    arg2 = 0;
                }
            } else {
                if (!(a < t)) {
                    arg2 = 0;
                }
                if (b <= t) {
                    arg2 = 0;
                }
            }
        }
        if (arg2 != 0) {
            l->v10(self, arg2);
        } else {
            l->v0C(self, arg2);
        }
    }
    return 1;
}
