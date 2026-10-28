/* rgp:protos */
#define RGP_SELF_MotionListCopy_171cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg0_00171cc0 {
    s32 unk0;
    void *unk4;
    s32 unk8;
} Arg0_00171cc0;

typedef struct Node_00171cc0 {
    struct Node_00171cc0 *unk0;
    u8 pad4[4];
    s32 unk8;
    s32 unkC;
} Node_00171cc0;

typedef struct Temp2_00171cc0 {
    u8 pad0[0x48];
    s32 unk48;
} Temp2_00171cc0;

/*rgp*/
/*rgp*/
/*rgp*/

void MotionListCopy_171cc0(Arg0_00171cc0 *arg0, Arg0_00171cc0 *arg1, s32 arg2) {
    Node_00171cc0 *var_19;
    Temp2_00171cc0 *temp_2;
    Node_00171cc0 *temp_17;

    if (arg2 == 0) {
        arg1->unk0 = arg0->unk0;
        arg1->unk4 = arg0->unk4;
        arg1->unk8 = arg0->unk8;
        return;
    }
    arg1->unk0 = -1;
    arg1->unk4 = NULL;
    var_19 = (Node_00171cc0 *) arg0->unk4;
    while (var_19 != NULL) {
        temp_17 = (Node_00171cc0 *) ((u8 *) var_19 + 0x10);
        if (temp_17 != NULL) {
            temp_2 = ((Temp2_00171cc0 *)MotionListGetOrAddPlayer_172580(arg1, var_19->unkC, arg2, var_19->unk8));
            if (temp_2 != NULL) {
                temp_2->unk48 = 0;
                MotionPlayerReset_173870(temp_2);
                MotionPlayerCopyEntries_1737b0(temp_17, temp_2, arg2);
                var_19 = var_19->unk0;
                continue;
            }
            break;
        }
        var_19 = var_19->unk0;
    }
}
