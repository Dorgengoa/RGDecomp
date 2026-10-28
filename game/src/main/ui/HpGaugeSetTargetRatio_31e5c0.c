/* rgp:protos */
#define RGP_SELF_HpGaugeSetTargetRatio_31e5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clamp the index to the last entry, then write the f32 table at
   +0xC0.  No negative guard; the likely branch duplicates the
   index shift.  Proven at ScreenMarkerGetFadeIn_31bfd0. */

typedef struct Obj_FUN_0031e5c0 {
    u8 pad000[0xC0];
    f32 tab[1];        /* +0xC0 */
} Obj_FUN_0031e5c0;

void HpGaugeSetTargetRatio_31e5c0(Obj_FUN_0031e5c0 *o, s32 index, f32 value)
{
    if (index >= 0x10) {
        index = 0xF;
    }
    o->tab[index] = value;
}
