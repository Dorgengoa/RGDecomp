/* rgp:protos */
#define RGP_SELF_ScreenFadeIsFadingOut_1cf670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S1cf670 { u8 pad000[0x5980]; u8 m5980; u8 pad5981[0xF]; s32 m5990; };

/*rgp*/

u8 ScreenFadeIsFadingOut_1cf670(struct S1cf670 *p)
{
    s32 ok;

    ok = (ScreenFadeBlockIsDone_178110(&p->m5980) != 0) ^ 1;
    if (ok != 0) {
        ok = (~p->m5990) == 0;
    }
    return ok;
}
