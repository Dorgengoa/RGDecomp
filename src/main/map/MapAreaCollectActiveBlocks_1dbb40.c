#include "types.h"

typedef struct O_FUN_001dbb40 {
    u8 pad000[0x1C8];
    s16 m1C8;
    s16 m1CA;
} O_FUN_001dbb40;

extern s32 MapDataIsLoadedOrUnloading_1e7980(s32 v);

s32 MapAreaCollectActiveBlocks_1dbb40(O_FUN_001dbb40 *o, s32 *out, s32 max)
{
    s32 n;
    s32 *p;
    s32 i;

    if (out == 0 || max <= 0) return 0;
    if (MapDataIsLoadedOrUnloading_1e7980((s32)o) == 0) return 0;
    n = 0;
    p = (s32 *)((u8 *)o + 0x178);
    for (i = 0; i < o->m1CA; i++, p++) {
        if (MapDataIsLoadedOrUnloading_1e7980(*p) != 0) {
            out[n] = *p;
            n++;
        }
    }
    return n;
}
