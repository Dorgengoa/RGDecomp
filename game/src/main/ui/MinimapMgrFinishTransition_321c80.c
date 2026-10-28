/* rgp:protos */
#define RGP_SELF_MinimapMgrFinishTransition_321c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

typedef struct {
    u8 pad0[0x510];
    void *unk510;
    void *unk514;
    u8 pad518[0x8];
    s8 unk520;
} T321c80_arg0;

void MinimapMgrFinishTransition_321c80(T321c80_arg0 *arg0) {
    s8 temp_3;
    void *temp_4;

    if ((temp_4 = arg0->unk510) == NULL || arg0->unk514 == NULL) {
        return;
    }
    {
        arg0->unk520 = *(s8 *)((u8 *)temp_4 + 0x11C);
        if (MinimapSlotIsActive_322510(arg0->unk510) == 0) {
            arg0->unk520 = 2;
        }
        temp_3 = *(s8 *)((u8 *)arg0->unk514 + 0x11C);
        if (temp_3 == 2) {
            arg0->unk520 = temp_3;
        }
        if ((MinimapGetDrawAlpha_32a180(arg0->unk510) <= 0.0f && !(MinimapGetDrawAlpha_32a180(arg0->unk514) < 1.0f)) ||
            arg0->unk520 == 2) {
            arg0->unk510 = arg0->unk514;
            arg0->unk514 = NULL;
        }
    }
}
