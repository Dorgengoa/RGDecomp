#include "types.h"

class Sub {
public:
    s32 a;
    s32 b;
    s32 c;
    virtual s32 v08(s32);
};

struct Obj {
    u8 pad0[0x10];
    Sub sub;
    s32 unk20;
};

extern "C" {
s32 MemStackHeapFree_14dcb0(s32, s32);
s32 MemStackHeapAllocBack_14dcf0(s32, u32);
u32 AlignUp16_1cacd0(s32);
s32 MapNodeMoveReqSet_2fa800(s32, s32, s32, s32, s32);
s32 MapNodeMoveReqReset_2fa8d0(s32);
s32 DListNodeInit_42ec10(s32);
}

extern "C" s32 MapSequencerAddMoveReq_2fa150(Obj *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 t;

    if (arg0->unk20 == 0) {
        return 0;
    }
    t = MemStackHeapAllocBack_14dcf0(arg0->unk20, AlignUp16_1cacd0(0x40) >> 4);
    if (t == 0) {
        MemStackHeapFree_14dcb0(arg0->unk20, t);
        return 0;
    }
    DListNodeInit_42ec10(t);
    MapNodeMoveReqReset_2fa8d0(t + 0x10);
    if (MapNodeMoveReqSet_2fa800(t + 0x10, arg1, arg2, arg3, arg4) == 0) {
        MemStackHeapFree_14dcb0(arg0->unk20, t);
        return 0;
    }
    if (arg0->sub.v08(t) == 0) {
        MemStackHeapFree_14dcb0(arg0->unk20, t);
        return 0;
    }
    return 1;
}
