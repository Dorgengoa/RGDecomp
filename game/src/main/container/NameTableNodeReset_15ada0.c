/* rgp:protos */
#define RGP_SELF_NameTableNodeReset_15ada0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Object reset.  The two `lbu/and/or/sb` triples at +0x48 are a pair of 2-bit
   bitfields (little-endian: first declared field takes the LOW bits, so
   mask 0x3 then mask 0xC, both set to 1). */

typedef struct BF {
    u8 f0 : 2;
    u8 f2 : 2;
} BF;

void NameTableNodeReset_15ada0(u8 *p)
{
    s32 i;

    *(u8 *)(p + 0x08) = 0;
    *(s16 *)(p + 0x00) = -1;
    for (i = 0; i < 4; i++) {
        *(s32 *)(p + 0x50 + i * 4) = 0;
    }
    *(s32 *)(p + 0x60) = 0;
    *(s64 *)(p + 0x48) = 0;
    *(s64 *)(p + 0x40) = 0;
    *(s64 *)(p + 0x38) = 0;
    ((BF *)(p + 0x48))->f0 = 1;
    ((BF *)(p + 0x48))->f2 = 1;
    *(s16 *)(p + 0x06) = 0;
    *(s16 *)(p + 0x04) = 0;
    *(s16 *)(p + 0x02) = 0;
    *(s16 *)(p + 0x36) = 0;
    *(s16 *)(p + 0x28) = 0;
    *(s32 *)(p + 0x2C) = 0;
    *(s16 *)(p + 0x30) = 0;
    *(u8 *)(p + 0x32) = 0;
    *(u8 *)(p + 0x33) = 0;
    *(s16 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x64) = 0;
    *(u8 *)(p + 0x2A) = 0;
    *(u8 *)(p + 0x2B) = 0;
}
