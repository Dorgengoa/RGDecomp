/* rgp:protos */
#define RGP_SELF_FactoryMenuResReady_204890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of InsectMenuResReady_2031b0 (byte-identical, in cunits). */

extern s32 func_4EC0E0(void);

u8 FactoryMenuResReady_204890(void)
{
    s32 r;

    r = func_4EC0E0();
    return (r != 0);
}
