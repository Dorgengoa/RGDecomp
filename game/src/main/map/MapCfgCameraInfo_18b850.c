/* rgp:protos */
#define RGP_SELF_MapCfgCameraInfo_18b850 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode on

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481250;
extern s32 D_0048125C;
extern s32 D_004812CC;
/*rgp*/

s32 MapCfgCameraInfo_18b850(s32 arg0) {
    s32 temp_2;

    if (!(MapCfgIsCameraSkipped_18cb00() == 0)) {
        return 1;
    }
    temp_2 = VariantGetInt_15f780(arg0);
    if (temp_2 >= 0) {
        FixCameraRecArraySet_189760(D_00481250,
                     ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0((temp_2 * 0xD0) + 0x10, D_0048125C)),
                                  (void *) FixCameraRecCtor_18b8f0, 0, 0xD0, temp_2)),
                     temp_2);
        D_004812CC = 0;
        return 1;
    }
    return 0;
    return 1;
}
