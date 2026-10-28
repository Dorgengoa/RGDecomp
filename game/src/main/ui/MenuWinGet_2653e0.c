/* rgp:protos */
#define RGP_SELF_MenuWinGet_2653e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair over eight 0xE0-byte records reached through a
   POINTER in small data, not an array -- retail loads D_0048206C with
   `lw %gp_rel` and then indexes it. */

typedef struct RecE0 { u8 bytes[0xE0]; } RecE0;

extern RecE0 *D_0048206C;

void *MenuWinGet_2653e0(s32 index)
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
    return &D_0048206C[index];
}
