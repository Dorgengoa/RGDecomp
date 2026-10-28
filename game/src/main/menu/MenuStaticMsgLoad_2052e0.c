/* rgp:protos */
#define RGP_SELF_MenuStaticMsgLoad_2052e0 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#pragma opt_common_subs off
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00480278;
extern s32 D_00481BBC;
extern u8 D_004BBB60[0x400];

void MenuStaticMsgLoad_2052e0(void) {
    s32 sp4C;
    s32 temp_16;
    s32 temp_2;
    s32 temp_17;
    s32 t;

    D_00481BBC = 0;
    temp_2 = ((s32)GetReadBuffHeap_2025e0());
    temp_17 = ((s32)MemStackHeapAlloc_14db10(temp_2, 2, 0, 0x40));
    sp4C = 0;
    temp_16 = ResidentFileReadLocalizedMaybe_1c2860(D_00480278, temp_17, &sp4C) & 0xFF;
    t = temp_2;
    MemStackReturnToOwnerMaybe_14dad0(t);
    if ((temp_16 == 0) || (sp4C <= 0)) {
        return;
    }
    D_00481BBC = ((s32)MsgTableParseText_28aab0(D_004BBB60, temp_17, sp4C));
    MemStackHeapFree_14dcb0(temp_2, temp_17);
}
