/* rgp:protos */
#define RGP_SELF_UiGetWidgetPos_2910a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S2910A0 { u8 pad000[0x14]; f32 f14; f32 f18; };

/*rgp*/

void UiGetWidgetPos_2910a0(void *a, void *b, s32 *out1, s32 *out2)
{
    struct S2910A0 *q;

    *out2 = 0;
    *out1 = 0;
    q = ((struct S2910A0 *)UiFindWidget_290460(a, b));
    if (q != 0) {
        *out1 = (s32)q->f14;
        *out2 = (s32)q->f18;
    }
}
