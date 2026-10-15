#include "types.h"
/* insect 0x005135F0 -- 152 bytes, 38 instructions.
 * The element address is `a + i` off a POINTER parameter, so mwcc cannot
 * prove it non-null and the `if (p == 0)` survives as a real `beql`. */

typedef struct Obj {
    u8 pad00[0x71];
    s8 f71;                         /* +0x71 */
    u8 pad72[0x1E8 - 0x72];
} Obj;

extern s32 insect_InsectPieceTestStatus_513280(Obj *p, s32 k);

s32 insect_InsectTeamIsDefeated_5135f0(Obj *a, s32 k)
{
    s32 r;
    s32 i;

    r = 1;
    for (i = 0; i < 5; i++) {
        Obj *p = a + i;
        if (p == 0) {
            continue;
        }
        if (k != p->f71) {
            continue;
        }
        if (insect_InsectPieceTestStatus_513280(p, 0x1F) == 0) {
            r = 0;
        }
    }
    return r;
}
