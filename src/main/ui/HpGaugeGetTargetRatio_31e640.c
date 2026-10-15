#include "types.h"

/* Clamp the index to the last entry, then read the f32 table at
   +0xC0.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031e640 {
    u8 pad000[0xC0];
    f32 tab[1];        /* +0xC0 */
} Obj_FUN_0031e640;

f32 HpGaugeGetTargetRatio_31e640(Obj_FUN_0031e640 *o, s32 index)
{
    if (index >= 0x10) {
        index = 0xF;
    }
    return o->tab[index];
}
