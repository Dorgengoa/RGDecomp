#include "types.h"

void *GroupSubEntryFindNth_425e10(void *arg0, s64 arg1, s32 arg2) {
    u8 *t8;
    s16 t7;
    s16 key;
    s32 count;
    s32 i;
    u8 *node;

    t8 = *(u8 **)((u8 *)arg0 + 0x8C);
    if (t8 == 0) goto zero;
    t7 = *(s16 *)((u8 *)arg0 + 0x7C);
    if (t7 > 0) goto ok;
zero:
    return 0;
ok:
    key = (s16)arg1;
    count = 0;
    for (i = 0; i < t7; i++) {
        node = t8 + i * 0x44;
        if (node == 0) break;
        if (*(s16 *)(node + 0x18) != key) continue;
        if (arg2 < 0 || arg2 == count) return node;
        count++;
    }
    return 0;
}
