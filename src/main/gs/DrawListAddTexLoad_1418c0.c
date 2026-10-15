#include "types.h"
#include "vec.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void MemStackAllocQw_14d950(void *, s32);
extern s32 TexGroupAllocVram_157e70(s32, s32, s32);
extern void *TableGetEntryOrDefault_159f60(s32, s32);
extern void TexAnimeTableApplyMaybe_162f50(s32, void *, s32);
extern void TexAnimSeqUpdate_163dd0(s32, f32);
extern const u128 D_0047DE40 __attribute__((section(".sdata")));

typedef struct { u64 lo : 32; u64 hi : 32; } BF001418c0;

s32 DrawListAddTexLoad_1418c0(void *arg0, s32 arg1, f32 fparg0)
{
    u128 *temp_3;
    s32 temp_16_2;
    s32 temp_18;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_16;
    void *temp_2_3;
    void *var_17;

    temp_2 = ((s32 *)((u8 *)arg0 + 8))[S32(arg0, 0)];
    temp_18 = S32(arg0, 0x3BA0);
    if (temp_2 != 0) {
        var_17 = (u8 *)temp_2 + 8;
    } else {
        var_17 = NULL;
    }
    if (temp_18 == 0 || var_17 == NULL) {
        return 0;
    }
    temp_16 = S32(var_17, 0x28) + (S32(var_17, 0x2C) * 0x10);
    temp_2_2 = TexGroupAllocVram_157e70(temp_18, arg1, temp_16);
    if (temp_2_2 <= 0) {
        return 0;
    }
    temp_3 = (u128 *)((u8 *)temp_16 + (temp_2_2 * 0x10));
    *temp_3 = 0;
    *(u32 *)temp_3 = 0x60000000;
    MemStackAllocQw_14d950(var_17, temp_2_2 + 1);
    if (temp_16 != 0) {
        *(u128 *)PTR(arg0, 4) = D_0047DE40;
        *(s32 *)((u8 *)PTR(arg0, 4) + 4) = temp_16 & 0x0FFFFFFF;
        *(void **)((u8 *)arg0 + 4) = (u8 *)PTR(arg0, 4) + 0x10;
    }
    temp_2_3 = TableGetEntryOrDefault_159f60(temp_18, arg1);
    if (temp_2_3 != NULL) {
        temp_16_2 = S32(temp_2_3, 0xC);
        if (temp_16_2 != 0) {
            if (!(fparg0 <= 0.0f)) {
                TexAnimSeqUpdate_163dd0(temp_16_2, fparg0);
            }
            TexAnimeTableApplyMaybe_162f50(temp_16_2, arg0, arg1);
        }
    }
    return 1;
}
