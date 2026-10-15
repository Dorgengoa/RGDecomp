#include "types.h"
/* normal 0x004F9770 -- hide widget 0x80 and clear its latch at +0x3D8.
 * `$4` is never reloaded: `p` is still live in the argument register. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3D8 - 0x37A];
    s16 f3D8;
} Obj;

extern void func_291110(Obj *p, s32 id, s32 c, s32 d);

void normal_FieldHudWidget80CarryCloseMaybe_4f9770(Obj *p)
{
    if (p->f378 != 0) {
        func_291110(p, 0x80, 0, 1);
        p->f3D8 = 0;
    }
}
