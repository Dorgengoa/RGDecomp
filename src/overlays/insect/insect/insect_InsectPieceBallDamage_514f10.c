#include "types.h"
/* insect 0x00514F10 -- 84 bytes, 21 instructions.  Subtracts damage from the
 * s8 gauge at +0x4C, clamping at zero and raising the state byte.  The tail's
 * `dsll32 $2,$16,24` / `dsra32 $2,$2,24` is an s64 return of an (s8) cast, not
 * an s8 local -- the guard tests the FULL s32 difference. */

typedef struct Obj {
    u8 pad00[0x41];
    s8 f41;                         /* +0x41 */
    u8 pad42[0x4C - 0x42];
    s8 f4C;                         /* +0x4C */
} Obj;

extern void insect_InsectPieceSetStatus_5132d0(Obj *o, s32 k);

s64 insect_InsectPieceBallDamage_514f10(Obj *o, s32 d)
{
    s32 v;

    v = o->f4C - d;
    if (v <= 0) {
        v = 0;
        insect_InsectPieceSetStatus_5132d0(o, 0x18);
        o->f41 = 2;
    }
    o->f4C = v;
    return (s8)v;
}
