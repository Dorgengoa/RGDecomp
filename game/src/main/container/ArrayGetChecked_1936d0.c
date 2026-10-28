/* rgp:protos */
#define RGP_SELF_ArrayGetChecked_1936d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair, table a POINTER member: count at +0x9C, base at
   +0xA0, records 0x1D0 bytes. */

typedef struct Rec1D0 { u8 bytes[0x1D0]; } Rec1D0;

typedef struct Owner9C {
    u8 pad000[0x9C];
    s32 count;         /* +0x9C */
    Rec1D0 *rec;       /* +0xA0 */
} Owner9C;

void *ArrayGetChecked_1936d0(Owner9C *o, s32 index)
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
