#include "types.h"

/* THREE edits, all needed:
   (1) `jalr $25` = C++ virtual, vptr +0, slot 0x50 = virtual #18
       ([[levers.d/jalr-is-cpp-virtual]]);
   (2) the f32 at +0x10 must be a real class MEMBER -- as
       `*(f32 *)((u8 *)self + 0x10)` mwcc CSEs the address into `$v0` and
       addresses it as `0($v0)` (+1 word, 4 wrong words);
   (3) the virtual's result must be named in a LOCAL and tested with an EARLY
       return: `r = self->v18(); if (r == 0) return 0;`. Calling it inside the
       guard, or naming it and keeping the block form, is 33 words -- retail
       annuls `daddu $4,$17,$0` (the next call's argument) in the `bnezl`
       slot and only that spelling leaves it sinkable. */

class VE39FFA0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual s32 v18(void);
    u8 pad004[0x10 - 4];
    f32 f10;
};
extern "C" s32 EquipSlotGetGaugeMax_3a02d0(VE39FFA0 *);

extern "C" s32 EquipSlotSetGaugeClamped_39ffa0(VE39FFA0 *self, s32 arg1)
{
    f32 t;
    s32 r;

    r = self->v18();
    if (r == 0) { return 0; }
    t = (f32)EquipSlotGetGaugeMax_3a02d0(self);
    if (arg1 < 0) {
        self->f10 = t;
    } else {
        self->f10 = (f32)arg1;
    }
    if (!(self->f10 <= t)) {
        self->f10 = t;
    }
    return 1;
}
