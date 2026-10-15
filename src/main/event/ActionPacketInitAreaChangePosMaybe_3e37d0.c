#include "types.h"

extern u8 *D_00483994;
extern const f32 D_0045B078;
extern const f32 D_0045B080;
extern void ActionPacketClear_3e3e90(void *);

/* The float parameter takes $f12 whatever its prototype position (independent
   EABI pools), so it is written last.  Retail FALLS THROUGH into the `4` arm,
   so that is the `if` body and 0xE is the else. */

u8 *ActionPacketInitAreaChangePosMaybe_3e37d0(u8 *p0, s32 p1, s32 p2, s32 p3, s32 p4, f32 f)
{
    if (D_00483994 == 0) {
        return 0;
    }
    ActionPacketClear_3e3e90(p0);
    if (p3 != 0) {
        *(s8 *)(p0 + 0x2) = 4;
    } else {
        *(s8 *)(p0 + 0x2) = 0xE;
    }
    *(s8 *)(p0 + 0x3) = 0x2E;
    *(s16 *)(p0 + 0x0) = 2;
    *(s32 *)(p0 + 0xC) = p1;
    *(s32 *)(p0 + 0x10) = p2;
    *(f32 *)(p0 + 0x14) = (f32)p4 / D_0045B078;
    *(f32 *)(p0 + 0x18) = f / D_0045B080;
    return p0;
}
