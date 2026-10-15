/* main s27m: CLOSED -- ARRAY SUBSCRIPT spelling `((T *)(base + K))[idx]` (index in rs of
   the addu); `base + idx * N + K` in any operand order is 6 bad. */
#include "types.h"

extern s32 InsectRecSlotFindFree_3d0210(void);

s32 InsectRecSlotAddItem_3d0190(void *arg0, void *arg1) {
    s32 idx;

    if (arg1 == NULL) {
        return 0;
    }
    idx = InsectRecSlotFindFree_3d0210();
    if (idx < 0) {
        return 0;
    }
    ((s16 *)((u8 *)(*(void **)((u8 *)arg0 + 0x18)) + 2))[idx] = *(s16 *)((u8 *)arg1 + 4);
    ((void **)((u8 *)(*(void **)((u8 *)arg0 + 0x18)) + 0xC))[idx] = arg1;
    return 1;
}
