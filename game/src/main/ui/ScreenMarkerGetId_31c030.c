/* rgp:protos */
#define RGP_SELF_ScreenMarkerGetId_31c030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same shape as ScreenMarkerGetFadeIn_31bfd0 but the table base IS the pointer: no struct
   displacement, and the addu takes the base first. */

s16 ScreenMarkerGetId_31c030(s16 *tab, s32 index)
{
    if (index >= 0x20) {
        index = 0x1F;
    }
    return tab[index];
}
