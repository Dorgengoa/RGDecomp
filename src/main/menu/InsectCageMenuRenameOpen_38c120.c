#include "types.h"

extern void MemStackReset_14d830(void *);
extern s32 MemStackNew_14e230(s32, void *);
extern s16 LoaderRequestFile_1cd870(s32, void *, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void TextEntryAllocParts_436860(s32, void *, void *);
extern void TextEntryReset_436930(s32);
extern s32 TextEntryCtor_436950(s32);
extern u8 D_00455260[0x400];
extern u8 D_00464050[0x400];
extern s16 D_0047FBD0;
extern s32 D_00483298;
extern s8 D_0048329C;
extern s32 D_00484104;
extern u8 D_004E9440[0x248];

s32 InsectCageMenuRenameOpen_38c120(void) {
    s32 var_2;

    MemStackReset_14d830(D_004E9440);
    var_2 = MemStackNew_14e230(0x248, D_004E9440);
    if (var_2 != 0) {
        var_2 = TextEntryCtor_436950(var_2);
    }
    D_00483298 = var_2;
    TextEntryReset_436930(var_2);
    TextEntryAllocParts_436860(D_00483298, D_004E9440, D_00455260);
    D_0047FBD0 = LoaderRequestFile_1cd870(GetLoaderMgr_1f59d0(), D_00464050, 0);
    D_00484104 = 0;
    D_0048329C = 1;
    return 0;
}
