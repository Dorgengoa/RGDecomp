/* rgp:protos */
#define RGP_SELF_HpGaugeGetHideStep_31e680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clamp the index to the last entry, then read the s16 table at
   +0xA0.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031e680 {
    u8 pad000[0xA0];
    s16 tab[1];        /* +0xA0 */
} Obj_FUN_0031e680;

s16 HpGaugeGetHideStep_31e680(Obj_FUN_0031e680 *o, s32 index)
{
    if (index >= 0x10) {
        index = 0xF;
    }
    return o->tab[index];
}
