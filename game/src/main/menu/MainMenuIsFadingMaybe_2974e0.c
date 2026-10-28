/* rgp:protos */
#define RGP_SELF_MainMenuIsFadingMaybe_2974e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN MainMenuIsFadingMaybe_2974e0 -- window 0x00296000-0x0029C000.  D_0047EB98 is the s16
   gp mode flag the settled seed MainMenuInit_297510 writes (`D_0047EB98 = 1`).
   ONE load, two `==` tests, so the value is a named local. */

extern s16 D_0047EB98;

s32 MainMenuIsFadingMaybe_2974e0(void)
{
    s32 r;
    s16 v;

    v = D_0047EB98;
    r = 0;
    if (v == 2 || v == 1) {
        r = 1;
    }
    return r;
}
