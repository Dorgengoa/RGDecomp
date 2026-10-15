#include "types.h"
/* insect 0x00512E20 -- 80 bytes, 20 instructions.
 * The u8 member is widened into an s32 local, which is why the halving is an
 * arithmetic `sra` and the return needs no `andi 0xFF`.
 */

typedef struct Obj {
    u8  pad00[0x2A];
    u8  m2A[1];                     /* +0x2A */
} Obj;

extern s32 insect_InsectPieceTestStatus_513280(Obj *, s32);

s32 insect_InsectPieceGetStat_512e20(Obj *o, s32 i, s32 k)
{
    s32 v;

    v = o->m2A[i];
    if (insect_InsectPieceTestStatus_513280(o, 3) != 0) {
        if (k == 0) {
            v >>= 1;
        }
    }
    return v;
}
