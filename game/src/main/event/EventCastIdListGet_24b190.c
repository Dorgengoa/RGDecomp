/* rgp:protos */
#define RGP_SELF_EventCastIdListGet_24b190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Bounds-checked read out of a pointed-to s32 array, -1 when out of range.
   The same asymmetric two-guard shape as the ObjRecTableGet_1c3f60 family, with -1 as
   the fallback instead of a null pointer. */

typedef struct Table320 {
    u8 pad000[0x320];
    s32 *entry;        /* +0x320 */
    s32 count;         /* +0x324 */
} Table320;

/* MATCHED by the shared-label guard recipe -- both guards `goto none`, and
   `none:` goes BEFORE the compute block so the compute needs its own
   `goto found`. The full derivation, the mechanism (a second predecessor is
   what leaves the `b`'s delay slot empty) and the five spellings it replaced
   are written up once, in src/world/ObjRecTableGet_1c3f60.c. */

s32 EventCastIdListGet_24b190(Table320 *t, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < t->count;
    if (ok != 0) {
        goto found;
    }
none:
    return -1;
found:
    return t->entry[index];
}
