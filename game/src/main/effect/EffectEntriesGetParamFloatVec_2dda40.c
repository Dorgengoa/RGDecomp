/* rgp:protos */
#define RGP_SELF_EffectEntriesGetParamFloatVec_2dda40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Sweep the 0x30-entry, 0xE0-stride table at p0 and hand every entry whose
   halfword id at +0xE equals a1's word at +8 to EffectEntryNodeGetParamFloatVec_2d9b20.
   No `b` to the test at the top => the loop is a do/while, not a while. */

void EffectEntriesGetParamFloatVec_2dda40(void *p0, void *a1, void *a2, void *a3)
{
    s32 i;
    u8 *e;

    i = 0;
    do {
        e = (u8 *)p0 + i * 0xE0;
        if (*(s16 *)(e + 0xE) == *(s32 *)((u8 *)a1 + 8)) {
            EffectEntryNodeGetParamFloatVec_2d9b20(e, a1, a2, a3);
        }
        i++;
    } while (i < 0x30);
}
