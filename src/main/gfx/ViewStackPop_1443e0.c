#include "types.h"

struct Obj0 {
    u8  pad000[0xF20];
    u8 *mF20;
};

extern s32 DrawListAddViewPacket_1482e0(struct Obj0 *);
extern void DrawListAddCameraMatrixPacket_1481b0(struct Obj0 *);

/* sltu on the compare -> both sides are pointers (unsigned).
   The store must be a MEMBER store (sw ..,0xF20($16)), not a cast walk. */
void ViewStackPop_1443e0(struct Obj0 *p0)
{
    u8 *cur;

    cur = p0->mF20;
    if ((u8 *)p0 + 0xF30 < cur) {
        p0->mF20 = cur - 0x4F0;
        DrawListAddViewPacket_1482e0(p0);
        DrawListAddCameraMatrixPacket_1481b0(p0);
    }
}
