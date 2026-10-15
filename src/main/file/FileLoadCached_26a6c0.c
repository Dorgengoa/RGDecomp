#include "types.h"

typedef struct D00481F78Struct {
    u8 pad0[0x1808];
    s32 unk1808;
} D00481F78Struct;

extern D00481F78Struct *D_00481F78;
extern void MemStackReturnToOwnerMaybe_14dad0(s32 arg0);
extern s32 MemStackHeapAlloc_14db10(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void MemStackHeapFree_14dcb0(s32 arg0, s32 arg1);
extern s32 ResidentFileReadLocalizedMaybe_1c2860(s32 arg0, s32 arg1, s32 *arg2);
extern s32 FileCacheGetData_26a790(s32 arg0, s32 *arg1);

s32 FileLoadCached_26a6c0(s32 arg0, s32 *arg1) {
    s32 sp5C;
    s32 temp_18;
    s32 temp_17;
    s32 var_2;

    var_2 = FileCacheGetData_26a790(arg0, &sp5C);
    if (var_2 != 0) {
        if (arg1 != NULL) {
            *arg1 = sp5C;
        }
        return var_2;
    }
    temp_17 = D_00481F78->unk1808;
    temp_18 = MemStackHeapAlloc_14db10(temp_17, 2, 0, 0x40);
    MemStackReturnToOwnerMaybe_14dad0(temp_17);
    MemStackHeapFree_14dcb0(temp_17, temp_18);
    if (ResidentFileReadLocalizedMaybe_1c2860(arg0, temp_18, &sp5C) == 0) {
        return 0;
    }
    if (arg1 != NULL) {
        *arg1 = sp5C;
    }
    var_2 = temp_18;
    return var_2;
}
