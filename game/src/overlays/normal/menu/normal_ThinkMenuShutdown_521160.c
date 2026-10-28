/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuShutdown_521160 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00521160 -- near-twin of normal_ShopMenuShutdown_50a630, different globals. */
extern u8 D_004B2570[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00484934;
extern u8  D_00480788;
extern u8  D_0048493C;
extern u8  D_00484938;
extern u8  D_00484940;

void normal_ThinkMenuShutdown_521160(void)
{
    normal_ThinkMenuResFree_5217b0();
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
    D_00484934 = 0;
    D_00480788 = 1;
    D_0048493C = 0;
    D_00484938 = 0;
    D_00484940 = 0;
}
