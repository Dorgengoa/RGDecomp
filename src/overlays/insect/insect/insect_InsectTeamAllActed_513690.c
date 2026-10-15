#include "types.h"
/* insect 0x00513690 -- 184 bytes.  A five-slot scan over a 488-byte record
 * array; the flag starts at 1 and is cleared by the one arm that matches. */

typedef struct Ent {
    u8 pad00[0x71];
    s8 f71;                         /* +0x71 */
    u8 pad72[0x1E8 - 0x72];
} Ent;

extern s32 insect_InsectPieceTestStatus_513280(Ent *e, s32 k);

s32 insect_InsectTeamAllActed_513690(Ent *a, s32 k)
{
    s32  r;
    s32  i;
    Ent *e;

    r = 1;
    for (i = 0; i < 5; i++) {
        e = &a[i];
        if (e != 0) {
            if (insect_InsectPieceTestStatus_513280(e, 0x1B) != 0) {
                if (k == e->f71) {
                    if (insect_InsectPieceTestStatus_513280(e, 0x1C) == 0) {
                        r = 0;
                    }
                }
            }
        }
    }
    return r;
}
