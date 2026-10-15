#include "types.h"
/* insect 0x00513540 -- 176 bytes, 44 instructions.
 * Walks the five 0x1E8-byte entries of an array and clears state 0x1C on
 * every entry that carries state 0x1B and whose f71 matches the argument. */

typedef struct Obj {
    u8  pad00[0x71];
    s8  f71;                        /* +0x71 */
    u8  pad72[0x1E8 - 0x72];
} Obj;

extern s32 insect_InsectPieceTestStatus_513280(Obj *e, s32 k);
extern void insect_InsectPieceSetStatus_5132d0(Obj *e, s32 k);

void insect_InsectTeamMarkAllActed_513540(Obj *a, s32 b)
{
    Obj *e;
    s32 i;

    i = 0;
    do {
        e = &a[i];
        if (e != 0) {
            if (insect_InsectPieceTestStatus_513280(e, 0x1B) != 0) {
                if (b == e->f71) {
                    if (insect_InsectPieceTestStatus_513280(e, 0x1C) == 0) {
                        insect_InsectPieceSetStatus_5132d0(e, 0x1C);
                    }
                }
            }
        }
        i++;
    } while (i < 5);
}
