/* rgp:protos */
#define RGP_SELF_ObjRecTableGet_1c3fe0 1
#include "port/game_protos.h"
#line 1
#include "objrec.h"

/* The same lookup against the 0x1814 table -- same 0x28 stride and the same
   asymmetric guard pair as ObjRecTableGet_1c3f60. */

typedef struct Owner1810 {
    u8 pad000[0x1810];
    s32 count;         /* +0x1810 */
    u8 rec[1];         /* +0x1814, 0x28 bytes each */
} Owner1810;

/* MATCHED by the shared-label guard recipe -- both guards `goto none`, and
   `none:` goes BEFORE the compute block so the compute needs its own
   `goto found`. The full derivation, the mechanism (a second predecessor is
   what leaves the `b`'s delay slot empty) and the five spellings it replaced
   are written up once, in src/world/ObjRecTableGet_1c3f60.c. */

void *ObjRecTableGet_1c3fe0(Owner1810 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < o->count;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x28];
}
