#include "types.h"

class VE {
    u8 pad_[0x24];
public:
    virtual s32 f08();
};

/* The `beql $2,$3` chain jumps INTO each arm, so this is a compiled switch and
   the case order is the compare chain REVERSED (retail tests 4,3,2,1).
   Indirect call: handler table at 0x24 of the item, slot 0x8. */


extern "C" void *ListIterNextItem_1b1db0(void *);

static inline u8 *Pop(u8 *self)
{
    u8 *t = *(u8 **)(self + 0x4);
    if (t == 0) {
        return 0;
    }
    u8 *r = t + 0x10;
    *(u8 **)(self + 0x4) = *(u8 **)(r - 0x10);
    return r;
}

extern "C" void MotionEventListBindHandlers_1b4700(u8 *self, u8 *cfg)
{
    u8 *node;
    u8 *o;

    *(u8 **)(self + 0x4) = *(u8 **)(self + 0x0);
    while ((node = Pop(self)) != 0) {
        *(s32 *)(node + 0x14) = *(s32 *)(node + 0x10);
        while ((o = (u8 *)ListIterNextItem_1b1db0(node)) != 0) {
            switch (((VE *)o)->f08()) {
            case 1:
                *(s32 *)(o + 0x0) = *(s32 *)(cfg + 0x1C);
                break;
            case 2:
                *(s32 *)(o + 0x0) = *(s32 *)(cfg + 0x20);
                break;
            case 3:
                *(s32 *)(o + 0x0) = *(s32 *)(cfg + 0x24);
                break;
            case 4:
                *(s32 *)(o + 0x0) = *(s32 *)(cfg + 0x28);
                break;
            default:
                *(s32 *)(o + 0x0) = 0;
                break;
            }
        }
        *(s32 *)(node + 0x14) = 0;
    }
    *(s32 *)(self + 0x4) = 0;
}
