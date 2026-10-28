/* rgp:protos */
#define RGP_SELF_ScreenMarkerSetFadeOut_31bf50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clamp the index to the last entry, then write the s16 table at
   +0xA0.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031bf50 {
    u8 pad000[0xA0];
    s16 tab[1];        /* +0xA0 */
} Obj_FUN_0031bf50;

void ScreenMarkerSetFadeOut_31bf50(Obj_FUN_0031bf50 *o, s32 index, s16 value)
{
    if (index >= 0x20) {
        index = 0x1F;
    }
    o->tab[index] = value;
}
