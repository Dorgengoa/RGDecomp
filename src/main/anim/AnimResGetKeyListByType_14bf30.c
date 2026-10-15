#include "types.h"


s32 AnimResGetKeyListByType_14bf30(void **arg0, s32 arg1)
{
    u8 *e;
    u8 *p;
    s32 i;
    s32 n;
    s32 ok;

    p = (u8 *)*arg0;
    ok = p != NULL;
    if (!ok) {
        return 0;
    }
    if (arg1 == 1) {
        if (!ok) return 0;
        return *(s32 *)(p + 0x20);
    }
    if (arg1 == 2) {
        if (!ok) return 0;
        return *(s32 *)(p + 0x28);
    }
    n = *(s32 *)(p + 0x2C);
    if (n == 0) {
        return 0;
    }
    e = *(u8 **)(p + 0x30);
    for (i = 0; i < n; i++) {
        if (*(s32 *)(e + 4) == arg1) {
            return *(s32 *)(e + 0xC);
        }
        e = *(u8 **)e;
    }
    return 0;
}
