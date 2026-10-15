#include "types.h"

extern void SoundPlayEntry_1b8f90(s32,s32,s32,s32,s32,s32,s32);
extern void SoundResolveKey_1b9970(void *arg0, s32 arg1, s32 arg2);

void SoundPlayScaledVolume_1b9520(s32 arg0, s32 arg1, s32 arg2, f32 fparg0)
{
    u8 sp90[0x10];
    u8 sp80[0x10];
    u8 sp70[0x10];
    s32 var_20;
    s32 var_19;
    s32 var_17;
    s32 var_16;
    s32 var_6;
    s8 temp_2;
    s8 temp_2_2;
    s8 var_2;
    void *sp98;
    void *sp88;
    void *sp78;

    var_20 = arg0;
    var_19 = arg1;
    if (var_20 != -1) {
        SoundResolveKey_1b9970(sp90, var_20, var_19);
        sp98 = *(void **)(sp90 + 8);
        if ((sp98 != NULL) && (*(s8 *)((u8 *)sp98 + 0x6) == 4)) {
            temp_2 = *(s8 *)((u8 *)sp98 + 0xA);
            if (temp_2 >= 0) {
                var_19 = *(s16 *)((u8 *)sp98 + 0x4);
                var_20 = (temp_2 & 0xFF) << 0x18;
            }
        }
    }
    var_16 = var_19;
    var_17 = var_20;
    if (var_20 != -1) {
        SoundResolveKey_1b9970(sp70, var_20, var_19);
        sp78 = *(void **)(sp70 + 8);
        if ((sp78 != NULL) && (*(s8 *)((u8 *)sp78 + 0x6) == 4)) {
            temp_2_2 = *(s8 *)((u8 *)sp78 + 0xA);
            if (temp_2_2 >= 0) {
                var_16 = *(s16 *)((u8 *)sp78 + 0x4);
                var_17 = (temp_2_2 & 0xFF) << 0x18;
            }
        }
    }
    SoundResolveKey_1b9970(sp80, var_17, var_16);
    sp88 = *(void **)(sp80 + 8);
    if (sp88 != NULL) {
        var_2 = *(s8 *)((u8 *)sp88 + 0x8);
    } else {
        var_2 = 0;
    }
    var_6 = (s32)(fparg0 * (f32)var_2);
    if (var_6 > 0x7f) {
        var_6 = 0x7F;
    }
    SoundPlayEntry_1b8f90(var_20,var_19,-1,var_6,0x40,0x2000,arg2);
}
