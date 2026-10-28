/* rgp:protos */
#define RGP_SELF_UiPlaceWidgetAtCell_2a4a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T2A4A90 { u8 pad000[0x10]; s16 f10; s16 f12; s16 f14; s16 f16; };

/*rgp*/

s32 UiPlaceWidgetAtCell_2a4a90(void *a, void *b, struct T2A4A90 *p, float rgp_f0)
{
    if (p == 0) return 0;
    UiMoveOrPlaceWidget_2a4af0(a, (float)rgp_f0, b, (p->f10 + p->f14) * 48, (p->f12 + p->f16) * 56);
    return 1;
}
