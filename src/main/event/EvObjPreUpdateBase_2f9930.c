#include "types.h"

/* MAIN EvObjPreUpdateBase_2f9930 -- flag normaliser on +0xD0.
   The `sltu/xori` pairs are materialised booleans; the second one is
   additionally `andi 0xFF`, i.e. a u8 temporary, the first is not. */

void EvObjPreUpdateBase_2f9930(u8 *p)
{
    s32 f;
    s32 a;
    u8 b;
    s32 v;

    f = *(s32 *)(p + 0xD0) & 0xFFFF7FFF;
    *(s32 *)(p + 0xD0) = f;
    a = !((f & 0x80000000) != 0);
    if (a == 0) {
        v = f | 0x20000000;
        *(s32 *)(p + 0xD0) = v;
        *(s32 *)(p + 0xD0) = v | 0x40000000;
    } else {
        b = !((f & 0x40000000) != 0);
        if (b != 0) {
            v = f & 0xDFFFFFFF;
        } else {
            v = f | 0x20000000;
        }
        *(s32 *)(p + 0xD0) = v;
        *(s32 *)(p + 0xD0) = v | 0x40000000;
    }
}
