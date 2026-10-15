#include "types.h"

typedef struct {
    void *unk0;
    void *unk4;
    s32 unk8;
    u8 padC[0x4];
    s32 unk10;
} T24f120_arg0;

void EventVoiceChanSetPlaying_24f120(T24f120_arg0 *arg0, s32 arg1, s32 pd2, s8 arg3, s32 arg4)
{
    u8 *var_6;
    s32 var_8;
    u8 *temp_3;
    u8 *temp_3_2;

    var_8 = arg4;
    if (arg0->unk4 != NULL) {
        var_6 = (u8 *)-1;
    } else {
        var_6 = NULL;
        arg0->unk4 = arg0->unk0;
        arg0->unk8 = 0;
    }
    if (var_6 != NULL) {
        var_6 = NULL;
    } else {
        goto body;
    top:
        if (arg1 == var_8) goto done;
    body:
        temp_3 = (u8 *)arg0->unk4;
        if (temp_3 == NULL) {
            var_6 = NULL;
        } else {
            var_8 = *(s32 *)(temp_3 + 0xC);
            var_6 = temp_3 + 0x10;
            temp_3_2 = *(u8 **)(temp_3 + 0x0);
            arg0->unk4 = temp_3_2;
            if (temp_3_2 == NULL) {
                arg0->unk8 = 1;
            }
        }
        if (var_6 != NULL) goto top;
    done:
        arg0->unk4 = NULL;
        arg0->unk8 = 0;
    }
    if (var_6 != NULL) {
        *(s32 *)(var_6 + 0x0) = 2;
        *(s32 *)(var_6 + 0x4) = -1;
        *(u8 *)(var_6 + 0x10) = 0;
        *(s32 *)(var_6 + 0xC) = -1;
        *(s8 *)(var_6 + 0x20) = arg3;
        arg0->unk10 = -1;
    }
}
