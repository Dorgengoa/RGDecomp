#include "types.h"

class Obj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual s32 get();
};

typedef struct {
    u8 pad0[0x10];
    s16 *unk10;
} Arg1;

extern "C" {
extern s32 InvFindFreeSlotId_3c4900(s32, s32, s32);
extern s32 InvMoveItemMaybe_3c5b10(s32, Arg1 *, s32, s32, s32, s32, s32, u8);
extern Obj *InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
extern s32 ItemGetStackLimit_3d4480(Obj *);
extern s32 ItemHasCountFlag_3d44e0(Arg1 *);
}

extern "C" s32 InvMoveItemToCategoryMaybe_3c59b0(s32 arg0, Arg1 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7)
{
    s32 s;
    s32 res;
    s32 k;
    Obj *o;
    s32 v;

    if (arg1 == NULL) {
        return 0;
    }
    s = *arg1->unk10;
    res = -1;
    if (ItemHasCountFlag_3d44e0(arg1) != 0) {
        k = -1;
        for (;;) {
            o = InvFindInCategoryRange_3c8370(arg0, s, arg2, k, 0, 1);
            if (o == NULL) {
                break;
            }
            v = o->get();
            if (v < ItemGetStackLimit_3d4480(o)) {
                res = *(s16 *)((u8 *)o + 6);
                break;
            }
            k = *(s16 *)((u8 *)o + 6) + 1;
        }
    }
    if (res < 0) {
        res = InvFindFreeSlotId_3c4900(arg0, s, arg2);
    }
    if (res < 0) {
        return 0;
    }
    return InvMoveItemMaybe_3c5b10(arg0, arg1, res, arg3, arg4, arg5, arg6, arg7);
}
