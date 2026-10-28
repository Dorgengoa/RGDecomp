/* rgp:protos */
#define RGP_SELF_TexPairGet_18fa20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair over eight 0x5C-byte records in a static array. */

typedef struct Rec5C { u8 bytes[0x5C]; } Rec5C;

extern Rec5C D_0049D0B0[];

void *TexPairGet_18fa20(s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 8;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &D_0049D0B0[index];
}
