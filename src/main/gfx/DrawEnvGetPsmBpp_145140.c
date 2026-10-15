#include "types.h"
struct Obj1 { u8 pad000[0x30]; s32 m30; };
struct Obj0 { u8 pad000[0x270]; struct Obj1 *m270; };
s32 DrawEnvGetPsmBpp_145140(struct Obj0 *p0)
{
    s32 t1;

    t1 = p0->m270->m30;
    switch (t1) {
    case 0x0:
        return 0x20;
    case 0x1:
        return 0x18;
    case 0x2:
        return 0x10;
    case 0xA:
        return 0x10;
    case 0x13:
        return 0x8;
    case 0x14:
        return 0x4;
    case 0x30:
        return 0x20;
    case 0x31:
        return 0x18;
    case 0x32:
        return 0x10;
    case 0x3A:
        return 0x10;
    }
    return 0x20;
}
