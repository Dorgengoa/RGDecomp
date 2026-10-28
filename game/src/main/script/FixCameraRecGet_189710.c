/* rgp:protos */
#define RGP_SELF_FixCameraRecGet_189710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair whose table is a POINTER member: count at +0x1630,
   base at +0x1634, records 0xD0 bytes. */

typedef struct RecD0 { u8 bytes[0xD0]; } RecD0;

typedef struct Owner1630 {
    u8 pad000[0x1630];
    s32 count;         /* +0x1630 */
    RecD0 *rec;        /* +0x1634 */
} Owner1630;

void *FixCameraRecGet_189710(Owner1630 *o, s32 index)
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
    return &o->rec[index];
}
