/* rgp:protos */
#define RGP_SELF_ScreenMarkerSetId_31bfb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same shape as ScreenMarkerSetFadeIn_31bf30 but the table base IS the pointer. */

void ScreenMarkerSetId_31bfb0(s16 *tab, s32 index, s16 value)
{
    if (index >= 0x20) {
        index = 0x1F;
    }
    tab[index] = value;
}
