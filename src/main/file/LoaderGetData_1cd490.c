#include "types.h"

struct R1CD490 { u8 pad000[0x90]; void *f90; s32 f94; };

extern struct R1CD490 *LoaderQueueFindUnitById_1cdc70(void *p, s32 a, u8 *b, s32 z);

void *LoaderGetData_1cd490(void *p, s32 a, s32 *out)
{
    struct R1CD490 *r;

    if (out != 0) {
        *out = 0;
    }
    r = LoaderQueueFindUnitById_1cdc70(p, a, (u8 *)p + 0x30, 0);
    if (r != 0) goto ok;
    return 0;
ok:
    if (out != 0) {
        *out = r->f94;
    }
    return r->f90;
}
