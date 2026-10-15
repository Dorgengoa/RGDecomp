#include "types.h"

extern void LoaderQueueAppendSeparator_1cd670(s32);
extern s32 LoaderRequestFile_1cd870(s32, s32, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern s16 D_0047FF4C;
extern s16 D_0047FF54;
extern s32 D_0047FF58;

struct Elem003987E0 {
    s32 unk0;
    s32 unk4;
};
extern struct Elem003987E0 D_00454410[];

s32 InsectMenuResRequest_3987e0(void)
{
    s32 temp_19;
    s32 temp_2;
    s32 var_18;
    s32 var_17;
    struct Elem003987E0 *temp_16;

    temp_19 = GetLoaderMgr_1f59d0();
    var_18 = 1;
    if (D_0047FF4C != 0) {
        if (D_0047FF54 >= 0) {
            var_18 += 2;
        }
    }
    var_17 = 0;
    while (var_17 < var_18) {
        temp_16 = &D_00454410[var_17];
        temp_16->unk0 = -1;
        temp_16->unk4 = 0;
        temp_2 = LoaderRequestFile_1cd870(temp_19, *(s32 *)((u8 *)&D_0047FF58 + var_17 * 4), 0);
        temp_16->unk0 = temp_2;
        if (temp_2 == -1) {
            return 1;
        }
        var_17 += 1;
    }
    LoaderQueueAppendSeparator_1cd670(temp_19);
    return 0;
}
