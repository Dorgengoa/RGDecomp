/* rgp:protos */
#define RGP_SELF_ScreenMarkerGetFadeIn_31bfd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clamp the index to the last entry, then read the s16 table at +0xE0.
   No negative guard -- the clamp is the only bound, and the likely branch
   duplicates the index shift into its own delay slot. */

typedef struct Obj_FUN_0031bfd0 {
    u8 pad000[0xE0];
    s16 tab[1];        /* +0xE0 */
} Obj_FUN_0031bfd0;

s16 ScreenMarkerGetFadeIn_31bfd0(Obj_FUN_0031bfd0 *o, s32 index)
{
    if (index >= 0x20) {
        index = 0x1F;
    }
    return o->tab[index];
}
