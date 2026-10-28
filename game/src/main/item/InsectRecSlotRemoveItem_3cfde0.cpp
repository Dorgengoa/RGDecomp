#include "types.h"
#pragma opt_propagation off
typedef struct Tb { s16 h[4]; s32 w[6]; } Tb;
typedef struct O { u8 pad[0x18]; Tb *t; } O;
extern "C" void ItemMarkRemoved_3d4130(s32, s32);

extern "C" bool InsectRecSlotRemoveItem_3cfde0(O *arg0, s32 arg1, s32 arg2)
{
    bool r;
    s32 i;

    if (arg1 == 0) {
        return false;
    }
    r = false;
    for (i = 0; i < 5; i++) {
        if (arg0->t->w[i + 1] == arg1) {
            for (i++; i < 5; i++) {
                arg0->t->h[i] = arg0->t->h[i + 1];
                arg0->t->w[i] = arg0->t->w[i + 1];
            }
            arg0->t->h[5] = -1;
            arg0->t->w[5] = 0;
            if (arg2 != 0) {
                ItemMarkRemoved_3d4130(arg1, 0);
            }
            r = true;
            break;
        }
    }
    return r;
}
