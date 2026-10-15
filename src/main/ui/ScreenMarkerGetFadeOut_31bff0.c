#include "types.h"

/* Clamp the index to the last entry, then read the s16 table at
   +0xA0.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031bff0 {
    u8 pad000[0xA0];
    s16 tab[1];        /* +0xA0 */
} Obj_FUN_0031bff0;

s16 ScreenMarkerGetFadeOut_31bff0(Obj_FUN_0031bff0 *o, s32 index)
{
    if (index >= 0x20) {
        index = 0x1F;
    }
    return o->tab[index];
}
