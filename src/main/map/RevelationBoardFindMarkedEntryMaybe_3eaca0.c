#include "types.h"

extern void *RevelationBoardFindById_3eb580(void);

s16 RevelationBoardFindMarkedEntryMaybe_3eaca0(void) {
    void *obj;
    u8 *elem;
    s32 i;

    obj = RevelationBoardFindById_3eb580();
    if (obj == NULL) {
        return -1;
    }
    elem = *(u8 **)((u8 *)obj + 8);
    for (i = 0; i < *(s16 *)((u8 *)obj + 4); i++, elem += 0x1C) {
        if (*(u8 *)(elem + 0x18) & 1) {
            return *(s16 *)(elem + 0x16);
        }
    }
    return -1;
}
