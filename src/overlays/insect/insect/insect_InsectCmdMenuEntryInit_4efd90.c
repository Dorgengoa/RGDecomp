#include "types.h"
/* insect 0x004EFD90 -- 24 bytes, 6 instructions.  Reset a small descriptor;
 * the store order is SOURCE order (0x00, 0x04, 0x0C, then the byte at 0x08 in
 * the `jr` delay slot). */

typedef struct Desc {
    s32 f00;                        /* +0x00 */
    s32 f04;                        /* +0x04 */
    s8  f08;                        /* +0x08 */
    u8  pad09[0xC - 0x9];
    s32 f0C;                        /* +0x0C */
} Desc;

void insect_InsectCmdMenuEntryInit_4efd90(Desc *d)
{
    d->f00 = 0;
    d->f04 = 0;
    d->f0C = 0;
    d->f08 = -1;
}
