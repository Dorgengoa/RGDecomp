#include "types.h"

/* Two constant tables written through a sub-object pointer, chosen by arg1.

   The ARM ORDER is read off the fall-through, not off the test: retail's
   `beql $17, $0` jumps to the D_004611A8 arm, so the arm it falls INTO --
   D_004611B8 -- is the source's `if` body and the test is `arg1 != 0`.
   Writing it the m2c way (`if (arg1 == 0)` first) lays the two blocks out
   the other way round.

   Both guards are early returns; each materialises its own zero in the
   branch's delay slot, which is the per-site `return 0` tell. */

extern void *UiFindWidget_290460(s32, s32);
extern void strcpy(void *, const char *);

extern const char D_004611A8[];
extern const char D_004611B8[];

extern s32 D_00482360;

s32 MenuMsgWindowSetSkin_295220(s32 arg0, s32 arg1)
{
    u8 *p;
    u8 *q;

    p = UiFindWidget_290460(D_00482360, arg0);
    if (p == 0) {
        return 0;
    }
    q = *(u8 **)(p + 0x20);
    if (q == 0) {
        return 0;
    }
    if (arg1 != 0) {
        strcpy(p + 4, D_004611B8);
        *(s16 *)(q + 0x8) = 0xF0;
        *(s16 *)(q + 0xA) = 0x28;
        *(s16 *)(q + 0x28) = 0xF0;
        *(s16 *)(q + 0x2A) = 0x38;
        *(s16 *)(q + 0x48) = 0xF0;
        *(s16 *)(q + 0x4A) = 0x44;
        *(s16 *)(q + 0x68) = 0xD4;
        *(s16 *)(q + 0x6A) = 0x44;
        *(s16 *)(q + 0x88) = 0xE6;
        *(s16 *)(q + 0x8A) = 0x3A;
        *(s16 *)(q + 0xA8) = 0xD4;
        *(s16 *)(q + 0xAA) = 0x28;
        *(s16 *)(q + 0xC8) = 0xD4;
        *(s16 *)(q + 0xCA) = 0x38;
        *(s16 *)(q + 0xE8) = 0xD4;
        *(s16 *)(q + 0xEA) = 0x44;
        *(s16 *)(q + 0x108) = 0xE4;
        *(s16 *)(q + 0x10A) = 0x28;
        *(s16 *)(q + 0x128) = 0xE4;
        *(s16 *)(q + 0x12A) = 0x44;
        *(s16 *)(q + 0x148) = 0xF0;
        *(s16 *)(q + 0x14A) = 0x28;
        *(s16 *)(q + 0x168) = 0xF0;
        *(s16 *)(q + 0x16A) = 0x38;
        *(s16 *)(q + 0x188) = 0xF0;
        *(s16 *)(q + 0x18A) = 0x44;
    } else {
        strcpy(p + 4, D_004611A8);
        *(s16 *)(q + 0x8) = 0x54;
        *(s16 *)(q + 0xA) = 0x4A;
        *(s16 *)(q + 0x28) = 0x54;
        *(s16 *)(q + 0x2A) = 0x5A;
        *(s16 *)(q + 0x48) = 0x54;
        *(s16 *)(q + 0x4A) = 0x66;
        *(s16 *)(q + 0x68) = 0x38;
        *(s16 *)(q + 0x6A) = 0x66;
        *(s16 *)(q + 0x88) = 0x4A;
        *(s16 *)(q + 0x8A) = 0x5C;
        *(s16 *)(q + 0xA8) = 0x38;
        *(s16 *)(q + 0xAA) = 0x4A;
        *(s16 *)(q + 0xC8) = 0x38;
        *(s16 *)(q + 0xCA) = 0x5A;
        *(s16 *)(q + 0xE8) = 0x38;
        *(s16 *)(q + 0xEA) = 0x66;
        *(s16 *)(q + 0x108) = 0x48;
        *(s16 *)(q + 0x10A) = 0x4A;
        *(s16 *)(q + 0x128) = 0x48;
        *(s16 *)(q + 0x12A) = 0x66;
        *(s16 *)(q + 0x148) = 0x54;
        *(s16 *)(q + 0x14A) = 0x4A;
        *(s16 *)(q + 0x168) = 0x54;
        *(s16 *)(q + 0x16A) = 0x5A;
        *(s16 *)(q + 0x188) = 0x54;
        *(s16 *)(q + 0x18A) = 0x66;
    }
    return 1;
}
