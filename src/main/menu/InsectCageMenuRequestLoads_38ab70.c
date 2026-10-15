#include "types.h"

typedef struct {
    s8 unk0;
    u8 pad1[0x3F];
} Elem0038AB70;

void LoaderQueueSeparatorGlobal_28afd0();
void LoadHandleArrayReset_28b160(s32, s32);
s32 LoadHandleRequestFile_28b550(s32, void *, s32, s32);
s8 InsectCageMsgListBuild_3845b0(s32 *, s32, s32);
void InsectCageBuildCbRootPath_38acb0(Elem0038AB70 *);
void InsectCharaPathFormat_390de0(void *, s32);
s32 InsectCageMenuGetCageInsect_390f00(s32, s32);
s32 InsectCageMenuGetCurCageItem_391030();
s32 InsectCageGetType_3910c0();
void InsectRecClearMsgEntries_3cefb0(s32);
void InsectRecPreMsgBuildNop_3cf020(s32);
void InsectRecRemoveListedInsectsMaybe_3cf030(s32);
void InsectRecPostMsgBuildNop_3cf0b0(s32);
void InsectRecClearPairEntries_3cf2f0(s32);
extern s32 D_004832D0;
extern s32 D_004832E4;
extern s16 D_004832E8;
extern s32 D_00483304;
extern s8 D_004833EC;

void InsectCageMenuRequestLoads_38ab70(void)
{
    s32 b[5];
    Elem0038AB70 a[6];
    s32 id;
    s32 i;

    id = InsectCageMenuGetCurCageItem_391030();
    InsectRecPreMsgBuildNop_3cf020(id);
    D_004833EC = InsectCageMsgListBuild_3845b0(&D_004832D0, id, D_00483304 + 0xA00);
    InsectRecPostMsgBuildNop_3cf0b0(id);
    InsectRecRemoveListedInsectsMaybe_3cf030(id);
    InsectRecClearMsgEntries_3cefb0(id);
    InsectRecClearPairEntries_3cf2f0(id);
    LoadHandleArrayReset_28b160(D_004832E4, 7);
    D_004832E8 = 0;
    InsectCageBuildCbRootPath_38acb0(a);
    for (i = 0; i < 5; i++) {
        b[i] = InsectCageMenuGetCageInsect_390f00(InsectCageGetType_3910c0(), i);
        InsectCharaPathFormat_390de0(&a[i + 1], b[i]);
    }
    for (i = 0; i < 6; i++) {
        if (a[i].unk0 != 0 && LoadHandleRequestFile_28b550(D_004832E4 + D_004832E8 * 0x38, &a[i], 0, 0) >= 0) {
            D_004832E8++;
        }
    }
    LoaderQueueSeparatorGlobal_28afd0();
}
