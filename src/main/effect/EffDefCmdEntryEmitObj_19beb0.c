#include "types.h"

/* The float handle is copied into a SECOND stack slot and read back as an
   integer word (lwc1 0x3C / swc1 0x38 / lw $5,0x38): a named f32 copy plus a
   type-punned read.  Writing `*(s32 *)&h` directly is 2 words short, and a
   1-float struct passed by value is coalesced away -- both measured. */
extern void *SlotGetInt_15f720(void *);
extern void EffHdlFindIdByName_1a3ba0(f32 *, void *, void *);
extern s32 *HandleTableGet_1a3b20(void *, s32);
s32 EffDefCmdEntryEmitObj_19beb0(void *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];
    f32 h;
    f32 x;
    u8 *y;
    void *it;
    s32 *r;
    if (*(void **)(o + 0x2C) == 0) {
        return 0;
    }
    it = SlotGetInt_15f720(args);
    y = *(u8 **)(o + 0x0);
    EffHdlFindIdByName_1a3ba0(&h, y + 0x7C, it);
    x = h;
    r = HandleTableGet_1a3b20(y + 0x7C, *(s32 *)&x);
    *(s32 *)(*(u8 **)(o + 0x2C) + 0x44) = r ? *r : 0;
    return 1;
}
