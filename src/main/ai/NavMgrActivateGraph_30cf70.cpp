#include "types.h"

extern "C" {
extern void PtrArrayUpdatePow2_30d0a0(u8 *arg0);
extern s32 PtrArrayInsertAt_30d0d0(u8 *arg0, u8 *arg1, s32 arg2);
extern s32 NavMgrFindInsertIndex_30d190(u8 *arg0, s32 arg1);
extern void PtrArrayRemove_30d270(u8 *arg0, u8 *arg1);
extern s32 PtrArrayIsAllocated_30d350(u8 *arg0);
extern void BitArraySet_42cdc0(u8 *arg0, u32 arg1, s32 arg2);
extern s32 BitArrayTest_42ce40(u8 *arg0, u32 arg1);
extern s32 NavGraphGetIdThunk_310e90(u8 *arg0);
}

static inline bool Valid30CF70(u8 *a)
{
    bool v;

    if (*(s32 *)(a + 0x0) == 0) {
        v = false;
    } else if (*(s32 *)(a + 0x8) == 0) {
        v = false;
    } else if (*(s32 *)(a + 0x18) == 0) {
        v = false;
    } else {
        v = true;
    }
    return v;
}

static inline u8 *Get30CF70(u8 *a, u32 i)
{
    u8 *e;

    if (i >= *(u32 *)(a + 0x4)) {
        e = 0;
    } else {
        e = *(u8 **)(a + 0x0) + i * 0x120;
    }
    return e;
}

extern "C" s32 NavMgrActivateGraph_30cf70(u8 *arg0, u32 arg1)
{
    u8 *e;

    if (!Valid30CF70(arg0)) {
        return 0;
    }
    if (BitArrayTest_42ce40(arg0 + 0x18, arg1) != 0) {
        return 0;
    }
    e = Get30CF70(arg0, arg1);
    if (e == 0) {
        return 0;
    }
    if (PtrArrayIsAllocated_30d350(arg0 + 8) != 0 && e != 0) {
        PtrArrayRemove_30d270(arg0 + 8, e);
        if (PtrArrayInsertAt_30d0d0(arg0 + 8, e, NavMgrFindInsertIndex_30d190(arg0 + 8, NavGraphGetIdThunk_310e90(e))) >= 0) {
            PtrArrayUpdatePow2_30d0a0(arg0 + 8);
        }
    }
    BitArraySet_42cdc0(arg0 + 0x18, arg1, 1);
    return 1;
}
