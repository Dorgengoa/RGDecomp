/* rgp:protos */
#define RGP_SELF_HpGaugeGetDisplayedRatio_31e600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clamp the index to the last entry, then read the f32 table at
   +0x100.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031e600 {
    u8 pad000[0x100];
    f32 tab[1];        /* +0x100 */
} Obj_FUN_0031e600;

f32 HpGaugeGetDisplayedRatio_31e600(Obj_FUN_0031e600 *o, s32 index)
{
    if (index >= 0x10) {
        index = 0xF;
    }
    return o->tab[index];
}
