#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E74F0[];
extern const s32 D_004E7AF0;
extern const s32 D_004E7AF8;
extern const s32 D_004E7AFC;
extern const s32 D_004E7B00;
extern const s32 D_004E7B04;
extern const s32 D_004E7B08;
extern const s32 D_004E7B14;
extern const s32 D_004E7B20;
extern const s32 D_004E7B24;
extern const s32 D_004E7B28;
extern const s32 D_004E7B2C;
extern const s32 D_004E7B30;

void StaticInitTextLayout_46cad0(void)
{
    s32 l0;
    s32 l1;

    *(s32 *)&D_004E7B00 = 0;
    *(s32 *)&D_004E7AFC = 0;
    *(s32 *)&D_004E7B04 = 0x10;
    *(s32 *)&D_004E7B08 = 0x14;
    *(s32 *)&D_004E7B14 = 4;
    *(s32 *)&D_004E7AF8 = 0;
    *(s32 *)&D_004E7AF0 = 0;
    *(s32 *)&D_004E7B20 = 0x80;
    *(s32 *)&D_004E7B24 = 0x80;
    *(s32 *)&D_004E7B28 = 0x80;
    *(s32 *)&D_004E7B2C = 0xFF;
    *(s32 *)&D_004E7B30 = 0x3F800000;
    l1 = 0;
    do {
        *(s32 *)((u8 *)D_004E74F0 + (l1 * 0xC) + 0x4) = -1;
        *(s32 *)((u8 *)D_004E74F0 + (l1 * 0xC)) = -1;
        *(s32 *)((u8 *)D_004E74F0 + (l1 * 0xC) + 0x8) = 0;
        l0 = ((l1 + 1) < 0x80);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
