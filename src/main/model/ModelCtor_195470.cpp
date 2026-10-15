#include "types.h"

/* The trailing call is a genuine C++ virtual: retail is
   `lw t9, 0xF0(this) / lw t9, 0x10(t9) / jalr t9`, this = self+0x10 -- a
   sub-object EMBEDDED at self+0x10 whose own vtable pointer happens to live
   at self+0xF0 (embedded-relative +0xE0, since mwcc places the vptr AFTER
   the sub-object's leading data). The vtable-pointer STORE two lines up
   (`self->unkF0 = &D_0046FFA0`) is a plain data write and already matched
   before this fix -- only the CALL needed to become C++.
   virtual_index = (0x10 - 8) / 4 = 2. */

typedef struct VTable00195470 {
    u8 pad0[0x10];
    void (*unk10)(void *self);
} VTable00195470;

typedef struct Obj00195470 {
    u8 pad0[0xF0];
    VTable00195470 *unkF0;
    u8 pad_F4[0x1B0 - 0xF4];
    void *unk1B0;
} Obj00195470;

class Embedded00195470 {
    u8 pad000[0xE0];
public:
    virtual void slot00();
    virtual void slot04();
    virtual void init();
};

extern "C" VTable00195470 D_0046FFA0;
/* Incomplete array type: the compiler cannot prove this is <=8 bytes, so it
   is kept off %gp_rel and addressed with %hi/%lo like retail, matching the
   lever documented in src/mb/InsectBattleModeUpdate_27e0d0.c. */
extern "C" u8 D_0046FFC0[];

extern "C" Obj00195470 *ModelCtor_195470(Obj00195470 *self)
{
    Obj00195470 *s0;

    self->unk1B0 = D_0046FFC0;
    s0 = self;
    self->unkF0 = &D_0046FFA0;
    ((Embedded00195470 *)((u8 *)s0 + 0x10))->init();
    return s0;
}
