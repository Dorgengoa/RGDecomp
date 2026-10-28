/* rgp:protos */
#define RGP_SELF_MenuGridCursorPlaceCb_2a8f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T2A8F40 { u8 pad000[0x10]; s16 f10; s16 f12; };

extern void *D_00482360;
/*rgp*/

s32 MenuGridCursorPlaceCb_2a8f40(struct T2A8F40 *p)
{
    UiSetWidgetPos_290f60(D_00482360, 0xAE, p->f10 * 97 + 0x11, p->f12 * 97 + 0x31);
    return 1;
}
