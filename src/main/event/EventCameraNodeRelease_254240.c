#include "types.h"

typedef struct S00254240_a1 {
    u8 pad0[0x5C];
    s32 unk5C;
} S00254240_a1;

typedef struct S00254240_a0 {
    u8 pad0[0x30];
    s32 unk30;
    s32 unk34;
} S00254240_a0;

extern void EventCameraNodeReset_254c90(void *);

s32 EventCameraNodeRelease_254240(S00254240_a0 *arg0, S00254240_a1 *arg1, s32 arg2)
{
    s32 result;

    if (arg1 == NULL) {
        return 0;
    }
    result = arg1->unk5C;
    switch (arg2) {
    case 0:
        if (arg0->unk30 == 0) {
            EventCameraNodeReset_254c90(arg1);
        }
        break;
    case 1:
        if (arg0->unk34 == 0) {
            EventCameraNodeReset_254c90(arg1);
        }
        break;
    case 2:
        EventCameraNodeReset_254c90(arg1);
        break;
    }
    return result;
}
