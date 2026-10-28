/* rgp:protos */
#define RGP_SELF_SoundStreamChannelsInit_207960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                                /* extern */
/*rgp*/                                /* extern */
/*rgp*/                       /* extern */
/*rgp*/               /* extern */
/*rgp*/                                /* extern */
/*rgp*/                                 /* extern */
extern s16 D_00481C80;
extern s16 D_00481C84;
extern s16 D_00481C88;
extern s32 D_00481CA0;

void SoundStreamChannelsInit_207960(s32 arg0) {
    s32 *temp_3;
    s32 temp_2;
    s32 var_6;

    temp_2 = ((s32)GetStreamMgr_207ea0());
    StreamMgrInitChans_1d69b0(temp_2);
    var_6 = 0;
    D_00481C80 = -1;
    D_00481C84 = -1;
    D_00481C88 = -1;
    do {
        temp_3 = (s32 * )((u8 *)&D_00481CA0 + (var_6 * 4));
        var_6 += 1;
        *temp_3 = -1;
    } while (var_6 < 4);
    if (arg0 != 0) {
        MemStackHeapAlloc_14db10(arg0, 1, 0, 0x40);
        MemStackAlign64_14d8e0(arg0);
        StreamMgrOpenChan_1d67e0(temp_2, 0, 2, 4, 0xBB80, arg0);
        StreamMgrOpenChan_1d67e0(temp_2, 1, 2, 1, 0xBB80, arg0);
        StreamMgrOpenChan_1d67e0(temp_2, 2, 2, 1, 0xBB80, arg0);
        MemStackReturnToOwnerMaybe_14dad0(arg0);
    }
}
