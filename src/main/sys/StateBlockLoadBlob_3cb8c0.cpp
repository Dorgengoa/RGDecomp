#include "types.h"

/* `lw $25,0($4) / lw $25,0x10($25) / jalr $25` and `lw $25,0($20) /
   lw $25,0x8($25) / jalr $25` -> two C++ virtual calls on arg0 itself
   (arg0 IS the polymorphic object -- offset 0 is its own vtable pointer,
   not a nested field). slot0 -> vtable+0x8, slot2 -> vtable+0x10. Both
   calls take no explicit args beyond the implicit `this`. */

class Ent {
public:
    virtual s32  s0();      /* slot 0 -> vtable +0x8 */
    virtual void s1();      /* slot 1 -> vtable +0xC (unused) */
    virtual s32  s2();      /* slot 2 -> vtable +0x10 */
    s32 f4;
};

extern "C" void *memcpy(void *, const void *, s32);

extern "C" s32 StateBlockLoadBlob_3cb8c0(Ent *arg0, void *arg1, s32 arg2)
{
    s32 temp_16;
    s32 var_17;

    if (arg1 != 0 && arg2 > 0) {
        goto success;
    }
    return 0;
success:
    temp_16 = arg0->f4;
    var_17 = arg0->s2();
    if (arg2 < var_17) {
        var_17 = arg2;
    }
    memcpy((u8 *)arg0 + arg0->s0(), arg1, var_17);
    arg0->f4 = temp_16;
    return var_17;
}
