#include "types.h"

typedef struct Entry001bd450 {
    u8 pad0[4];
    s32 unk4;
} Entry001bd450;

extern s32 DoubleLess_1002b0(s32 arg0, s32 arg1);
extern s32 GetSoundStreamTable_1bf7c0(void);
extern void SoundStreamHandleResolve_1bfa50(s32 *arg0, s32 arg1, s32 *arg2);
extern void SoundStreamLockDtor_1bfab0(s32 *arg0, s32 arg1);
extern s32 SoundStreamLockAcquire_1bfb40(s32 *arg0);
extern void SoundStreamSetFillThreshold_1bfd50(s32 arg0, f32 arg1);
extern s32 fptodp(s32, s32, f32 arg1);
extern s32 D_004814F0;
extern u8 D_004A25F0[];

void SoundStreamSlotSetFillThreshold_1bd450(s32 arg0, s32 arg2, f32 fparg0)
{
    s32 sp3C;
    s32 sp38;
    f32 var_f20;
    s32 temp_5;
    s32 var_6;
    Entry001bd450 *var_16;

    var_6 = arg2;
    var_f20 = fparg0;
    if ((arg0 < 0) || (arg0 >= 4)) {
        var_16 = NULL;
    } else {
        var_6 = arg0 * 0x128;
        var_16 = (Entry001bd450 *) (D_004A25F0 + var_6);
    }
    if ((var_16 == NULL) || (*(s32 *) ((u8 *) &D_004814F0 + (var_6 = arg0 * 4)) == 0)) var_16 = NULL;
    if (var_16 != NULL) {
        if ((DoubleLess_1002b0(fptodp(arg0, arg2, var_f20), 0) != 0) || !(var_f20 < 1.0f)) {
            var_f20 = 0.75f;
        }
        temp_5 = GetSoundStreamTable_1bf7c0();
        sp38 = var_16->unk4;
        SoundStreamHandleResolve_1bfa50(&sp3C, temp_5, &sp38);
        SoundStreamSetFillThreshold_1bfd50(SoundStreamLockAcquire_1bfb40(&sp3C), var_f20);
        SoundStreamLockDtor_1bfab0(&sp3C, -1);
    }
}
