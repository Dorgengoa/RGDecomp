#include "types.h"

/* Clamp the index to the last entry, then read the f32 table at
   +0x180.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031e330 {
    u8 pad000[0x180];
    f32 tab[1];        /* +0x180 */
} Obj_FUN_0031e330;

f32 HpGaugeGetSlotAlpha_31e330(Obj_FUN_0031e330 *o, s32 index)
{
    if (index >= 0x10) {
        index = 0xF;
    }
    return o->tab[index];
}
