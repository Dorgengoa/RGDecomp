#include "types.h"

/* Clamp the index to the last entry, then read the f32 table at
   +0x140.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031e620 {
    u8 pad000[0x140];
    f32 tab[1];        /* +0x140 */
} Obj_FUN_0031e620;

f32 HpGaugeGetSettledRatio_31e620(Obj_FUN_0031e620 *o, s32 index)
{
    if (index >= 0x10) {
        index = 0xF;
    }
    return o->tab[index];
}
