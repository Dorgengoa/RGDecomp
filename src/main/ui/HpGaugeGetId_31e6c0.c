#include "types.h"

/* Same shape as ScreenMarkerGetFadeIn_31bfd0 but the table base IS the pointer: no struct
   displacement, and the addu takes the base first. */

s16 HpGaugeGetId_31e6c0(s16 *tab, s32 index)
{
    if (index >= 0x10) {
        index = 0xF;
    }
    return tab[index];
}
