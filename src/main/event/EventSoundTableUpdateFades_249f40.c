#include "types.h"

typedef struct Entry {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
} Entry;

extern void SoundSetEntryVolumeScaled_1b9820(s32 a, s32 b, s32 c, f32 d);

void EventSoundTableUpdateFades_249f40(Entry *arg0)
{
    s32 temp_3;
    s32 var_16;
    Entry *temp_5;

    var_16 = 0;
    do {
        temp_5 = &arg0[var_16];
        if (temp_5->unk0 != -1) {
            temp_3 = temp_5->unk10;
            if (temp_3 > 0) {
                temp_5->unk8 = temp_5->unk8 + ((temp_5->unkC - temp_5->unk8) / (f32) temp_3);
                temp_5->unk10 = temp_5->unk10 - 1;
                SoundSetEntryVolumeScaled_1b9820(temp_5->unk0, temp_5->unk4, 0, temp_5->unk8);
            }
        }
        var_16 += 1;
    } while (var_16 < 0x40);
}
