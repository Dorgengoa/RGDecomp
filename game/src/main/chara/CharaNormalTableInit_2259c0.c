/* rgp:protos */
#define RGP_SELF_CharaNormalTableInit_2259c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same family as CharaTableInit_225660: the ten-store clear block appears twice.
   Here the guard is `bltz` on a signed s32 id that is narrowed to the s16
   at +0x2E, and the sentinel written first is -1. */

typedef struct S2259c0 {
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
    /* 0x2C */ s16 m2C;
    /* 0x2E */ s16 m2E;
} S2259c0;

void CharaNormalTableInit_2259c0(S2259c0 *o, s32 id, s32 p2, s64 p3, s64 p4, s32 p5,
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
    o->m2E = -1;
    o->m28 = 0;
    o->m2C = 0;
    if (id < 0) {
        return;
    }
    o->m2E = (s16)id;
    o->m28 = p5;
    if (p5 != 0) {
        o->m2C = (s16)p6;
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
