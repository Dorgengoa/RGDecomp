/* rgp:protos */
#define RGP_SELF_InsectCageMenuRequestLoads_38ab70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s8 unk0;
    u8 pad1[0x3F];
} Elem0038AB70;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004832D0;
extern s32 D_004832E4;
extern s16 D_004832E8;
extern s32 D_00483304;
extern s8 D_004833EC;

void InsectCageMenuRequestLoads_38ab70(void)
{
    s32 b[5] __attribute__((aligned(16)));
    Elem0038AB70 a[6] __attribute__((aligned(16)));
    s32 id;
    s32 i;

    id = InsectCageMenuGetCurCageItem_391030();
    InsectRecPreMsgBuildNop_3cf020();
    D_004833EC = InsectCageMsgListBuild_3845b0(&D_004832D0, id, D_00483304 + 0xA00);
    InsectRecPostMsgBuildNop_3cf0b0(id);
    InsectRecRemoveListedInsectsMaybe_3cf030(id);
    InsectRecClearMsgEntries_3cefb0(id);
    InsectRecClearPairEntries_3cf2f0(id);
    LoadHandleArrayReset_28b160(D_004832E4, 7);
    D_004832E8 = 0;
    InsectCageBuildCbRootPath_38acb0(a);
    for (i = 0; i < 5; i++) {
        b[i] = ((s32)InsectCageMenuGetCageInsect_390f00(((signed char)InsectCageGetType_3910c0()), i));
        InsectCharaPathFormat_390de0(&a[i + 1], b[i], 0, 0);
    }
    for (i = 0; i < 6; i++) {
        if (a[i].unk0 != 0 && LoadHandleRequestFile_28b550(D_004832E4 + D_004832E8 * 0x38, &a[i], 0, 0) >= 0) {
            D_004832E8++;
        }
    }
    LoaderQueueSeparatorGlobal_28afd0();
}
