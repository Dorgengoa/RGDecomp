/* rgp:protos */
#define RGP_SELF_FixedTexGet_15d5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair over two 0x68-byte records in a STATIC array.  The
   array is not 4 bytes wide, so mwcc gives it %hi/%lo rather than %gp_rel
   without needing `const`. */

typedef struct Rec68_FUN_0015d5c0 { u8 bytes[0x68]; } Rec68_FUN_0015d5c0;

extern Rec68_FUN_0015d5c0 D_00495DA0[];

void *FixedTexGet_15d5c0(s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 2;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &D_00495DA0[index];
}
