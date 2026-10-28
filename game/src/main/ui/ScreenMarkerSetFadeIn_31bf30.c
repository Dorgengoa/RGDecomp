/* rgp:protos */
#define RGP_SELF_ScreenMarkerSetFadeIn_31bf30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clamp the index to the last entry, then write the s16 table at
   +0xE0.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031bf30 {
    u8 pad000[0xE0];
    s16 tab[1];        /* +0xE0 */
} Obj_FUN_0031bf30;

void ScreenMarkerSetFadeIn_31bf30(Obj_FUN_0031bf30 *o, s32 index, s16 value)
{
    if (index >= 0x20) {
        index = 0x1F;
    }
    o->tab[index] = value;
}
