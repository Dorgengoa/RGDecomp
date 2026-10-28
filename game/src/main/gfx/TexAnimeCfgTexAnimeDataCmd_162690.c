/* rgp:protos */
#define RGP_SELF_TexAnimeCfgTexAnimeDataCmd_162690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481148;
extern s32 D_0048114C;
extern u8 D_00495E70[0x20];
extern s16 D_00495E9E[0x10];

s32 TexAnimeCfgTexAnimeDataCmd_162690(void *arg0) {
    void *old;

    D_00481148 = -1;
    TexAnimKeyInit_164080(D_00495E70);
    old = arg0;
    arg0 = (u8 *)arg0 + 8;
    D_00495E70[0] = VariantGetInt_15f780(old);
    SlotGetInt_15f720(arg0);
    D_00495E9E[0] = (s16)D_0048114C;
    return 1;
}
