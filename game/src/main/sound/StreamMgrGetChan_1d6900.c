/* rgp:protos */
#define RGP_SELF_StreamMgrGetChan_1d6900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair over four 0xE0-byte records at +0x00.  Retail's
   `sll 3 / subu / sll 5` is mwcc's strength reduction of *0xE0 as
   (index*8 - index)*32, which is what names the record size. */

typedef struct OwnerE0 {
    u8 rec[1];         /* +0x00, 0xE0 bytes each */
} OwnerE0;

void *StreamMgrGetChan_1d6900(OwnerE0 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 4;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0xE0];
}
