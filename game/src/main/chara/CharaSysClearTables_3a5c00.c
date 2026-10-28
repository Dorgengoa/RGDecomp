/* rgp:protos */
#define RGP_SELF_CharaSysClearTables_3a5c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaSysClearTables_3a5c00(s32 p0)
{
    s32 l0;
    s32 l1;
    s32 l2;
    s32 l3;

    l0 = 0;
    do {
        l1 = (l0 * 0x14);
        l2 = 0;
        do {
            *(u8 *)((u8 *)(p0 + (l0 * 0xA)) + l2 + 0x254) = 0;
            *(s16 *)((u8 *)(p0 + (l0 * 0x14)) + (l2 << 1) + 0x2F4) = 0;
            *(s16 *)((u8 *)(p0 + (l0 * 0x14)) + (l2 << 1) + 0x434) = 0;
            *(s16 *)((u8 *)(p0 + (l0 * 0x14)) + (l2 << 1) + 0x574) = 0;
            *(s16 *)((u8 *)(p0 + (l0 * 0x14)) + (l2 << 1) + 0x6B4) = 0;
            *(s16 *)((u8 *)(p0 + (l0 * 0x14)) + (l2 << 1) + 0x8F4) = 0;
            *(s16 *)((u8 *)(p0 + (l0 * 0x14)) + (l2 << 1) + 0xA34) = 0;
            l1 = ((l2 + 1) < 0xA);
            l2 = (l2 + 1);
        } while (l1 != 0);
        l3 = 0;
        do {
            *(s16 *)((u8 *)(p0 + (l0 << 3)) + (l3 << 1) + 0x7F4) = 0;
            *(s16 *)((u8 *)(p0 + (l0 << 3)) + (l3 << 1) + 0x874) = 0;
            l3 = (l3 + 1);
        } while (l3 < 4);
        *(s16 *)((u8 *)p0 + (l0 << 1) + 0xB74) = 0;
        l0 = (l0 + 1);
    } while (l0 < 0x10);
}
