/* rgp:protos */
#define RGP_SELF_SoundCategoryFadeInit_1b60c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x200];
    s32 m204;
    s32 m208;
    s32 m20C;
    u8 pad210[0x34];
    s32 m244;
    s32 m248;
    s32 m24C;
    s32 m250;
    s32 m254;
    s32 m258;
    s32 m25C;
    s32 m260;
};

void SoundCategoryFadeInit_1b60c0(struct Obj0 *p0)
{
    s32 l0;

    p0->m00 = 0xD;
    l0 = 0;
    while (l0 < p0->m00) {
        *(s32 *)((u8 *)p0 + (l0 << 5) + 0x4) = 0;
        *(s32 *)((u8 *)p0 + (l0 << 5) + 0x10) = 0x3F800000;
        *(s32 *)((u8 *)p0 + (l0 << 5) + 0x8) = 0x3F800000;
        *(s32 *)((u8 *)p0 + (l0 << 5) + 0x1C) = 0xBF800000;
        *(s32 *)((u8 *)p0 + (l0 << 5) + 0x20) = 0;
        l0 = (l0 + 1);
    }
    p0->m204 = 0;
    p0->m208 = 0xB;
    p0->m20C = -1;
    p0->m244 = 1;
    p0->m248 = 2;
    p0->m24C = 3;
    p0->m250 = 4;
    p0->m254 = 5;
    p0->m258 = 7;
    p0->m25C = 9;
    p0->m260 = -1;
}
