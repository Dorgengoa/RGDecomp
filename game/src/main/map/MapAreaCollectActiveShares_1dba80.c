/* rgp:protos */
#define RGP_SELF_MapAreaCollectActiveShares_1dba80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O_FUN_001dba80 {
    u8 pad000[0x1C8];
    s16 m1C8;
    s16 m1CA;
} O_FUN_001dba80;

/*rgp*/

s32 MapAreaCollectActiveShares_1dba80(O_FUN_001dba80 *o, s32 *out, s32 max)
{
    s32 n;
    s32 *p;
    s32 i;

    if (out == 0 || max <= 0) return 0;
    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980((s32)o)) == 0) return 0;
    n = 0;
    p = (s32 *)((u8 *)o + 0x128);
    for (i = 0; i < o->m1C8; i++, p++) {
        if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(*p)) != 0) {
            out[n] = *p;
            n++;
        }
    }
    return n;
}
