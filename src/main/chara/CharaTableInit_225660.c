#include "types.h"

/* Reset-then-populate.  The ten-store clear block appears TWICE (the
   static-inline-helper tell), and every conditional pair is
   `o->field = arg;  if (arg != 0) o->other = next;` - the unconditional
   store sits in the branch delay slot.  `bnel` on the first character
   duplicates the join block's `o->m28 = name` into its delay slot, so the
   name store is the statement AFTER the two early returns. */

typedef struct S225660 {
    /* 0x00 */ s64 m00;
    /* 0x08 */ s64 m08;
    /* 0x10 */ s32 m10;
    /* 0x14 */ s32 m14;
    /* 0x18 */ s32 m18;
    /* 0x1C */ s32 m1C;
    /* 0x20 */ s16 m20;
    /* 0x22 */ s16 m22;
    /* 0x24 */ s16 m24;
    /* 0x26 */ s16 m26;
    /* 0x28 */ s32 m28;
    /* 0x2C */ s32 m2C;
    /* 0x30 */ s16 m30;
    /* 0x32 */ s16 m32;
    /* 0x34 */ f32 m34;
} S225660;

void CharaTableInit_225660(S225660 *o, s8 *name, s32 p2, s64 p3, s64 p4, s32 p5,
                  s32 p6, s32 p7, s32 s0, s32 s1, s32 s2, s32 s3, s32 s4)
{
    o->m10 = 0;
    o->m26 = 0;
    o->m00 = 0;
    o->m08 = 0;
    o->m14 = 0;
    o->m20 = 0;
    o->m18 = 0;
    o->m22 = 0;
    o->m1C = 0;
    o->m24 = 0;
    o->m28 = 0;
    o->m2C = 0;
    o->m30 = 0;
    o->m34 = 1.0f;
    o->m32 = 0;
    if (name == 0 || *name == 0) {
        return;
    }
    o->m28 = (s32)name;
    o->m2C = p5;
    if (p5 != 0) {
        o->m30 = (s16)p6;
    }
    o->m10 = 0;
    o->m26 = 0;
    o->m00 = 0;
    o->m08 = 0;
    o->m14 = 0;
    o->m20 = 0;
    o->m18 = 0;
    o->m22 = 0;
    o->m1C = 0;
    o->m24 = 0;
    o->m26 = (s16)p2;
    o->m00 = p3;
    o->m08 = p4;
    o->m14 = p7;
    if (p7 != 0) {
        o->m20 = (s16)s0;
    }
    o->m18 = s1;
    if (s1 != 0) {
        o->m22 = (s16)s2;
    }
    o->m1C = s3;
    if (s3 != 0) {
        o->m24 = (s16)s4;
    }
}
