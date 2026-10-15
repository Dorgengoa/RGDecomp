#include "types.h"

typedef struct S2_0028ed70 {
    u8 pad0[4];
    void (*unk4)(void *self, s32 arg1);
} S2_0028ed70;

typedef struct S1_0028ed70 {
    u16 unk0;
    S2_0028ed70 *unk4;
    s32 unk8;
} S1_0028ed70;

extern S2_0028ed70 *StateMachineFindState_28ee80(S1_0028ed70 *, u16);

void StateMachineUpdate_28ed70(S1_0028ed70 *arg0)
{
    S2_0028ed70 *temp;
    S2_0028ed70 *newptr;

    if (arg0->unk8 != 0) {
        temp = arg0->unk4;
        if (temp == NULL) {
            newptr = StateMachineFindState_28ee80(arg0, arg0->unk0);
            arg0->unk4 = newptr;
            if (newptr != NULL) {
                arg0->unk0 = 0;
                arg0->unk4->unk4(arg0, 1);
            }
        } else {
            temp->unk4(arg0, 0);
        }
    }
}
