#include "types.h"

/* Clamp the index to the last entry, then write the s16 table at
   +0x40.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031bf90 {
    u8 pad000[0x40];
    s16 tab[1];        /* +0x40 */
} Obj_FUN_0031bf90;

void ScreenMarkerSetTimer_31bf90(Obj_FUN_0031bf90 *o, s32 index, s16 value)
{
    if (index >= 0x20) {
        index = 0x1F;
    }
    o->tab[index] = value;
}
