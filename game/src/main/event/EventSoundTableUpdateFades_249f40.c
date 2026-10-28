/* rgp:protos */
#define RGP_SELF_EventSoundTableUpdateFades_249f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Entry {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
} Entry;

/*rgp*/

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
