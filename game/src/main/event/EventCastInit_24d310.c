/* rgp:protos */
#define RGP_SELF_EventCastInit_24d310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Eight 0x60-byte records, each cleared to an identity-ish 3x4 and handed to
   XformRecSetDefaultNameMaybe_1c6940, then four 8.0f writes through the sub-object pointer.

   ONE WORD in here needed both halves of a lever and either alone is a
   MEASURED NULL.  Retail's record address is `addu $5, $5, $18` -- offset in
   rs, base in rt, which is INTEGER arithmetic (`off + (s32)p`), not pointer
   arithmetic.  Four pointer spellings (`p + i*0x60`, `i*0x60 + p`,
   `&p[i*0x60]`, `q = p; q += ...`) and the cast WITHOUT a named product all
   compile to the IDENTICAL object with the operands the other way round.
   What flips it is naming the product in a local AND writing the addition on
   integers:

       off = i * 0x60;
       q = (u8 *)(off + (s32)p);

   Also measured null here: float literals versus their bit patterns.
   `*(f32 *)x = 0.0f` and `*(s32 *)x = 0` give one identical object, as do
   `1.0f` and `0x3F800000`. */

/*rgp*/
/*rgp*/

extern s32 D_00481F30;

void EventCastInit_24d310(u8 *p)
{
    s32 i;
    s32 j;
    s32 off;
    u8 *q;
    u8 *r;

    *(s32 *)(p + 0x00) = 0;
    *(s32 *)(p + 0x04) = 0;
    *(s32 *)(p + 0x08) = 0;
    for (i = 0; i < 8; i++) {
        off = i * 0x60;
        q = (u8 *)(off + (s32)p);
        *(s16 *)(q + 0x60) = 2;
        *(s16 *)(q + 0x62) = 0;
        *(s16 *)(q + 0x68) = 0;
        *(s16 *)(q + 0x6E) = -1;
        *(s16 *)(q + 0x6A) = -1;
        *(s16 *)(q + 0x6C) = -1;
        r = q + 0x10;
        *(f32 *)(q + 0x10) = 0.0f;
        *(f32 *)(q + 0x14) = 0.0f;
        *(f32 *)(q + 0x18) = 0.0f;
        *(f32 *)(q + 0x1C) = 1.0f;
        *(f32 *)(q + 0x20) = 0.0f;
        *(f32 *)(q + 0x24) = 0.0f;
        *(f32 *)(q + 0x28) = 0.0f;
        *(f32 *)(q + 0x2C) = 1.0f;
        *(f32 *)(q + 0x30) = 0.0f;
        *(f32 *)(q + 0x34) = 0.0f;
        *(f32 *)(q + 0x38) = 0.0f;
        *(f32 *)(q + 0x3C) = 1.0f;
        XformRecSetDefaultNameMaybe_1c6940(r);
        for (j = 0; j < 4; j++) {
            *(f32 *)(r + j * 4 + 0x30) = 8.0f;
        }
    }
    *(s32 *)(p + 0x310) = 0;
    *(s32 *)(p + 0x320) = 0;
    *(s32 *)(p + 0x324) = 0;
    *(s32 *)(p + 0x328) = 0;
    *(s32 *)(p + 0x32C) = 0;
    D_00481F30 = 0;
    EventAreaListClear_24a280(p);
}
