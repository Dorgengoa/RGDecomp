#include "types.h"

/* title.bin overlay, 0x004ED380 -- sum a field over a two-element array of
 * 0x20-byte records and return whether the total is positive.
 *
 * `slt $2, $0, $6` in the jr delay slot is `sum > 0`, not `sum != 0`.
 * The array address is materialised %hi/%lo, hence `const`.
 */

typedef struct Rec_title_FUN_004ed380 {
    u8 pad000[0x1C];
    s32 field01C;      /* +0x1C */
} Rec_title_FUN_004ed380;

extern const Rec_title_FUN_004ed380 D_004F19F0[];

s32 title_TitleAnySaveExists_4ed380(void)
{
    s32 total;
    s32 i;

    total = 0;
    for (i = 0; i < 2; i++) {
        total += D_004F19F0[i].field01C;
    }
    return total > 0;
}
