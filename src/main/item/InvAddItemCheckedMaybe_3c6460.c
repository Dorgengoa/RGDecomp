#include "types.h"

extern void InvAddItemCoreMaybe_3c6540(void *a, void *b, void *c, void *d, s32 e, s32 f, s32 *n);

s32 InvAddItemCheckedMaybe_3c6460(void *a, void *b, void *c, void *d, s32 *out)
{
    s32 n;

    n = 0;
    InvAddItemCoreMaybe_3c6540(a, b, d, c, -1, 1, &n);
    if (out != 0) {
        *out = n;
    }
    if (n > 0) {
        return 0;
    }
    return 1;
}
