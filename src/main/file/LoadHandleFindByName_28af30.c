#include "types.h"

/* Element stride 0x38 (retail strength-reduces *56 to ((i*8-i)*8)). */

extern s32 LoadHandleNameMatch_28b1c0(void *e, void *key);

void *LoadHandleFindByName_28af30(void *key, void *arr, s32 n)
{
    s32 i;
    void *e;

    if (key == 0 || arr == 0 || n <= 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        e = (u8 *)arr + i * 0x38;
        if (LoadHandleNameMatch_28b1c0(e, key) != 0) {
            return e;
        }
    }
    return 0;
}
