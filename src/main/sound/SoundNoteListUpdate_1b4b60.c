#include "types.h"
#pragma opt_common_subs off

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 padA[0xC - 0xA];
    f32 unkC;
    f32 unk10;
} Elem001B4B60;

typedef struct {
    s32 unk0;
    Elem001B4B60 *unk4;
    f32 unk8;
} Obj001B4B60;

void SoundStopEntry_1b8bc0(s32, s32, s16);                   /* extern */
void SoundPlayScaledVolPan_1b9680(s32, s32, s16, f32, f32);         /* extern */
void SoundSetEntryVolumeScaled_1b9820(s32, s32, s16, f32);              /* extern */
extern void SoundSetPanFloat_1b9a50(s32, s32, s32, f32);
s32 SoundIdGetIndex_1bbf20(s32);                              /* extern */

void SoundNoteListUpdate_1b4b60(Obj001B4B60 *arg0) {
                    s32 arg_h2;

    Elem001B4B60 *temp_16;
    s32 var_18;
    s32 temp_4;
    s32 temp_17;
    f32 var_f21;
    f32 temp_f1;
    f32 temp_f20;

    if (arg0->unk4 != 0) {
        var_18 = 0;
        while (var_18 < arg0->unk0) {
            temp_16 = (Elem001B4B60 *)((u8 *) arg0->unk4 + (var_18 * 0x14));
            temp_4 = temp_16->unk0;
            if (temp_4 >= 0) {
                temp_f1 = temp_16->unkC;
                temp_f20 = temp_16->unk10;
                if (temp_f1 >= 0.0f) {
                    var_f21 = temp_f1 * arg0->unk8;
                } else {
                    var_f21 = arg0->unk8;
                }
                temp_17 = SoundIdGetIndex_1bbf20(temp_4);
                if (temp_16->unk6 == 0) {
                    arg_h2 = temp_16->unk8;
                    SoundPlayScaledVolPan_1b9680(temp_16->unk0, temp_17, arg_h2, var_f21, temp_f20);
                } else if (!(temp_16->unkC < 0.0f)) {
                    arg_h2 = temp_16->unk8;
                    SoundSetEntryVolumeScaled_1b9820(temp_16->unk0, temp_17, arg_h2, var_f21);
                    SoundSetPanFloat_1b9a50(temp_16->unk0, temp_17, temp_16->unk8, temp_f20);
                }
                if (temp_16->unk6 >= temp_16->unk4) {
                    arg_h2 = temp_16->unk8;
                    SoundStopEntry_1b8bc0(temp_16->unk0, temp_17, arg_h2);
                    temp_16->unk0 = -1;
                    temp_16->unkC = -1.0f;
                    temp_16->unk10 = 0;
                }
                temp_16->unk6 = (s16) (temp_16->unk6 + 1);
            }
            var_18 += 1;
        }
    }
}
