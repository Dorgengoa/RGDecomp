/* rgp:protos */
#define RGP_SELF_CompleteCheckCursorPlace_39e2c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T39E2C0 { u8 pad000[0x12]; s16 f12; };

extern u8 D_004E96B0[];
/*rgp*/

s32 CompleteCheckCursorPlace_39e2c0(struct T39E2C0 *p)
{
    UiSetWidgetPos_290f60(D_004E96B0, 5, 0, p->f12 * 27);
    return 1;
}
